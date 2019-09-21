#include "inventorytaskcreate.h"
#include "usermanger.h"
#include "inventorytask.h"
#include "extern.h"

InventoryTaskCreate::InventoryTaskCreate(int key,QString pri_id, QString title,QString physical,QString location,QString sublocation, QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);
    userKey=key;
    m_pri_id=pri_id;
    wtitle=title;
    m_physical=physical;
    m_location=location;
    m_sublocation=sublocation;
    State=Edit;
    interface();
}
InventoryTaskCreate::InventoryTaskCreate(int key, QString title,QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);
    userKey=key;
    wtitle = title;
    m_physical=nullptr;
    m_location=nullptr;
    m_sublocation=nullptr;
    State=Create;
    interface();
}

void InventoryTaskCreate::interface()
{
    root = doc.documentElement().firstChildElement("InventoryTaskCreate");

    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText(root.firstChildElement("pageTitle").text()+" "+wtitle);
    pageTitle->setObjectName("title");
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);

    phycalLabel = new QLabel(this);
    phycalLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    phycalLabel->setAlignment(Qt::AlignHCenter);
    phycalLabel->setText(root.firstChildElement("phycalLabel").text());
    phycalLabel->setObjectName("taskLabel");
    phycalLabel->resize(width*32/100,height*4/100);
    phycalLabel->move((width-phycalLabel->width())/2-width*29/100,height*22/100);

    QPixmap pixmap("assets:/clear.png");
    phycalEdit = new LineEdit(pixmap,2,this);
    phycalEdit->setPlaceholderText(root.firstChildElement("phycalEdit").text());
    phycalEdit->resize(width*69/100,height*6/100);
    phycalEdit->move((width-phycalEdit->width())/2-width*7/100,height*25/100);
    phycalEdit->setObjectName("inputEdit");
    phycalEdit->installEventFilter(this);
    if(State==Edit)
        phycalEdit->setText(m_physical);

    locationLabel = new QLabel(this);
    locationLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setText(root.firstChildElement("locationLabel").text());
    locationLabel->setObjectName("taskLabel");
    locationLabel->resize(width*29/100,height*4/100);
    locationLabel->move((width-locationLabel->width())/2-width*36/100,height*33/100);

    locationEdit = new LineEdit(pixmap,2,this);
    locationEdit->setPlaceholderText(root.firstChildElement("locationEdit").text());
    locationEdit->resize(width*69/100,height*6/100);
    locationEdit->move((width-locationEdit->width())/2-width*7/100,height*36/100);
    locationEdit->setObjectName("inputEdit");
    locationEdit->installEventFilter(this);
    if(State==Edit)
        locationEdit->setText(m_location);

    physicalBtn = new QPushButton(this);
    physicalBtn->resize(width*15/100,height*6/100);
    physicalBtn->move((width-physicalBtn->width())/2+width*36/100,height*25/100);
    physicalBtn->setText(root.firstChildElement("physicalBtn").text());
    physicalBtn->setObjectName("taskCtrlBtn");
    connect(physicalBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));


    locationBtn = new QPushButton(this);
    locationBtn->resize(width*15/100,height*6/100);
    locationBtn->move((width-locationBtn->width())/2+width*36/100,height*36/100);
    locationBtn->setText(root.firstChildElement("locationBtn").text());
    locationBtn->setObjectName("taskCtrlBtn");
    connect(locationBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));

    sublocationLabel = new QLabel(this);
    sublocationLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sublocationLabel->setAlignment(Qt::AlignHCenter);
    sublocationLabel->setText(root.firstChildElement("sublocationLabel").text());
    sublocationLabel->setObjectName("taskLabel");
    sublocationLabel->resize(width*29/100,height*4/100);
    sublocationLabel->move((width-sublocationLabel->width())/2-width*31/100,height*44/100);

    sublocationEdit = new LineEdit(pixmap,2,this);
    sublocationEdit->setPlaceholderText(root.firstChildElement("sublocationEdit").text());
    sublocationEdit->resize(width*69/100,height*6/100);
    sublocationEdit->move((width-sublocationEdit->width())/2-width*7/100,height*47/100);
    sublocationEdit->setObjectName("inputEdit");
    sublocationEdit->installEventFilter(this);
    if(State==Edit)
        sublocationEdit->setText(m_sublocation);

    sublocationBtn = new QPushButton(this);
    sublocationBtn->resize(width*15/100,height*6/100);
    sublocationBtn->move((width-sublocationBtn->width())/2+width*36/100,height*47/100);
    sublocationBtn->setText(root.firstChildElement("sublocationBtn").text());
    sublocationBtn->setObjectName("taskCtrlBtn");
    connect(sublocationBtn,SIGNAL(clicked()),this,SLOT(keyboardShow()));

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
void InventoryTaskCreate::keyboardShow()
{
    customKeyboard = new CustomKeyBoard(this);
    customKeyboard->setModal(1);
    customKeyboard->show();

    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if(btn==physicalBtn)
    {
        phycalEdit->setFocus(Qt::MouseFocusReason);
        customKeyboard->inputTarget = phycalEdit;
    }
    else if(btn==locationBtn){

        locationEdit->setFocus(Qt::MouseFocusReason);
        customKeyboard->inputTarget = locationEdit;
    }
    else {
        sublocationEdit->setFocus(Qt::MouseFocusReason);
        customKeyboard->inputTarget = sublocationEdit;
    }

}
void InventoryTaskCreate::insertTask()
{

    if(State==Edit)
    {
        if(phycalEdit->text()!=nullptr && locationEdit->text()!=nullptr && sublocationEdit->text()!=nullptr)
         {
            if(!updateData(phycalEdit->text(), locationEdit->text(),sublocationEdit->text(), userKey, m_pri_id))
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

        if(phycalEdit->text()!=nullptr && locationEdit->text()!=nullptr && sublocationEdit->text()!=nullptr)
         {
            if(!insertData(phycalEdit->text(), locationEdit->text(),sublocationEdit->text(), userKey))
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

bool InventoryTaskCreate::insertData(QString phyStr, QString lctStr,QString sublctStr,int key)
{

       QSqlQuery query;
       query.prepare("SELECT physical FROM inventory WHERE physical = :physical");
       query.bindValue(":physical", phyStr);
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
       query.prepare("INSERT INTO inventory (key, physical, location,sub_location,c_time) VALUES (:key, :physical, :location, :sub_location,:c_time)");
              query.bindValue(":key", key);
              query.bindValue(":physical", phyStr);
              query.bindValue(":location", lctStr);
              query.bindValue(":sub_location", sublctStr);
              query.bindValue(":c_time", QDateTime::currentDateTime().toString("MM_dd_hh_mm"));
              if(query.exec())
              {
                  return true;
              }


       return false;

}
bool InventoryTaskCreate::updateData(QString phyStr, QString lctStr,QString sublctStr,int key, QString pri_id)
{
//      QByteArray ba = pri_id.toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);
        QSqlQuery query;
        query.prepare("UPDATE inventory SET key=:key, physical=:physical, location=:location, sub_location=:sub_location, c_time=:c_time WHERE pri_id=:pri_id");
        query.bindValue(":key", key);
        query.bindValue(":physical", phyStr);
        query.bindValue(":location", lctStr);
        query.bindValue(":sub_location", sublctStr);
        query.bindValue(":pri_id", pri_id.toInt());
        query.bindValue(":c_time", QDateTime::currentDateTime().toString("MM_dd_hh_mm"));

        if(query.exec())
        {
           return true;
        }

        return false;
}

