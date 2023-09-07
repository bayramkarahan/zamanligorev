#include <QCoreApplication>
#include<servis.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Servis *s=new Servis();
    return a.exec();
}
