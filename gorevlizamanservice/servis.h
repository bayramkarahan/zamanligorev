#ifndef SERVIS_H
#define SERVIS_H
#include<QDebug>
#include <QObject>
#include<QTimer>
#include<QTime>
#include<QRegularExpression>
#include<filecrud.h>
class Servis
{
public:
    Servis();
public slots:
   void init();
   void gorevKontrol();

   bool task1State=false;
   bool task2State=false;
   bool task3State=false;
   bool task4State=false;
   bool task5State=false;

   void resetStatus()
       {
       task1State=false;
       task2State=false;
       task3State=false;
       task4State=false;
       task5State=false;
       };
      QTimer *timerGorevBaslama;

      void listToFile(QStringList list, QString filename);
      QStringList fileToList(QString filename);
      QString listGetLine(QStringList list,QString data);
      QStringList listRemove(QStringList list,QString data);
      QStringList listReplace(QStringList list,QString oldData,QString newData,int index);
      QStringList listMerge(QStringList list1, QStringList list2,int dataIndex);
      QStringList listGetList(QStringList list, QString data,int index);
     QString localDir;
      QStringList ayarlist;
};

#endif // SERVIS_H
