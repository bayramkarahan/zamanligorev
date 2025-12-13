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

    QTimer *gorevKontrolTimer = new QTimer();
    QObject::connect(gorevKontrolTimer, &QTimer::timeout, [&](){

    gorevKontrol();
    });
    gorevKontrolTimer->start(500);
    init();
}

void Servis::init()
{
    qDebug()<<"init...";
    DatabaseHelper *db=new DatabaseHelper(localDir+"zamanligorev.json");
    taskList = db->Oku();
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
            QString taskCommand=veri["taskCommand"].toString();
            QTime taskTime = QTime::fromString(veri["taskTime"].toString(), "hh:mm");
            bool selectedTask = veri.value(QStringLiteral("selectedTask")).toBool(false);
            int zaman=saatToSaniye(taskTime).toInt();

            if(qAbs(currentsaatsaniye-zaman)<=2&&selectedTask)
            {
                QString key = taskCommand + QString::number(zaman);

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

