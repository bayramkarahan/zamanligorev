#include "ayarwidget.h"
#include<Database.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QTimeEdit>
#include <QToolButton>
#include <QHeaderView>
#include <QIcon>

AyarWidget::AyarWidget(const QString& localDir, int boy, QWidget *parent)
    : QWidget(parent),
    boy(boy),
    localDir(localDir)
{
    db = new DatabaseHelper(localDir + "zamanligorev.json");
    setupUI();
    fillTable();
}

void AyarWidget::setupUI()
{
    setWindowTitle(tr("Görev Listesi"));
    setFixedSize(QSize(boy*32, boy*18));
    setWindowIcon(QIcon(":/icons/zamanligorev.svg"));

    twlh = new QTableWidget(this);
    twlh->setFixedSize(QSize(boy*31, boy*13));
    twlh->setColumnCount(6);

    twlh->setHorizontalHeaderLabels({
        tr("Seç"),
        tr("Index"),
        tr("Görev Zamanı"),
        tr("Görev"),
        "",
        ""
    });

    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);

    twlh->setColumnWidth(0, boy*1);
    twlh->setColumnWidth(1, boy*1);
    twlh->setColumnWidth(2, boy*5);
    twlh->setColumnWidth(3, boy*18);
    twlh->setColumnWidth(4, boy*3);
    twlh->setColumnWidth(5, boy*2);
    twlh->setColumnHidden(1, true);
    // Yeni Görev
    insertTaskButton = new QToolButton(this);
    insertTaskButton->setFixedSize(QSize(boy*5, boy*4));
    insertTaskButton->setIconSize(QSize(boy*5, boy*2));
    insertTaskButton->setIcon(QIcon(":/icons/add.svg"));
    insertTaskButton->setAutoRaise(true);
    insertTaskButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    insertTaskButton->setText(tr("Özel Görev Ekle"));

    connect(insertTaskButton, &QToolButton::clicked, this, [this]() {
        QJsonObject veri;
        veri["index"] = QString::number(db->getIndex("index"));
        veri["taskCommand"] = "sample";
        veri["taskTime"] = "00:00";
        veri["selectedTask"] = db->Oku().isEmpty();
        db->Ekle(veri);
        fillTable();
    });

    // poweroff
    insertPowerOffButton = new QToolButton(this);
    insertPowerOffButton->setFixedSize(QSize(boy*5, boy*4));
    insertPowerOffButton->setIconSize(QSize(boy*5, boy*2));
    insertPowerOffButton->setIcon(QIcon(":/icons/close.svg"));
    insertPowerOffButton->setAutoRaise(true);
    insertPowerOffButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    insertPowerOffButton->setText(tr("Kapat Görevi Ekle"));

    connect(insertPowerOffButton, &QToolButton::clicked, this, [this]() {
        QJsonObject veri;
        veri["index"] = QString::number(db->getIndex("index"));
        veri["taskCommand"] = "/usr/sbin/poweroff";
        veri["taskTime"] = "17:00";
        veri["selectedTask"] = db->Oku().isEmpty();
        db->Ekle(veri);
        fillTable();
    });

    // reboot Görev
    insertRebootButton = new QToolButton(this);
    insertRebootButton->setFixedSize(QSize(boy*5, boy*4));
    insertRebootButton->setIconSize(QSize(boy*5, boy*2));
    insertRebootButton->setIcon(QIcon(":/icons/reboot.svg"));
    insertRebootButton->setAutoRaise(true);
    insertRebootButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    insertRebootButton->setText(tr("Yeniden Başlat\n Görevi Ekle"));

    connect(insertRebootButton, &QToolButton::clicked, this, [this]() {
        QJsonObject veri;
        veri["index"] = QString::number(db->getIndex("index"));
        veri["taskCommand"] = "/usr/sbin/reboot";
        veri["taskTime"] = "13:00";
        veri["selectedTask"] = db->Oku().isEmpty();
        db->Ekle(veri);
        fillTable();
    });

    // logout Görev
    insertLogoutButton = new QToolButton(this);
    insertLogoutButton->setFixedSize(QSize(boy*5, boy*4));
    insertLogoutButton->setIconSize(QSize(boy*5, boy*2));
    insertLogoutButton->setIcon(QIcon(":/icons/session.svg"));
    insertLogoutButton->setAutoRaise(true);
    insertLogoutButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    insertLogoutButton->setText(tr("Oturum Kapat\n Görevi Ekle"));

    connect(insertLogoutButton, &QToolButton::clicked, this, [this]() {
        QJsonObject veri;
        veri["index"] = QString::number(db->getIndex("index"));
        veri["taskCommand"] = "loginctl terminate-seat seat0";
        veri["taskTime"] = "12:10";
        veri["selectedTask"] = db->Oku().isEmpty();
        db->Ekle(veri);
        fillTable();
    });

    // lockscreen gorev
    insertLockButton = new QToolButton(this);
    insertLockButton->setFixedSize(QSize(boy*5, boy*4));
    insertLockButton->setIconSize(QSize(boy*5, boy*2));
    insertLockButton->setIcon(QIcon(":/icons/lock.svg"));
    insertLockButton->setAutoRaise(true);
    insertLockButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    insertLockButton->setText(tr("Oturum Kilitle\n Görevi Ekle"));

    connect(insertLockButton, &QToolButton::clicked, this, [this]() {
        QJsonObject veri;
        veri["index"] = QString::number(db->getIndex("index"));
        veri["taskCommand"] = "sessionlockzm";
        veri["taskTime"] = "00:00";
        veri["selectedTask"] = db->Oku().isEmpty();
        db->Ekle(veri);
        fillTable();
    });
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    vbox->addWidget(twlh);
    hbox->addWidget(insertPowerOffButton);
    hbox->addWidget(insertRebootButton);
    hbox->addWidget(insertLogoutButton);
    hbox->addWidget(insertLockButton);
    hbox->addWidget(insertTaskButton);
    vbox->addLayout(hbox);

    setLayout(vbox);
}

