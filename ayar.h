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

bool MainWindow::dosyaVarmi(QString dosya)
{
    FileCrud *filecdr=new FileCrud();
    filecdr->dosya=localDir+dosya;

    if (!filecdr->fileExists())
    {
        QMessageBox msgError;
        msgError.setText("Ayarları Kaydetmeden İşlem Yapamazsınız..!");
        msgError.setIcon(QMessageBox::Critical);
        msgError.setWindowTitle("Uyarı!");
        msgError.exec();
        return false;
    }
    else return true;
}
QWidget *MainWindow::ayar()
{
 //   qDebug()<<"ayar";
 //   init();

    QWidget *ayarPage=new QWidget();
    ayarPage->setFixedWidth(500);
    ayarPage->setFixedHeight(400);
/***********************task1*************************************************/
QTimeEdit *task1TimeEdit=new QTimeEdit;
 if(listGetLine(ayarlist,"task1Time")!="")
    task1TimeEdit->setTime(saniyeToSaat(listGetLine(ayarlist,"task1Time").split("|")[2]));

 QLineEdit *task1CommandEdit=new QLineEdit;
task1CommandEdit->setText("");
if(listGetLine(ayarlist,"task1Command")!="")
    if(listGetLine(ayarlist,"task1Command").split("|")[2]!="")task1CommandEdit->setText(listGetLine(ayarlist,"task1Command").split("|")[2]);
/************************************************************************/

/***********************task2*************************************************/
QTimeEdit *task2TimeEdit=new QTimeEdit;
 if(listGetLine(ayarlist,"task2Time")!="")
    task2TimeEdit->setTime(saniyeToSaat(listGetLine(ayarlist,"task2Time").split("|")[2]));

 QLineEdit *task2CommandEdit=new QLineEdit;
task2CommandEdit->setText("");
if(listGetLine(ayarlist,"task2Command")!="")
    if(listGetLine(ayarlist,"task2Command").split("|")[2]!="")task2CommandEdit->setText(listGetLine(ayarlist,"task2Command").split("|")[2]);
/************************************************************************/
/***********************task3*************************************************/
QTimeEdit *task3TimeEdit=new QTimeEdit;
 if(listGetLine(ayarlist,"task3Time")!="")
    task3TimeEdit->setTime(saniyeToSaat(listGetLine(ayarlist,"task3Time").split("|")[2]));

 QLineEdit *task3CommandEdit=new QLineEdit;
task3CommandEdit->setText("");
if(listGetLine(ayarlist,"task3Command")!="")
    if(listGetLine(ayarlist,"task3Command").split("|")[2]!="")task3CommandEdit->setText(listGetLine(ayarlist,"task3Command").split("|")[2]);
/************************************************************************/

/***********************task4*************************************************/
QTimeEdit *task4TimeEdit=new QTimeEdit;
 if(listGetLine(ayarlist,"task4Time")!="")
    task4TimeEdit->setTime(saniyeToSaat(listGetLine(ayarlist,"task4Time").split("|")[2]));

 QLineEdit *task4CommandEdit=new QLineEdit;
task4CommandEdit->setText("");
if(listGetLine(ayarlist,"task4Command")!="")
    if(listGetLine(ayarlist,"task4Command").split("|")[2]!="")task4CommandEdit->setText(listGetLine(ayarlist,"task4Command").split("|")[2]);
/************************************************************************/

/***********************task5*************************************************/
QTimeEdit *task5TimeEdit=new QTimeEdit;
 if(listGetLine(ayarlist,"task5Time")!="")
    task5TimeEdit->setTime(saniyeToSaat(listGetLine(ayarlist,"task5Time").split("|")[2]));

 QLineEdit *task5CommandEdit=new QLineEdit;
task5CommandEdit->setText("");
if(listGetLine(ayarlist,"task5Command")!="")
    if(listGetLine(ayarlist,"task5Command").split("|")[2]!="")task5CommandEdit->setText(listGetLine(ayarlist,"task5Command").split("|")[2]);
/************************************************************************/
    QPushButton *ayarKaydetButton= new QPushButton;
    //ayarKaydetButton->setFixedSize(150, 30);
   // ayarKaydetButton->setIconSize(QSize(150,30));
    ayarKaydetButton->setText("Ayarları Kaydet");
    ayarKaydetButton->setStyleSheet("Text-align:Center");
  //  ayarKaydetButton->setFlat(true);
   // ayarKaydetButton->setIcon(QIcon(":icons/saveprofile.png"));

    connect(ayarKaydetButton, &QPushButton::clicked, [=]() {
         QStringList _ayarlist;

         _ayarlist.append("ayar|task1Time|"+saatToSaniye(task1TimeEdit->time()));
        _ayarlist.append("ayar|task1Command|"+task1CommandEdit->text());

        _ayarlist.append("ayar|task2Time|"+saatToSaniye(task2TimeEdit->time()));
       _ayarlist.append("ayar|task2Command|"+task2CommandEdit->text());

       _ayarlist.append("ayar|task3Time|"+saatToSaniye(task3TimeEdit->time()));
      _ayarlist.append("ayar|task3Command|"+task3CommandEdit->text());

      _ayarlist.append("ayar|task4Time|"+saatToSaniye(task4TimeEdit->time()));
     _ayarlist.append("ayar|task4Command|"+task4CommandEdit->text());

     _ayarlist.append("ayar|task5Time|"+saatToSaniye(task5TimeEdit->time()));
    _ayarlist.append("ayar|task5Command|"+task5CommandEdit->text());

        QStringList listconf=fileToList("zamanligorev.conf");
        listconf=listMerge(_ayarlist,listconf,0);
        listToFile(listconf,"zamanligorev.conf");
        ayarlist=listGetList(fileToList("zamanligorev.conf"), "ayar",0);//0 sütun bilgisi olan güne göre list
        init();
        tw->widget(1)->deleteLater();
        tw->widget(2)->deleteLater();
        tw->addTab(ayar(),"Ayarlar");
       //tw->addTab(saatpzrts(1),"Pzrts");
        tw->addTab(hakkinda(),"Hakkında");



 });


    auto layout = new QGridLayout(ayarPage);
    //layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(5);
   // layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(new QLabel("1. Görev"),1,0,1,1);
    layout->addWidget(task1TimeEdit, 1,1,1,1);
    layout->addWidget(task1CommandEdit, 1,2,1,1);

    layout->addWidget(new QLabel("2. Görev"),2,0,1,1);
    layout->addWidget(task2TimeEdit, 2,1,1,1);
    layout->addWidget(task2CommandEdit, 2,2,1,1);

    layout->addWidget(new QLabel("3. Görev"),3,0,1,1);
    layout->addWidget(task3TimeEdit, 3,1,1,1);
    layout->addWidget(task3CommandEdit, 3,2,1,1);

    layout->addWidget(new QLabel("4. Görev"),4,0,1,1);
    layout->addWidget(task4TimeEdit, 4,1,1,1);
    layout->addWidget(task4CommandEdit, 4,2,1,1);


    layout->addWidget(new QLabel("5. Görev"),5,0,1,1);
    layout->addWidget(task5TimeEdit, 5,1,1,1);
    layout->addWidget(task5CommandEdit, 5,2,1,1);



    layout->addWidget(ayarKaydetButton,7,0,1,3);

//layout->setColumnStretch(6, 255);

    return ayarPage;
}
#endif // AYAR_H
