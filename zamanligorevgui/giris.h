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
#include<QCheckBox>
#include<QProcess>
QWidget *MainWindow::giris()
{
    QWidget *girisPage=new QWidget();
    girisPage->setFixedWidth(500);
   girisPage->setFixedHeight(300);
   auto  screenLabel = new QLabel(girisPage);
    screenLabel->setFixedSize(QSize(200,200));
     screenLabel->setAutoFillBackground(true);
  //  screenbtn->setIcon(QIcon(":/icons/zamanligorev.svg"));
     QPixmap *pixmap=new QPixmap(":/icons/zamanligorev.svg");

     screenLabel->setPixmap(*pixmap);
    screenLabel->setScaledContents(true);

       auto layout = new QGridLayout(girisPage);
    layout->setContentsMargins(0, 0, 0,0);
    layout->setVerticalSpacing(10);
    //layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(new QLabel("Zamanlı Görevler"),0,0,1,1,Qt::AlignHCenter);
    layout->addWidget(screenLabel, 1,0,1,1,Qt::AlignHCenter);
    // girisPage->setStyleSheet("background-color: #acacac");

   // layout->setColumnStretch(6, 255);


    return girisPage;
}
#ifndef GIRIS_H
#define GIRIS_H

#endif // GIRIS_H