void AyarWidget::fillTable()
{
    twlh->setRowCount(0);
    QJsonArray dizi = db->Oku();

    int sr = 0;
    for (const QJsonValue &item : dizi)
    {
        QJsonObject veri = item.toObject();
        twlh->insertRow(sr);

        QCheckBox *chk = new QCheckBox();
        chk->setChecked(veri.value("selectedTask").toBool());

        QLineEdit *index = new QLineEdit(veri.value("index").toString());
        index->setReadOnly(true);

        QTimeEdit *time = new QTimeEdit(this);
        time->setTime(QTime::fromString(veri["taskTime"].toString(), "HH:mm"));

        QLineEdit *cmd = new QLineEdit(veri["taskCommand"].toString());

        QToolButton *saveButton = new QToolButton();
        saveButton->setText(tr("Kaydet"));
        /*connect(save, &QToolButton::clicked, this, [this]() {

            fillTable();
        });*/
        // Save lambda (sadece bu satırı güncelle)
        connect(saveButton, &QToolButton::clicked, this, [this, index]() {
            QToolButton* btn = qobject_cast<QToolButton*>(sender());
            if (!btn) return;

            // Satır numarasını bul
            int row = -1;
            for (int i = 0; i < twlh->rowCount(); ++i)
                if (twlh->cellWidget(i, 4) == btn) {  // 3: saveButton sütunu
                    row = i;
                    break;
                }
            if (row < 0) return;

            QLineEdit* idxWidget = qobject_cast<QLineEdit*>(twlh->cellWidget(row, 1));
            QTimeEdit* taskTimeWidget = qobject_cast<QTimeEdit*>(twlh->cellWidget(row, 2));
            QLineEdit* taskCommandWidget = qobject_cast<QLineEdit*>(twlh->cellWidget(row, 3));
            QCheckBox* chk = qobject_cast<QCheckBox*>(twlh->cellWidget(row, 0));

            if (!idxWidget || !taskTimeWidget || !taskCommandWidget || !chk) return;
            // DB güncelle
            db->Sil("index", index->text());
            QJsonObject yeni;
            yeni["index"] = idxWidget->text();
            yeni["taskTime"] = taskTimeWidget->time().toString("HH:mm");
            yeni["taskCommand"] = taskCommandWidget->text();
            yeni["selectedTask"] = chk->isChecked();
            db->Ekle(yeni);
            fillTable();
        });


        QToolButton *remove = new QToolButton();
        remove->setText(tr("Sil"));
        connect(remove, &QToolButton::clicked, this, [this, index]() {
            db->Sil("index", index->text());
            fillTable();
        });

        twlh->setCellWidget(sr, 0, chk);
        twlh->setCellWidget(sr, 1, index);
        twlh->setCellWidget(sr, 2, time);
        twlh->setCellWidget(sr, 3, cmd);
        twlh->setCellWidget(sr, 4, saveButton);
        twlh->setCellWidget(sr, 5, remove);

        sr++;
    }
}
