/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#ifndef AYAR_H
#define AYAR_H
#include<QToolButton>
#include<QCheckBox>
#include<QMessageBox>
#include<QApplication>
#include<QDesktopWidget>
#include <functional>

QWidget* MainWindow::ayar()
{
    QDialog *d = new QDialog();
    d->setWindowTitle(tr("Görev Listesi"));
    d->setFixedSize(QSize(boy*32,boy*18));
    d->setWindowIcon(QIcon(":/icons/zamanligorev.svg"));

    QTableWidget *twlh = new QTableWidget(d);
    twlh->setFixedSize(QSize(boy*31,boy*13));
    twlh->setColumnCount(6);
    twlh->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Seç")));
    twlh->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Index")));
    twlh->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Görev Zamanı")));
    twlh->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Görev")));
    twlh->setHorizontalHeaderItem(4, new QTableWidgetItem(""));
    twlh->setHorizontalHeaderItem(5, new QTableWidgetItem(""));

    twlh->setSelectionBehavior(QAbstractItemView::SelectRows);
    twlh->setSelectionMode(QAbstractItemView::SingleSelection);

    twlh->setColumnWidth(0, boy*1);
    twlh->setColumnWidth(1, boy*1);
    twlh->setColumnWidth(2, boy*5);
    twlh->setColumnWidth(3, boy*16);
    twlh->setColumnWidth(4, boy*3);
    twlh->setColumnWidth(5, boy*2);
twlh->setColumnHidden(1, true);
    DatabaseHelper *db = new DatabaseHelper(localDir+"zamanligorev.json");

    // Tabloyu doldur
    auto fillTable = [twlh, db, this](void) {
        twlh->setRowCount(0);
        QJsonArray dizi = db->Oku();
        int sr = 0;
        for (const QJsonValue &item : dizi)
        {
            QJsonObject veri = item.toObject();
            twlh->insertRow(sr);

            QCheckBox *mCheck = new QCheckBox();
            mCheck->setChecked(veri.value("selectedTask").toBool());

            QLineEdit *index = new QLineEdit(veri.value("index").toString());
            index->setReadOnly(true);
            QString timeStr = veri.value("taskTime").toString();
            QTimeEdit *taskTime = new QTimeEdit(this);
            taskTime->setTime(QTime::fromString(timeStr, "HH:mm"));

            QLineEdit *taskCommand = new QLineEdit(veri.value("taskCommand").toString());

            QToolButton *saveButton = new QToolButton();
            saveButton->setText(tr("Kaydet"));

            QToolButton *removeButton = new QToolButton();
            removeButton->setText(tr("Sil"));

            // Save lambda (sadece bu satırı güncelle)
            connect(saveButton, &QToolButton::clicked, this, [this,twlh, db, sr]() {
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
                db->Sil("index", idxWidget->text());
                QJsonObject yeni;
                yeni["index"] = idxWidget->text();
                yeni["taskTime"] = taskTimeWidget->time().toString("hh:mm");
                yeni["taskCommand"] = taskCommandWidget->text();
                yeni["selectedTask"] = chk->isChecked();
                db->Ekle(yeni);
                //fillTable();
            });

            // Remove lambda (sadece bu satırı kaldır)
            connect(removeButton, &QToolButton::clicked, this, [this, twlh, db, sr]() {
                QToolButton* btn = qobject_cast<QToolButton*>(sender());
                if (!btn) return;

                // Satır numarasını bul
                int row = -1;
                for (int i = 0; i < twlh->rowCount(); ++i)
                    if (twlh->cellWidget(i, 5) == btn) {  // 4: removeButton sütunu
                        row = i;
                        break;
                    }

                if (row < 0) return;

                // Şimdi row ile DB ve widgetlar güncellenebilir
                QLineEdit* idxWidget = qobject_cast<QLineEdit*>(twlh->cellWidget(row, 1));
                if (!idxWidget) return;

                // DB’den sil
                db->Sil("index", idxWidget->text());

                // Satırı kaldır
                twlh->removeRow(row);
            });

            twlh->setCellWidget(sr, 0, mCheck);
            twlh->setCellWidget(sr, 1, index);
            twlh->setCellWidget(sr, 2, taskTime);
            twlh->setCellWidget(sr, 3, taskCommand);
            twlh->setCellWidget(sr, 4, saveButton);
            twlh->setCellWidget(sr, 5, removeButton);

            sr++;
        }
    };

    fillTable(); // tabloyu başta doldur

    // Yeni kelime ekleme
    QToolButton *insertWordButton= new QToolButton;
    insertWordButton->setFixedSize(QSize(boy*5,boy*4));
    insertWordButton->setIconSize(QSize(boy*5,boy*2));
    insertWordButton->setStyleSheet("Text-align:center");
    insertWordButton->setIcon(QIcon(":/icons/add.svg"));
    insertWordButton->setAutoRaise(true);
    insertWordButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    insertWordButton->setText(tr("Yeni Görev Ekle"));
    connect(insertWordButton, &QToolButton::clicked, this, [twlh, db, fillTable]() {
        QJsonObject veri;
        veri["index"] = QString::number(db->getIndex("index"));
        veri["taskCommand"] = "sample";
        veri["taskTime"] = "00:00";
        veri["selectedTask"] = db->Oku().isEmpty();
        db->Ekle(veri);
        fillTable(); // yeni satır eklendiğinde tabloyu yeniden doldur
    });

    QVBoxLayout * vbox = new QVBoxLayout();
    vbox->addWidget(twlh);
    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(insertWordButton);
    //hbox->addWidget(webAyarGuncelleButton);

    vbox->addLayout(hbox);

    d->setLayout(vbox);

    return d;
}

#endif // AYAR_H
