#include "consumptaskcreate.h"
#include "usermanger.h"
#include "consumptask.h"

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
    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText("Consumption "+wtitle);
    pageTitle->setObjectName("title");
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);

    orderLabel = new QLabel(this);
    orderLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    orderLabel->setAlignment(Qt::AlignHCenter);
    orderLabel->setText("WorkOrder");
    orderLabel->setObjectName("taskLabel");
    orderLabel->resize(width*29/100,height*4/100);
    orderLabel->move((width-orderLabel->width())/2-width*30/100,height*26/100);

    QPixmap pixmap("assets:/clear.png");
    orderEdit = new LineEdit(pixmap,2,this);
    orderEdit->setPlaceholderText("Order Input");
    orderEdit->resize(width*69/100,height*6/100);
    orderEdit->move((width-orderEdit->width())/2-width*7/100,height*30/100);
    orderEdit->setObjectName("inputEdit");
    orderEdit->installEventFilter(this);
    if(State==Edit)
        orderEdit->setText(m_order);

    locationLabel = new QLabel(this);
    locationLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setText("Location");
    locationLabel->setObjectName("taskLabel");
    locationLabel->resize(width*29/100,height*4/100);
    locationLabel->move((width-locationLabel->width())/2-width*30/100,height*37/100);

    locationEdit = new LineEdit(pixmap,2,this);
    locationEdit->setPlaceholderText("Location Input");
    locationEdit->resize(width*69/100,height*6/100);
    locationEdit->move((width-locationEdit->width())/2-width*7/100,height*42/100);
    locationEdit->setObjectName("inputEdit");
    locationEdit->installEventFilter(this);
    if(State==Edit)
        locationEdit->setText(m_location);

    orderBtn = new QPushButton(this);
    orderBtn->resize(width*15/100,height*6/100);
    orderBtn->move((width-orderBtn->width())/2+width*36/100,height*30/100);
    orderBtn->setText("ABC");
    orderBtn->setObjectName("taskCtrlBtn");
    connect(orderBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));

    locationBtn = new QPushButton(this);
    locationBtn->resize(width*15/100,height*6/100);
    locationBtn->move((width-locationBtn->width())/2+width*36/100,height*42/100);
    locationBtn->setText("ABC");
    locationBtn->setObjectName("taskCtrlBtn");
    connect(locationBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));

    cancelBtn = new QPushButton(this);
    cancelBtn->resize(width*26/100,height*6/100);
    cancelBtn->move((width-cancelBtn->width())/2-width*25/100,height*76/100);
    cancelBtn->setText("Cancel");
    cancelBtn->setObjectName("taskCtrlBtn");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    continueBt = new QPushButton(this);
    continueBt->resize(width*26/100,height*6/100);
    continueBt->move((width-cancelBtn->width())/2+width*27/100,height*76/100);
    continueBt->setText("Continue");
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
                QMessageBox::warning(this,"Input Error","Update failed!");
                return;
             }
        }
        else {
                QMessageBox::warning(this,"Input Error","Please Input data correctly!");
                return;
        }

    }
    else if(State==Create) {

        if(orderEdit->text()!=nullptr && locationEdit->text()!=nullptr)
         {
            if(!insertData(orderEdit->text(), locationEdit->text(), userKey))
            {
                QMessageBox::warning(this,"Input Error","Order number exists already!");
                return;
            }
         }
        else {
            QMessageBox::warning(this,"Input Error","Please Input data correctly!");
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
       query.prepare("INSERT INTO consump (key, order_val, location) VALUES (:key, :order_val, :location)");
       query.bindValue(":key", key);
       query.bindValue(":order_val", oderStr);
       query.bindValue(":location", lctStr);
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
        query.prepare("UPDATE consump SET key=:key, order_val=:order_val, location=:location WHERE pri_id=:pri_id");
        query.bindValue(":key", key);
        query.bindValue(":order_val", oderStr);
        query.bindValue(":location", lctStr);
        query.bindValue(":pri_id", pri_id.toInt());

        if(query.exec())
        {
           return true;
        }

        return false;
}

