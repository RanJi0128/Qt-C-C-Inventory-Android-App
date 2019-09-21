#include "shippingtaskcreate.h"
#include "usermanger.h"
#include "shippingtask.h"
#include "extern.h"

ShippingTaskCreate::ShippingTaskCreate(int key, QString pri_id,QString title,QString order,QString ship,QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);
    userKey=key;
    m_pri_id=pri_id;
    wtitle=title;
    m_order=order;
    m_ship=ship;
    State=Edit;
    interface();
}
ShippingTaskCreate::ShippingTaskCreate(int key, QString title,QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);
    userKey=key;
    wtitle = title;
    m_order=nullptr;
    m_ship=nullptr;
    State=Create;
    interface();
}

void ShippingTaskCreate::interface()
{
    root = doc.documentElement().firstChildElement("ShippingTaskCreate");

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

    shipLabel = new QLabel(this);
    shipLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    shipLabel->setAlignment(Qt::AlignHCenter);
    shipLabel->setText(root.firstChildElement("shipLabel").text());
    shipLabel->setObjectName("taskLabel");
    shipLabel->resize(width*29/100,height*4/100);
    shipLabel->move((width-shipLabel->width())/2-width*38/100,height*37/100);

    shipEdit = new LineEdit(pixmap,2,this);
    shipEdit->setPlaceholderText(root.firstChildElement("shipEdit").text());
    shipEdit->resize(width*69/100,height*6/100);
    shipEdit->move((width-shipEdit->width())/2-width*7/100,height*42/100);
    shipEdit->setObjectName("inputEdit");
    shipEdit->installEventFilter(this);
    if(State==Edit)
        shipEdit->setText(m_ship);

    orderBtn = new QPushButton(this);
    orderBtn->resize(width*15/100,height*6/100);
    orderBtn->move((width-orderBtn->width())/2+width*36/100,height*30/100);
    orderBtn->setText(root.firstChildElement("orderBtn").text());
    orderBtn->setObjectName("taskCtrlBtn");
    connect(orderBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));

    shipBtn = new QPushButton(this);
    shipBtn->resize(width*15/100,height*6/100);
    shipBtn->move((width-shipBtn->width())/2+width*36/100,height*42/100);
    shipBtn->setText(root.firstChildElement("shipBtn").text());
    shipBtn->setObjectName("taskCtrlBtn");
    connect(shipBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));

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
void ShippingTaskCreate::insertTask()
{

    if(State==Edit)
    {
        if(orderEdit->text()!=nullptr && shipEdit->text()!=nullptr)
         {
            if(!updateData(orderEdit->text(), shipEdit->text(), userKey, m_pri_id))
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

        if(orderEdit->text()!=nullptr && shipEdit->text()!=nullptr)
         {
            if(!insertData(orderEdit->text(), shipEdit->text(), userKey))
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

bool ShippingTaskCreate::insertData(QString oderStr, QString shipStr,int key)
{

       QSqlQuery query;
       query.prepare("SELECT order_val FROM shipping WHERE order_val = :order_val");
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
       query.prepare("INSERT INTO shipping (key, order_val, ship_val, c_time) VALUES (:key, :order_val, :ship_val, :c_time)");
       query.bindValue(":key", key);
       query.bindValue(":order_val", oderStr);
       query.bindValue(":ship_val", shipStr);
       query.bindValue(":c_time", QDateTime::currentDateTime().toString("MM_dd_hh_mm"));
       if(query.exec())
       {
           return true;
       }

       return false;
}
bool ShippingTaskCreate::updateData(QString oderStr, QString shipStr, int key, QString pri_id)
{
//      QByteArray ba = pri_id.toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);
        QSqlQuery query;
        query.prepare("UPDATE shipping SET key=:key, order_val=:order_val, ship_val=:ship_val, c_time=:c_time WHERE pri_id=:pri_id");
        query.bindValue(":key", key);
        query.bindValue(":order_val", oderStr);
        query.bindValue(":ship_val", shipStr);
        query.bindValue(":pri_id", pri_id.toInt());
        query.bindValue(":c_time", QDateTime::currentDateTime().toString("MM_dd_hh_mm"));

        if(query.exec())
        {
           return true;
        }

        return false;
}
void ShippingTaskCreate::keyboardShow()
{
    customKeyboard = new CustomKeyBoard(this);
    customKeyboard->setModal(1);
    customKeyboard->show();

    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(btn==shipBtn)
    {
        shipEdit->setFocus(Qt::MouseFocusReason);
        customKeyboard->inputTarget = shipEdit;
    }
    else {

        orderEdit->setFocus(Qt::MouseFocusReason);
        customKeyboard->inputTarget = orderEdit;
    }

}
