#include "mainwindow.h"

MainWindow::MainWindow(QString dbState,QWidget *parent) : QMainWindow(parent)
{
  QSize size = qApp->screens()[0]->size();
  width = size.width();
  height = size.height();
  this->setGeometry(0,0,width,height);

  m_dbState=dbState;
  //this->showFullScreen();

  userKey=0;

  interface();

}
MainWindow::~MainWindow()
{
    mainTimer->stop();
}
void MainWindow::interface()
{

    if(m_dbState.compare("ok"))
        dbErrorShow();

    serverInfoRead();

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
    task_control->setEnabled(0);
    task_control->setObjectName("taskCtrl");

    taskModel = new QStringListModel(this);
    QStringList List;
    List << "Shipping" << "Inventory" << "Consumption";
    taskModel->setStringList(List);

    task_control->setModel(taskModel);

    downloadBtn = new QPushButton(this);
    downloadBtn->resize(width*32/100,height*16/100);
    downloadBtn->move((width-downloadBtn->width())/2-downloadBtn->width()*73/100,height*59/100);
    downloadBtn->setText("Download");
    downloadBtn->setObjectName("controlBtn");
    downloadBtn->setEnabled(0);
    connect(downloadBtn,SIGNAL(clicked()),this,SLOT(downloadFile()));

    scanBtn = new QPushButton(this);
    scanBtn->resize(width*32/100,height*16/100);
    scanBtn->move((width-scanBtn->width())/2+scanBtn->width()*73/100,height*59/100);
    scanBtn->setText("Scan");
    scanBtn->setObjectName("controlBtn");
    scanBtn->setEnabled(0);
    connect(scanBtn,SIGNAL(clicked()),this,SLOT(taskShow()));

    purgeBtn = new QPushButton(this);
    purgeBtn->resize(width*32/100,height*16/100);
    purgeBtn->move((width-purgeBtn->width())/2-purgeBtn->width()*73/100,height*80/100);
    purgeBtn->setText("Purge");
    purgeBtn->setObjectName("controlBtn");
    purgeBtn->setEnabled(0);

    optionBtn = new QPushButton(this);
    optionBtn->resize(width*32/100,height*16/100);
    optionBtn->move((width-optionBtn->width())/2+optionBtn->width()*73/100,height*80/100);
    optionBtn->setText("Options");
    optionBtn->setObjectName("controlBtn");
    optionBtn->setEnabled(0);
    connect(optionBtn,SIGNAL(clicked()),this,SLOT(optionsShow()));

    for (int i=0;i<4;i++) {
        m_permission[i]=false;       
    }
    isCtrlEnable=false;

    mainTimer = new QTimer(this);
    mainTimer->start(300);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(backgroundTransfer()));

}
void MainWindow::backgroundTransfer()
{
    QDir directory("./temp");
    if(directory.exists())
    {
        QStringList files = directory.entryList(QStringList() << "*.csv",QDir::Files);
        foreach(QString filename, files) {

            QFile file_e("./temp/"+filename);
            file_e.open(QFile::ReadOnly);
            QString out = QLatin1String(file_e.readAll());
            QString sharedFile = serverInfo.sharedFolderPath +filename;
            bool state = download(serverInfo.userName,serverInfo.password,serverInfo.ip_address,sharedFile,out);
            if(state)
            {
                file_e.close();
                file_e.remove();
                stateTable.deleteData(filename);
            }
            else {

                file_e.close();
            }

        }
    }
}
void MainWindow::loginPageShow()
{
    loginPage =new UserManger(this);
    loginPage->showFullScreen();

}
void MainWindow::optionsShow()
{
    options = new Options(this);
    options->showFullScreen();
    options->generalOption->batteryInfoShow(sysInfo.batteryLevel,sysInfo.onCharge);
    options->generalOption->sysInfoShow(sysInfo.sysInfo);
    isCtrlEnable=true;

}

void MainWindow::dbErrorShow()
{

    if(QMessageBox::Ok==QMessageBox::warning(this,"Database Error",m_dbState))
                      exit(0);

}

void MainWindow::consumpTaskShow()
{
    consumpTask = new ConsumpTaskMenu(this,userKey);
    consumpTask->permission[0]=m_permission[0];
    if(consumpTask->permission[0])
      consumpTask->createBtn->setEnabled(1);
    consumpTask->permission[1]=m_permission[1];
    consumpTask->permission[2]=m_permission[2];
    consumpTask->showFullScreen();

}
void MainWindow::shippingTaskShow()
{
    shippingTask = new ShippingTaskMenu(this,userKey);
    shippingTask->permission[0]=m_permission[0];
    if(shippingTask->permission[0])
      shippingTask->createBtn->setEnabled(1);
    shippingTask->permission[1]=m_permission[1];
    shippingTask->permission[2]=m_permission[2];
    shippingTask->showFullScreen();

}
void MainWindow::inventoryTaskShow()
 {
     inventoryTask = new InventoryTaskMenu(this,userKey);
     inventoryTask->permission[0]=m_permission[0];
     if(inventoryTask->permission[0])
       inventoryTask->createBtn->setEnabled(1);
     inventoryTask->permission[1]=m_permission[1];
     inventoryTask->permission[2]=m_permission[2];
     inventoryTask->showFullScreen();

 }
