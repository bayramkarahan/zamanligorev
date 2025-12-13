#ifndef SERVIS_H
#define SERVIS_H
#include<QDebug>
#include <QObject>
#include<QTimer>
#include<QTime>
#include<QRegularExpression>
#include<QFileSystemWatcher>
#include<QJsonArray>

class Servis: public QObject
{
    Q_OBJECT
public:
    Servis();
    static QSet<QString> calisanGorevler;
public slots:
   void init();
   void gorevKontrol();
   QTime saniyeToSaat(QString _zaman);
   QString saatToSaniye(QTime _zaman);

   private:

      QTimer *timerGorevBaslama;

     QString localDir;
     QJsonArray taskList;

     QFileSystemWatcher zamanliGorevConfWather;
};

#endif // SERVIS_H
