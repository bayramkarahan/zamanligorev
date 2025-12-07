#include "servis.h"
#include<Database.h>
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
    gorevKontrolTimer->start(6000);
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

            int zaman=saatToSaniye(taskTime).toInt();

            if(qAbs(currentsaatsaniye-zaman)<=2)
            {
                qDebug()<<"görev:"<<taskCommand<<zaman<<currentsaatsaniye;
                system(taskCommand.toStdString().c_str());
                break;
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

