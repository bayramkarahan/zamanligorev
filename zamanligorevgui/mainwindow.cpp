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
#include "mainwindow.h"
#include<QTabWidget>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include<QFile>
#include<QFileDialog>
#include<QRegularExpression>
#include<QTimeEdit>
#include<QDate>
#include<QTimer>
#include<QTime>
#include<QMessageBox>
#include<giris.h>
#include<hakkinda.h>
#include<QApplication>
#include<QDesktopWidget>
#include<QMenu>
#include<QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
 {
      localDir="/usr/share/zamanligorev/";
      //localDir="./";
   // wl=new QWidgetAction(this);
    timer1.setSingleShot(true);
    connect(&timer1, SIGNAL(timeout()), &loop, SLOT(quit()));
  //  connect(this, SIGNAL(replayReceived()), &loop, SLOT(quit()));
    auto appIcon = QIcon(":/icons/zamanligorev.svg");
    QProcess process;
    process.start("/bin/bash", {"-c", "dpkg -s zamanligorev | grep -i '^Version:' | awk '{print $2}'"});
    process.waitForFinished();

    QString version = QString::fromUtf8(process.readAll()).trimmed();
    setWindowTitle("zamanligorev " + version);


     this->setWindowIcon(appIcon);


      /**********************form ayarları yapıldı***********************/
      QSize screenSize = qApp->screens()[0]->size();
     // qDebug()<<screenSize.width()/65<<screenSize.height()/35;
      boy=screenSize.width()/65;
     en=boy;
      setFixedWidth(en*32);
      setFixedHeight(en*20);
      QRect screenGeometry = QApplication::desktop()->screenGeometry();
      int x = (screenGeometry.width()/2 - this->width()/2);
      int y = (screenGeometry.height() - this->height()) / 2;
      this->move(x, y);
      this->setStyleSheet("background-color: #dfdfdf;");

      tw=new QTabWidget(this);
      tw->resize(this->width(),this->height());
      /*************************SZS ekranı*******************************************/
     // qDebug()<<"ekranı göster";
      QFont ff( "Arial", 7.5, QFont::Normal);
      tw->setFont(ff);
      tw->clear();
      AyarWidget *gorev = new AyarWidget(localDir, boy, this);
     // gorev->show();

     tw->addTab(giris(),"Giriş");
     tw->addTab(gorev,"Görevler");
     tw->addTab(hakkinda(),"Hakkında");
     // this->showNormal();

}



MainWindow::~MainWindow()
{
  //  delete ui;
}

QTime MainWindow::saniyeToSaat(QString _zaman)
{
     QTime zm(0,0,0);
      zm=zm.addSecs(_zaman.toInt());
      return zm;
}
QString MainWindow::saatToSaniye(QTime _zaman)
{
   int zmm=_zaman.hour()*60*60+_zaman.minute()*60+_zaman.second();
   return QString::number(zmm);
}

void  MainWindow::gizle()
{
    //hide();
   // qDebug()<<"deded";
    QWidget::hide();
    timergizle->stop();

}


void  MainWindow::about()
{
    QSize screenSize = qApp->screens()[0]->size();
   // qDebug()<<screenSize.width()/65<<screenSize.height()/35;

    QWidget *hk=hakkinda();

    hk->show();
    hk->move(screenSize.width()/2-hk->width()/2,screenSize.height()/2-hk->height()/2);
     hk->setWindowTitle("Hakkında");
     auto appIcon = QIcon(":/icons/zamanligorev.svg");
     hk->setWindowIcon(appIcon);
}
void  MainWindow::widgetShow()
{
    qDebug()<<"ekranı göster";
    QFont ff( "Arial", 7.5, QFont::Normal);
    tw->setFont(ff);
    tw->clear();
    AyarWidget *gorev = new AyarWidget(localDir, boy, this);
    //gorev->show();
    tw->addTab(giris(),"Giriş");
    tw->addTab(gorev,"Görevler");
    tw->addTab(hakkinda(),"Hakkında");
    this->showNormal();

 }
QMenu* MainWindow::createMenu()
{
  // App can exit via Quit menu
 /* auto quitAction = new QAction("&Kapat", this);
  connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
  auto ayarAction = new QAction("&Ayarlar", this);
  connect(ayarAction, &QAction::triggered, qApp, gizle());
*/
    auto minimizeAction = new QAction(tr("Gi&zle"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);



     // auto  aboutAction = new QAction(tr("Hakkında"), this);
     //  connect( aboutAction, SIGNAL(triggered()), this, SLOT(about()));

   /* auto maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);
*/
    auto restoreAction = new QAction(tr("&Ayarlar"), this);
  //  connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);
     connect( restoreAction, SIGNAL(triggered()), this, SLOT(widgetShow()));

    auto quitAction = new QAction(tr("&Kapat"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    auto menu = new QMenu(this);
    //menu->addAction(quitAction)


    menu->addAction(minimizeAction);
    //menu->addAction(maximizeAction);
    menu->addAction(restoreAction);
    menu->addSeparator();


    menu->addSeparator();
   /// menu->addAction(aboutAction);

    menu->addAction(quitAction);

   // trayIcon = new QSystemTrayIcon(this);
    //trayIcon->setContextMenu(trayIconMenu);

    //;

  return menu;
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
  switch (reason_) {
  case QSystemTrayIcon::Trigger:
   // this->trayIcon->showMessage("zamanligörev", "zamanligörev Sistemi!");
      widgetShow();
    break;
  default:
    ;
  }
}

void MainWindow::WidgetClosed()
{
    //QWidget::hide();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit WidgetClosed();
   //  event->ignore();

}

