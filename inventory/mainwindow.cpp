#include "mainwindow.h"
#include "extern.h"

QDomDocument doc;

MainWindow::MainWindow(int dbState,QWidget *parent) : QMainWindow(parent)
{
  QSize size = qApp->screens()[0]->size();
  width = size.width();
  height = size.height();
  this->setGeometry(0,0,width,height);
  this->setObjectName("mainwindow");
  m_dbState=dbState;

  userKey=0;
  logoffTime=5;
  fullScreenFlag=true;

  loadXml();
  interface();


}
MainWindow::~MainWindow()
{
    mainTimer->stop();
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    width = size.width();
    height = size.height();

    objectGeometry();
}
void MainWindow::loadXml()
{
    QFile inFile("assets:/en.xml");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Error!","No Xml!");
        return;
    }
    QXmlStreamReader xmlReader(&inFile);
    doc.setContent(&inFile);

}
void MainWindow::interface()
{

    if(m_dbState)
        dbErrorShow();

    serverInfoRead();
    logoffTimeRead();

    root = doc.documentElement().firstChildElement("main");

    mainTitle = new QLabel(this);    
    mainTitle->setText(root.firstChildElement("mainTitle").text());
    mainTitle->setAlignment(Qt::AlignCenter);   
    mainTitle->setObjectName("title");

    taskLabel = new QLabel(this);
    taskLabel->setText(root.firstChildElement("taskLabel").text());
    taskLabel->setAlignment(Qt::AlignCenter);
    taskLabel->setObjectName("taskLabel");

    loginBtn = new QPushButton(this);
    loginBtn->setText(root.firstChildElement("loginBtn").text());
    loginBtn->setObjectName("loginBtn");
    connect(loginBtn,SIGNAL(clicked()),this,SLOT(loginPageShow()));

    task_control= new MyComboBox(this);    
    task_control->setEnabled(0);
    task_control->setObjectName("taskCtrl");

    taskModel = new QStringListModel(this);
    QStringList List;
    List << root.firstChildElement("taskModel_1").text() << root.firstChildElement("taskModel_2").text() << root.firstChildElement("taskModel_3").text();
    taskModel->setStringList(List);

    task_control->setModel(taskModel);

    downloadBtn = new QPushButton(this);  
    downloadBtn->setText(root.firstChildElement("downloadBtn").text());
    downloadBtn->setObjectName("controlBtn");
    downloadBtn->setEnabled(0);
    connect(downloadBtn,SIGNAL(clicked()),this,SLOT(downloadFile()));

    scanBtn = new QPushButton(this);
    scanBtn->setText(root.firstChildElement("scanBtn").text());
    scanBtn->setObjectName("controlBtn");
    scanBtn->setEnabled(0);
    connect(scanBtn,SIGNAL(clicked()),this,SLOT(taskShow()));

    purgeBtn = new QPushButton(this);    
    purgeBtn->setText(root.firstChildElement("purgeBtn").text());
    purgeBtn->setObjectName("controlBtn");
    purgeBtn->setEnabled(0);
    connect(purgeBtn,SIGNAL(clicked()),this,SLOT(dataDelDlg()));

    optionBtn = new QPushButton(this);    
    optionBtn->setText(root.firstChildElement("optionBtn").text());
    optionBtn->setObjectName("controlBtn");
    optionBtn->setEnabled(0);
    connect(optionBtn,SIGNAL(clicked()),this,SLOT(optionsShow()));

    objectGeometry();
    for (int i=0;i<4;i++) {
        m_permission[i]=false;       
    }
    isCtrlEnable=false;

    mainTimer = new QTimer(this);
    mainTimer->start(300);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(backgroundTransfer()));

}
void MainWindow::objectGeometry()
{
    mainTitle->setGeometry(0,height*11/100,width,height*6/100);

    taskLabel->resize(width*46/100,height*6/100);
    taskLabel->move((width-taskLabel->width())/2,height*37/100);

    loginBtn->resize(width*80/100,height*8/100);
    loginBtn->move((width-loginBtn->width())/2,height*24/100);

    task_control->resize(width*61/100,height*8/100);
    task_control->move((width-task_control->width())/2,height*44/100);

    downloadBtn->resize(width*32/100,height*16/100);
    downloadBtn->move((width-downloadBtn->width())/2-downloadBtn->width()*73/100,height*59/100);

    scanBtn->resize(width*32/100,height*16/100);
    scanBtn->move((width-scanBtn->width())/2+scanBtn->width()*73/100,height*59/100);

    purgeBtn->resize(width*32/100,height*16/100);
    purgeBtn->move((width-purgeBtn->width())/2-purgeBtn->width()*73/100,height*80/100);

    optionBtn->resize(width*32/100,height*16/100);
    optionBtn->move((width-optionBtn->width())/2+optionBtn->width()*73/100,height*80/100);


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
    if(fullScreenFlag)
     loginPage->showFullScreen();
    else {
       loginPage->show();
    }

}
void MainWindow::optionsShow()
{
    options = new Options(this);
    if(fullScreenFlag)
      options->showFullScreen();
    else {
       options->show();
    }
    options->generalOption->batteryInfoShow(sysInfo.batteryLevel,sysInfo.onCharge);
    options->generalOption->sysInfoShow(sysInfo.sysInfo);
    isCtrlEnable=true;

}

