#include "servis.h"

Servis::Servis()
{
qDebug()<<"servis...";
localDir="/usr/share/zamanligorev/";
QTimer *gorevKontrolTimer = new QTimer();
QObject::connect(gorevKontrolTimer, &QTimer::timeout, [&](){

gorevKontrol();
});
gorevKontrolTimer->start(6000);


}

void Servis::init()
{
 ///  qDebug()<<"init...";
    QStringList listconf=fileToList("zamanligorev.conf");
    ayarlist=listGetList(listconf, "ayar",0);//0 sütun bilgisi olan güne göre listconf listesinden filitreleniyor
}



void Servis::gorevKontrol()
{
    init();//ayarların yüklendiği yer
    int currentsaniye=QTime::currentTime().hour()*60*60+QTime::currentTime().minute()*60+QTime::currentTime().second();

    int currentsaatsaniye=QTime::currentTime().hour()*60*60+QTime::currentTime().minute()*60;
    QString lineayar=listGetLine(ayarlist,QString::number(currentsaatsaniye));
    if(lineayar!="")
    {
        //qDebug()<<"ayar..:"<<lineayar<<task1State<<task2State<<task3State<<task4State<<task5State;
        /***************************komut1*********************************/
        if(lineayar.split("|")[1]=="task1Time"&&task1State==false)
        {
            resetStatus();
            task1State=true;
            QString kmt=QString(listGetLine(ayarlist,"task1Command").split("|")[2]);
           // qDebug()<<"task1Time"<<kmt;
            system(kmt.toStdString().c_str());
        }

        /***************************komut2*********************************/
        if(lineayar.split("|")[1]=="task2Time"&&task2State==false)
        {
            resetStatus();
            task2State=true;

            QString kmt=QString(listGetLine(ayarlist,"task2Command").split("|")[2]);
           //qDebug()<<"task2Time"<<kmt;
            system(kmt.toStdString().c_str());
        }

        /***************************komut3*********************************/
        if(lineayar.split("|")[1]=="task3Time"&&task3State==false)
        {
            resetStatus();
            task3State=true;

            QString kmt=QString(listGetLine(ayarlist,"task3Command").split("|")[2]);
           // qDebug()<<"task3Time"<<kmt;
            system(kmt.toStdString().c_str());
        }

        /***************************komut4*********************************/
        if(lineayar.split("|")[1]=="task4Time"&&task4State==false)
        {
            resetStatus();
            task4State=true;

            QString kmt=QString(listGetLine(ayarlist,"task4Command").split("|")[2]);
           // qDebug()<<"task4Time"<<kmt;
            system(kmt.toStdString().c_str());
        }

        /***************************komut5*********************************/
        if(lineayar.split("|")[1]=="task5Time"&&task5State==false)
        {
            resetStatus();
            task5State=true;

            QString kmt=QString(listGetLine(ayarlist,"task5Command").split("|")[2]);
            //qDebug()<<"task5Time"<<kmt;
            system(kmt.toStdString().c_str());
        }


    }
}


QStringList Servis::listMerge(QStringList list1, QStringList list2, int dataIndex)
{
    for(int i=0;i<list1.count();i++)
    {
        QString line=list1[i];
        if(line!="")
        {

            QStringList lst=line.split("|");
            list2=listRemove(list2,lst[dataIndex]);
        }
    }
    for(int i=0;i<list1.count();i++)
    {
       list2.append(list1[i]);
    }
    return list2;
}
QStringList Servis::listReplace(QStringList list, QString oldData, QString newData, int index)
 {
    QStringList liste;
         QRegularExpression re(oldData);
     for(int i=0;i<list.count();i++)
     {
         if(list[i].contains(re))
         {
             QStringList lst=list[i].split("|");
             lst[index].replace(oldData, newData);
            // qDebug()<<lst;

             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[4]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
            // list.removeAt(i);
             liste.append(ln);
         }
     }
    // qDebug()<<list;
     return liste;
 }
QStringList Servis::listGetList(QStringList list, QString data,int index)
 {
    QStringList liste;
    QRegularExpression re(data);
     for(int i=0;i<list.count();i++)
     {
         if(list[i].contains(re))
         {
            liste.append(list[i]);

         }
     }
    // qDebug()<<list;
     return liste;
 }
QStringList Servis::listRemove(QStringList list,QString data)
 {
         QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(data)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString Servis::listGetLine(QStringList list,QString data)
 {
         QRegularExpression re(data);
     for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
     //qDebug()<<list;
     return "";
 }
QStringList Servis::fileToList(QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    QStringList list;
    for(int i=1;i<=fcc->fileCount();i++)
    {
         QString line=fcc->fileGetLine(i);
         if(line!="")
         {
             line.chop(1);
             QStringList lst=line.split("|");
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[4]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);

             list <<ln;
            // qDebug()<<ln;
             // list <<lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5];

         }
    }
        return list;
 }
void Servis::listToFile(QStringList list, QString filename)
 {
  //  qDebug()<<" listtofile";
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    //QStringList list;
    fcc->fileRemove();
    for(int i=0;i<list.count();i++)
    {
         QString line=list[i];
         if(line!="")
         {
             //line.chop(1);
             QStringList lst=line.split("|");
             //qDebug()<<line;
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[4]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);

             //qDebug()<<ln;
             fcc->fileWrite(ln);
            // fcc->fileWrite(lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5]);

         }

    }
/********************file permission*************************/
   QFile file(localDir+filename);
    if (file.open(QFile::ReadWrite)){
            if(!file.setPermissions(QFileDevice::WriteUser | QFileDevice::ReadUser|QFileDevice::ExeUser|
                                    QFileDevice::WriteOwner | QFileDevice::ReadOwner|QFileDevice::ExeOwner|
                                    QFileDevice::WriteGroup | QFileDevice::ReadGroup|QFileDevice::ExeGroup|
                                    QFileDevice::WriteOther | QFileDevice::ReadOther|QFileDevice::ExeOther)){
                qDebug()<< "Error in permissions";
             }
            file.close();
    }
/***********************************************/
 }

