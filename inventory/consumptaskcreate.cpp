#include "consumptaskcreate.h"
#include "usermanger.h"
#include "consumptask.h"
#include "extern.h"

ConsumpTaskCreate::ConsumpTaskCreate(int key, QString pri_id,QString title,QString order,QString location,QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);
    userKey=key;
    m_pri_id=pri_id;
    wtitle=title;
    m_order=order;
    m_location=location;
    State=Edit;
    interface();
}
ConsumpTaskCreate::ConsumpTaskCreate(int key, QString title,QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);
    userKey=key;
    wtitle = title;
    m_order=nullptr;
    m_location=nullptr;
    State=Create;
    interface();
}

void ConsumpTaskCreate::interface()
{
    root = doc.documentElement().firstChildElement("ConsumpTaskCreate");

    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText(root.firstChildElement("pageTitle").text()+" "+wtitle);
    pageTitle->setObjectName("title");
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);

    orderLabel = new QLabel(this);
    orderLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    orderLabel->setAlignment(Qt::AlignHCenter);
    orderLabel->setText(root.firstChildElement("orderLabel").text());
    orderLabel->setObjectName("taskLabel");
    orderLabel->resize(width*29/100,height*4/100);
    orderLabel->move((width-orderLabel->width())/2-width*30/100,height*26/100);

    QPixmap pixmap("assets:/clear.png");
    orderEdit = new LineEdit(pixmap,2,this);
    orderEdit->setPlaceholderText(root.firstChildElement("orderEdit").text());
    orderEdit->resize(width*69/100,height*6/100);
    orderEdit->move((width-orderEdit->width())/2-width*7/100,height*30/100);
    orderEdit->setObjectName("inputEdit");
    orderEdit->installEventFilter(this);
    if(State==Edit)
        orderEdit->setText(m_order);

    locationLabel = new QLabel(this);
    locationLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setText(root.firstChildElement("locationLabel").text());
    locationLabel->setObjectName("taskLabel");
    locationLabel->resize(width*29/100,height*4/100);
    locationLabel->move((width-locationLabel->width())/2-width*30/100,height*37/100);

    locationEdit = new LineEdit(pixmap,2,this);
    locationEdit->setPlaceholderText(root.firstChildElement("locationEdit").text());
    locationEdit->resize(width*69/100,height*6/100);
    locationEdit->move((width-locationEdit->width())/2-width*7/100,height*42/100);
    locationEdit->setObjectName("inputEdit");
    locationEdit->installEventFilter(this);
    if(State==Edit)
        locationEdit->setText(m_location);

    orderBtn = new QPushButton(this);
    orderBtn->resize(width*15/100,height*6/100);
    orderBtn->move((width-orderBtn->width())/2+width*36/100,height*30/100);
    orderBtn->setText(root.firstChildElement("orderBtn").text());
    orderBtn->setObjectName("taskCtrlBtn");
    connect(orderBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));

    locationBtn = new QPushButton(this);
    locationBtn->resize(width*15/100,height*6/100);
    locationBtn->move((width-locationBtn->width())/2+width*36/100,height*42/100);
    locationBtn->setText(root.firstChildElement("locationBtn").text());
    locationBtn->setObjectName("taskCtrlBtn");
    connect(locationBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));

    cancelBtn = new QPushButton(this);
    cancelBtn->resize(width*26/100,height*6/100);
    cancelBtn->move((width-cancelBtn->width())/2-width*25/100,height*76/100);
    cancelBtn->setText(root.firstChildElement("cancelBtn").text());
    cancelBtn->setObjectName("taskCtrlBtn");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    continueBt = new QPushButton(this);
    continueBt->resize(width*26/100,height*6/100);
    continueBt->move((width-cancelBtn->width())/2+width*27/100,height*76/100);
    continueBt->setText(root.firstChildElement("continueBt").text());
    continueBt->setObjectName("taskCtrlBtn");
    connect(continueBt,SIGNAL(clicked()),this,SLOT(insertTask()));


}
void ConsumpTaskCreate::keyboardShow()
{
    customKeyboard = new CustomKeyBoard(this);
    customKeyboard->setModal(1);
    customKeyboard->show();

    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(btn==locationBtn)
    {
        locationEdit->setFocus(Qt::MouseFocusReason);
        customKeyboard->inputTarget = locationEdit;
    }
    else {

        orderEdit->setFocus(Qt::MouseFocusReason);
        customKeyboard->inputTarget = orderEdit;
    }

}
void ConsumpTaskCreate::insertTask()
{

    if(State==Edit)
    {
        if(orderEdit->text()!=nullptr && locationEdit->text()!=nullptr)
         {
            if(!updateData(orderEdit->text(), locationEdit->text(), userKey, m_pri_id))
             {
                QMessageBox::warning(this,root.firstChildElement("errorTitle").text(),root.firstChildElement("error_1").text());
                return;
             }
        }
        else {
                QMessageBox::warning(this,root.firstChildElement("errorTitle").text(),root.firstChildElement("error_2").text());
                return;
        }

    }
    else if(State==Create) {

        if(orderEdit->text()!=nullptr && locationEdit->text()!=nullptr)
         {
            if(!insertData(orderEdit->text(), locationEdit->text(), userKey))
            {
                QMessageBox::warning(this,root.firstChildElement("errorTitle").text(),root.firstChildElement("error_3").text());
                return;
            }
         }
        else {
            QMessageBox::warning(this,root.firstChildElement("errorTitle").text(),root.firstChildElement("error_4").text());
            return;
        }
    }
    table->getReadAllData(userKey);
    this->close();

}

bool ConsumpTaskCreate::insertData(QString oderStr, QString lctStr,int key)
{

       QSqlQuery query;
       query.prepare("SELECT order_val FROM consump WHERE order_val = :order_val");
       query.bindValue(":order_val", oderStr);
       if(query.exec())
       {
           if(query.first())
           {
             return false;
           }

       }
       else {
         return false;
       }

       query.prepare("INSERT INTO consump (key, order_val, location,c_time,m_time) VALUES (:key, :order_val, :location,:c_time,:m_time)");
       query.bindValue(":key", key);
       query.bindValue(":order_val", oderStr);
       query.bindValue(":location", lctStr);
       query.bindValue(":c_time", QDateTime::currentDateTime().toString("MM_dd_hh_mm"));
       query.bindValue(":m_time", QDateTime::currentDateTime().toString("MM_dd_hh_mm"));
       if(query.exec())
       {
           return true;
       }

       return false;
}
bool ConsumpTaskCreate::updateData(QString oderStr, QString lctStr, int key, QString pri_id)
{
//      QByteArray ba = pri_id.toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);
        QSqlQuery query;
        query.prepare("UPDATE consump SET key=:key, order_val=:order_val, location=:location, m_time=:m_time WHERE pri_id=:pri_id");
        query.bindValue(":key", key);
        query.bindValue(":order_val", oderStr);
        query.bindValue(":location", lctStr);
        query.bindValue(":pri_id", pri_id.toInt());
        query.bindValue(":m_time", QDateTime::currentDateTime().toString("MM_dd_hh_mm"));

        if(query.exec())
        {
           return true;
        }

        return false;
}

