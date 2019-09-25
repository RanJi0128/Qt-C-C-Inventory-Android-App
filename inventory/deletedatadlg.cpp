#include "deletedatadlg.h"
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>
#include "extern.h"

DeleteDataDlg::DeleteDataDlg(QWidget *parent) : QDialog(parent)
{

    root = doc.documentElement().firstChildElement("DeleteDataDlg");

    QSize size = qApp->screens()[0]->size();
    width = size.width()*80/100;
    height = size.height()*25/100;

    this->setGeometry(size.width()*10/100,size.height()*3/8,width,height);

    line=new QLabel(this);
    line->setStyleSheet("QLabel{background-color: rgba(0, 179, 210,0.5);}");
    line->show();

    imgButton = new QToolButton(this);
    QPixmap pixmap("assets:/question.png");
    QPixmap scaled = pixmap.scaled( QSize(width*8/100, height*14/100), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    imgButton->setStyleSheet("QToolButton{border: none;}");
    imgButton->setIcon(QIcon(scaled));
    imgButton->setIconSize(scaled.size());
   // imgButton->setEnabled(0);


    title =new QLabel(root.firstChildElement("title").text(),this);
    title->show();
    title->setFont(QFont("Helvetica",height*8/100));

    text =new QLabel(root.firstChildElement("text").text(),this);
    text->setAlignment(Qt::AlignCenter);
    text->show();
    text->setFont(QFont("Helvetica",height*7/100));

    cb_1 = new QCheckBox(root.firstChildElement("cb_1").text(),this);
    cb_2 = new QCheckBox(root.firstChildElement("cb_2").text(),this);

    cb_1->setFont(QFont("Helvetica",height*6/100));   
    cb_2->setFont(QFont("Helvetica",height*6/100));

    QString style = "QCheckBox::indicator { width: %1px; height: %2px;}";
    cb_1->setStyleSheet(style.arg(width*4/100).arg(height*8/100));
    cb_2->setStyleSheet(style.arg(width*4/100).arg(height*8/100));

    okBtn = new QPushButton(root.firstChildElement("okBtn").text(),this);    
    okBtn->setFont(QFont("Helvetica",height*7/100));
    connect(okBtn,SIGNAL(clicked()),this,SLOT(okSlot()));

    cancelBtn = new QPushButton(root.firstChildElement("cancelBtn").text(),this);    
    cancelBtn->setFont(QFont("Helvetica",height*7/100));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    objectGeometry();

}
void DeleteDataDlg::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    width = size.width();
    height = size.height();

    objectGeometry();
}
void DeleteDataDlg::objectGeometry()
{
    line->setGeometry(0,height*26/100,width,height*1/100);
    title->setGeometry(width*13/100,height*9/100,width*43/100,height*10/100);
    imgButton->move(width*2/100,height*8/100);
    text->setGeometry(width*3/100,height*34/100,width*94/100,height*9/100);
    cb_1->setGeometry(width*6/100,height*52/100,width*57/100,height*8/100);
    cb_2->setGeometry(width*6/100,height*68/100,width*57/100,height*8/100);
    okBtn->setGeometry(width*14/100,height*83/100,width*23/100,height*15/100);
    cancelBtn->setGeometry(width*60/100,height*83/100,width*23/100,height*15/100);

}
void DeleteDataDlg::keyPressEvent(QKeyEvent */*event*/)
{
//    switch (event->key())
//    {
//        case Qt::Key_Backspace:
//          break;
//        default:
//        QWidget::keyPressEvent(event);
//    }
}
void DeleteDataDlg::okSlot()
{
    if(cb_1->isChecked() && !cb_2->isChecked())
        emit allDelete(1);
    else if(!cb_1->isChecked() && cb_2->isChecked()){

        emit downloadDelete(2);
    }
    else if(cb_1->isChecked() && cb_2->isChecked()){

        emit downloadAllDelete(3);
    }
    else {
        emit oneDelete(0);
    }
    this->close();
}