void MainWindow::dbErrorShow()
{

   if(m_dbState==1)
     {
        QMessageBox::warning(this,"Warning!","No Database!");
     }
    else if(m_dbState==2){
        QMessageBox::warning(this,"Warning!","Can't Open Database!");
    }
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
    if(fullScreenFlag)
      consumpTask->showFullScreen();
    else {
        consumpTask->show();
    }

}
void MainWindow::shippingTaskShow()
{
    shippingTask = new ShippingTaskMenu(this,userKey);
    shippingTask->permission[0]=m_permission[0];
    if(shippingTask->permission[0])
      shippingTask->createBtn->setEnabled(1);
    shippingTask->permission[1]=m_permission[1];
    shippingTask->permission[2]=m_permission[2];
   if(fullScreenFlag)
    shippingTask->showFullScreen();
   else {
       shippingTask->show();
   }

}
void MainWindow::inventoryTaskShow()
 {
     inventoryTask = new InventoryTaskMenu(this,userKey);
     inventoryTask->permission[0]=m_permission[0];
     if(inventoryTask->permission[0])
       inventoryTask->createBtn->setEnabled(1);
     inventoryTask->permission[1]=m_permission[1];
     inventoryTask->permission[2]=m_permission[2];
    if(fullScreenFlag)
     inventoryTask->showFullScreen();
    else {
        inventoryTask->show();
    }

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
void MainWindow::appLogoff()
{

     QWidget *widget = QApplication::activeWindow();
     if(widget->objectName().compare("mainwindow"))
     {
         widget->close();
     }
     task_control->setCurrentIndex(0);
     task_control->setEnabled(0);
     downloadBtn->setEnabled(0);
     scanBtn->setEnabled(0);
     purgeBtn->setEnabled(0);
     optionBtn->setEnabled(0);
     isCtrlEnable=false;


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
           serverInfo.init();
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
void MainWindow::logoffTimeRead()
{
    QFile file("./logoffTime.txt");
    if(file.exists())
    {
        file.open(QFile::ReadOnly);
        logoffTime =file.readAll().toInt();
        file.close();
    }
    QAndroidJniObject::callStaticMethod<void>("com/jni/systeminfo/AppActivity", "sysLogoffTime","(I)V",logoffTime);
}
void MainWindow::downloadFile()
{

    if(serverInfo.ip_address == nullptr)
    {
      QMessageBox::information(this,root.firstChildElement("serverErrorTitle").text(),root.firstChildElement("serverErrorText").text());
      return;
    }
    int res = QMessageBox::information(this,root.firstChildElement("downloadConfirmTitle").text(),root.firstChildElement("downloadConfirmText").text(),QMessageBox::Cancel,QMessageBox::Ok);
    if(res==QMessageBox::Ok)
    {
        for(int i =0;i<3;i++)
        {
            downloadAllData(i);
        }
    }
    else {
        downloadAllData(task_control->currentIndex());
    }


}
void MainWindow::downloadAllData(int index)
{
    jboolean state = false;
    QString sharedFile = serverInfo.sharedFolderPath;
    QString filename="";
    QString outStream="";

    switch (index) {

        case 0:

            filename = "shippingtask_"+QDateTime::currentDateTime().toString("yy_MM_dd_hh_mm_ss")+".csv";
            sharedFile+=filename;
            outStream=shippingTable.getCSVData(userKey);

            break;
        case 1:

            filename = "inventorytask_"+QDateTime::currentDateTime().toString("yy_MM_dd_hh_mm_ss")+".csv";
            sharedFile+=filename;
            outStream=inventoryTable.getCSVData(userKey);

             break;
        case 2:

            filename = "consumptask_"+QDateTime::currentDateTime().toString("yy_MM_dd_hh_mm_ss")+".csv";
            sharedFile+=filename;
            outStream=consumpTable.getCSVData(userKey);

            break;

    }


    state = download(serverInfo.userName,serverInfo.password,serverInfo.ip_address,sharedFile,outStream);
    downloadConfirm(state,filename,task_control->itemText(index),outStream);
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
void MainWindow::downloadConfirm(bool state,QString filename,QString taskName,QString out)
{
    if(state)
        QMessageBox::information(this,taskName+"  "+root.firstChildElement("downloadStateTitle").text(),root.firstChildElement("downloadStateText").text());
    else{
        int res = QMessageBox::warning(this,taskName+"  "+root.firstChildElement("downloadErrorTitle").text(),root.firstChildElement("downloadErrorText_1").text(),QMessageBox::Cancel,QMessageBox::Save);
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

   QMessageBox::warning(this,root.firstChildElement("downloadErrorTitle").text(),root.firstChildElement("downloadErrorText_2").text());

}
void MainWindow::dataDelDlg()
{
    deleteDlg=new DeleteDataDlg(this);
    connect(deleteDlg, SIGNAL(oneDelete(int)),this,SLOT(deleteData(int)));
    connect(deleteDlg, SIGNAL(allDelete(int)),this,SLOT(deleteData(int)));
    connect(deleteDlg, SIGNAL(downloadDelete(int)),this,SLOT(deleteData(int)));
    connect(deleteDlg, SIGNAL(downloadAllDelete(int)),this,SLOT(deleteData(int)));

    deleteDlg->setModal(1);
    deleteDlg->exec();

}
void MainWindow::deleteData(int flag)
{
    switch (flag) {

    case 0:
        dbDataDelete(task_control->currentIndex());
        break;
    case 1:
      {
        for(int i=0;i<3;i++)
        {
            dbDataDelete(i);
        }
        if (QFile::exists("./inventory.db" ))
        {
            QFile::remove("./inventory.db");

            QFile file("./log.txt");
            QString out = "Database deleted: "+QDateTime::currentDateTime().toString();
            if (file.open(QIODevice::ReadWrite) )
            {
                QTextStream stream(&file);
                stream << out << endl;

            }
            file.close();

        }
        break;
      }
    case 2:
    {
        QString prefix;
        if(task_control->currentIndex() == 0)
        {
            prefix ="shippingtask_";
        }
        else if(task_control->currentIndex()==1){
            prefix ="inventorytask_";
        }
        else {
            prefix ="consumptask_";
        }
        downloadDataDel(serverInfo.userName,serverInfo.password,serverInfo.ip_address,serverInfo.sharedFolderPath,prefix,false);
        break;
    }
    case 3:
        downloadDataDel(serverInfo.userName,serverInfo.password,serverInfo.ip_address,serverInfo.sharedFolderPath,nullptr,true);
        break;

    }
}
void MainWindow::dbDataDelete(int tableNum)
{
    switch (tableNum) {

       case 0:
        shippingTable.deleteAllData();
        break;
      case 1:
        inventoryTable.deleteAllData();
        break;
      case 2:
        consumpTable.deleteAllData();
        break;
    }
}
void MainWindow::downloadDataDel(QString userName, QString password, QString ip_address, QString sharedFolder,QString filePrefix, bool isAll)
{
    if(ip_address == nullptr)
    {
      QMessageBox::information(this,root.firstChildElement("serverErrorTitle").text(),root.firstChildElement("serverErrorText").text());
      return;
    }
     QAndroidJniObject::callStaticMethod<void>("com/jni/systeminfo/NetworkManager", "delFile","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V",
                                                         QAndroidJniObject::fromString(userName).object<jstring>(),
                                                         QAndroidJniObject::fromString(password).object<jstring>(),
                                                         QAndroidJniObject::fromString(ip_address).object<jstring>(),
                                                         QAndroidJniObject::fromString(sharedFolder).object<jstring>(),
                                                         QAndroidJniObject::fromString(filePrefix).object<jstring>(),isAll);

}
