#include "mainwindow.h"

MainWindow::MainWindow(QString dbState,QWidget *parent) : QMainWindow(parent)
{
  QSize size = qApp->screens()[0]->size();
  width = size.width();
  height = size.height();
  this->setGeometry(0,0,width,height);

  m_dbState=dbState;
  //this->showFullScreen();


  interface();

}
void MainWindow::interface()
{

    if(m_dbState.compare("ok"))
        dbErrorShow();

    mainTitle = new QLabel(this);
    mainTitle->setText("Operator,  please Log on");
    mainTitle->setAlignment(Qt::AlignCenter);
    mainTitle->setGeometry(0,height*11/100,width,height*6/100);
    mainTitle->setObjectName("title");

    taskLabel = new QLabel(this);
    taskLabel->setText("Tasks");
    taskLabel->setAlignment(Qt::AlignCenter);
    taskLabel->resize(width*46/100,height*6/100);
    taskLabel->move((width-taskLabel->width())/2,height*37/100);
    taskLabel->setObjectName("taskLabel");

    loginBtn = new QPushButton(this);
    loginBtn->resize(width*80/100,height*8/100);
    loginBtn->move((width-loginBtn->width())/2,height*24/100);
    loginBtn->setText("Login");
    loginBtn->setObjectName("loginBtn");
    connect(loginBtn,SIGNAL(clicked()),this,SLOT(loginPageShow()));

    task_control= new MyComboBox(this);
    task_control->resize(width*61/100,height*8/100);
    task_control->move((width-task_control->width())/2,height*44/100);
    task_control->insertItem(0,"Shipping");
    task_control->insertItem(1,"Inventory");
    task_control->insertItem(2,"Consumption");

    downloadBtn = new QPushButton(this);
    downloadBtn->resize(width*32/100,height*16/100);
    downloadBtn->move((width-downloadBtn->width())/2-downloadBtn->width()*73/100,height*59/100);
    downloadBtn->setText("Download");
    downloadBtn->setObjectName("controlBtn");

    scanBtn = new QPushButton(this);
    scanBtn->resize(width*32/100,height*16/100);
    scanBtn->move((width-scanBtn->width())/2+scanBtn->width()*73/100,height*59/100);
    scanBtn->setText("Scan");
    scanBtn->setObjectName("controlBtn");

    purgeBtn = new QPushButton(this);
    purgeBtn->resize(width*32/100,height*16/100);
    purgeBtn->move((width-purgeBtn->width())/2-purgeBtn->width()*73/100,height*80/100);
    purgeBtn->setText("Purge");
    purgeBtn->setObjectName("controlBtn");

    optionBtn = new QPushButton(this);
    optionBtn->resize(width*32/100,height*16/100);
    optionBtn->move((width-optionBtn->width())/2+optionBtn->width()*73/100,height*80/100);
    optionBtn->setText("Options");
    optionBtn->setObjectName("controlBtn");

}
void MainWindow::loginPageShow()
{
    loginPage =new UserManger(this);
    loginPage->showFullScreen();

}
void MainWindow::dbErrorShow()
{

    QMessageBox::warning(this,"Database Error",m_dbState);
    exit(0);

}