void MainWindow::taskShow()
{
    switch (task_control->currentIndex()) {

       case 0:
        shippingTaskShow();
        break;
       case 1:
        inventoryTaskShow();
        break;
       case 2:
        consumpTaskShow();
        break;

    }

}
void MainWindow::androidBatteryStateChanged(int level, bool onCharge)
{
//            QByteArray ba = QString::number(level).toLocal8Bit();
//            const char *c_str2 = ba.data();
//          __android_log_write(ANDROID_LOG_INFO,"you  call-------------->",c_str2);
    sysInfo.batteryLevel = level;
    sysInfo.onCharge = onCharge;

  if(isCtrlEnable)
   {
      options->generalOption->batteryInfoShow(sysInfo.batteryLevel,sysInfo.onCharge);
   }
}
void MainWindow::androidSysteminfo(QString info)
{
    sysInfo.sysInfo = info;
}
void MainWindow::loginSuccess(int key, int permission)
{
     userKey = key;
     task_control->setEnabled(1);

     downloadBtn->setEnabled(0);
     scanBtn->setEnabled(0);
     purgeBtn->setEnabled(0);
     optionBtn->setEnabled(0);

     if((permission >> 7) & 0x1)
     {

        m_permission[3]=true;
     }
     if((permission >> 6) & 0x1)
     {

        m_permission[2]=true;
     }
     if((permission >> 5) & 0x1)
     {
        m_permission[1]=true;
     }
     if((permission >> 4) & 0x1)
     {
        m_permission[0]=true;
     }
     if((permission >> 3) & 0x1)
     {
        optionBtn->setEnabled(1);
     }
     if((permission >> 2) & 0x1)
     {
        downloadBtn->setEnabled(1);
     }
     if((permission >> 1) & 0x1)
     {
        purgeBtn->setEnabled(1);
     }
     if((permission) & 0x1)
     {
        scanBtn->setEnabled(1);
     }

}
void MainWindow::serverInfoRead()
{
    QFile file("./server.txt");
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly))
        {
           QStringList strList;
           QTextStream in(&file);
           while (!in.atEnd())
           {
              QString line = in.readLine();
              strList.append(line);
           }
           QStringList userInfo = strList.at(0).split('/');
           serverInfo.ip_address = userInfo.at(0);
           serverInfo.userName = userInfo.at(1);
           for(int i =2;i< userInfo.length();i++)
             serverInfo.sharedFolderPath += userInfo.at(i) + '/';
          serverInfo.password = strList.at(1);

           file.close();

        }

    }

}
void MainWindow::downloadFile()
{
    jboolean state = false;
    if(serverInfo.ip_address == nullptr)
    {
      QMessageBox::information(this,"Error!","Have no Server!");
      return;
    }
    QString sharedFile = serverInfo.sharedFolderPath;
    QString filename="";
    QString outStream="";

    switch (task_control->currentIndex()) {

        case 0:

            filename = "shippingtask_"+QDateTime::currentDateTime().toString("yy_MM_dd_hh_mm_ss")+".csv";
            sharedFile+=filename;
            outStream=shippingTable.getCSVData();

            break;
        case 1:

            filename = "inventorytask_"+QDateTime::currentDateTime().toString("yy_MM_dd_hh_mm_ss")+".csv";
            sharedFile+=filename;
            outStream=inventoryTable.getCSVData();

             break;
        case 2:

            filename = "consumptask_"+QDateTime::currentDateTime().toString("yy_MM_dd_hh_mm_ss")+".csv";
            sharedFile+=filename;
            outStream=consumpTable.getCSVData();

            break;

    }

    state = download(serverInfo.userName,serverInfo.password,serverInfo.ip_address,sharedFile,outStream);
    downloadConfirm(state,filename,outStream);

}
bool MainWindow::download(QString userName, QString password, QString ip_address, QString sharedFile, QString outStream)
{
    return QAndroidJniObject::callStaticMethod<jboolean>("com/jni/systeminfo/NetworkManager", "downloadFile","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z",
                                                         QAndroidJniObject::fromString(userName).object<jstring>(),
                                                         QAndroidJniObject::fromString(password).object<jstring>(),
                                                         QAndroidJniObject::fromString(ip_address).object<jstring>(),
                                                         QAndroidJniObject::fromString(sharedFile).object<jstring>(),
                                                         QAndroidJniObject::fromString(outStream).object<jstring>());

}
void MainWindow::downloadConfirm(bool state,QString filename,QString out)
{
    if(state)
        QMessageBox::information(this,"Ok","Download Success!");
    else{
        int res = QMessageBox::warning(this,"Download Error!","Download Fail! Please Check SMB State.\n Would do you save downloading state?",QMessageBox::Cancel,QMessageBox::Save);
        if(res==QMessageBox::Save)
        {
            stateTable.insertData(filename,userKey);
            QDir dir;
            dir.mkdir("./temp");
            QFile file("./temp/"+filename);
            if (file.exists())
            {
                file.remove();
            }
            if (file.open(QIODevice::ReadWrite) )
            {
                QTextStream stream(&file);
                stream << out << endl;

            }
            file.close();
        }
        else {
            return;
        }
    }
}
void MainWindow::dataConfirm()
{

   QMessageBox::warning(this,"Download Error!"," Data have no for download!\n Please Check Data State.");

}
