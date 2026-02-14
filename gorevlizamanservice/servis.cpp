#include "servis.h"
#include<Database.h>
QSet<QString> Servis::calisanGorevler;   // 👈 TANIM
Servis::Servis()
{
    qDebug()<<"servis...";
    localDir="/usr/share/zamanligorev/";

    zamanliGorevConfWather.addPath(localDir+"zamanligorev.json");
     QObject::connect(&zamanliGorevConfWather, &QFileSystemWatcher::fileChanged, this,
            [this](){
                init();   // burada tekrar addPath() çağırılacak
            });

    QTimer *gorevKontrolTimer = new QTimer(this);
    QObject::connect(gorevKontrolTimer, &QTimer::timeout, [&](){

    gorevKontrol();
    });
    gorevKontrolTimer->start(500);
    init();
    //************************************************************
    //************************************************************
    bool noLoginStatus=false;
    QTimer *shutdownTimer = new QTimer(this);
    for (const QJsonValue &item : taskList) {
        if (!item.isObject()) continue;
        QJsonObject veri = item.toObject();
        QString taskCommand=veri["taskCommand"].toString();
        QTime taskTime = QTime::fromString(veri["taskTime"].toString(), "HH:mm");
        bool selectedTask = veri.value(QStringLiteral("selectedTask")).toBool(false);
        int zaman=saatToSaniye(taskTime).toInt();
        if(taskCommand=="nologinpoweroff"&&selectedTask)
        {
          shutdownTimer->setInterval(zaman * 1000); // saniye to milisaniye
            noLoginStatus=true;
        }

    }
    shutdownTimer->setSingleShot(true);

    connect(shutdownTimer, &QTimer::timeout, this, [](){
        QProcess::startDetached("systemctl", {"poweroff"});
    });

    //************************************************************
    //************************************************************
    QTimer *checkNologinTimer = new QTimer(this);
    checkNologinTimer->setInterval(5000);

    connect(checkNologinTimer, &QTimer::timeout, this, [=]() {

        if (isLoginScreen())  // login YOK
        {
            if (!shutdownTimer->isActive())
            {
                qDebug() << "Login yok, sayac basladi.";
                shutdownTimer->start();
            }
        }
        else  // login VAR
        {
            if (shutdownTimer->isActive())
            {
                qDebug() << "Login oldu, shutdown iptal.";
                shutdownTimer->stop();
            }
        }
    });

    if(noLoginStatus)
    {
        checkNologinTimer->start();
    }

}

void Servis::init()
{
    qDebug()<<"init...";
    DatabaseHelper *db=new DatabaseHelper(localDir+"zamanligorev.json");
    taskList = db->Oku();
}

bool Servis::isLoginScreen()
{
    QProcess proc;
    proc.start("loginctl", {"list-sessions", "--no-legend"});
    proc.waitForFinished();

    QString output = proc.readAllStandardOutput();
    QStringList lines = output.split("\n", Qt::SkipEmptyParts);

    for (const QString &line : lines)
    {
        if (line.contains("seat0") && !line.contains("lightdm"))
            return false;  // login VAR
    }

    return true; // login YOK
}


void Servis::gorevKontrol()
{
    int currentsaatsaniye =
        QTime::currentTime().hour()   * 3600 +
        QTime::currentTime().minute() * 60   +
        QTime::currentTime().second();

      //qDebug()<<"gorev kontrol"<<currentsaatsaniye;
        for (const QJsonValue &item : taskList) {
            if (!item.isObject()) continue;
            QJsonObject veri = item.toObject();
            QString index=veri["index"].toString();
            QString taskCommand=veri["taskCommand"].toString();
            QTime taskTime = QTime::fromString(veri["taskTime"].toString(), "HH:mm");
            bool selectedTask = veri.value(QStringLiteral("selectedTask")).toBool(false);
            int zaman=saatToSaniye(taskTime).toInt();
            QString today = QDate::currentDate().toString("yyyyMMdd");
            if(qAbs(currentsaatsaniye-zaman)<=2&&selectedTask)
            {
                 QString key = index + "_" + today + "_" + taskTime.toString("HHmm");

                if (calisanGorevler.contains(key))
                    continue;
                calisanGorevler.insert(key);
                qDebug()<<"görev:"<<taskCommand<<zaman<<currentsaatsaniye;
                system(taskCommand.toStdString().c_str());
            }
        }
}

QTime Servis::saniyeToSaat(QString _zaman)
{
    QTime zm(0,0,0);
    zm=zm.addSecs(_zaman.toInt());
    return zm;
}
QString Servis::saatToSaniye(QTime _zaman)
{
    int zmm=_zaman.hour()*60*60+_zaman.minute()*60+_zaman.second();
    return QString::number(zmm);
}

