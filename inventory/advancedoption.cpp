#include "advancedoption.h"
#include "mainwindow.h"


AdvancedOption::AdvancedOption(QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();

    interface();
}
void AdvancedOption::interface()
{
    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText("Advanced");
    pageTitle->setObjectName("title");
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);

    time_control= new MyComboBox(this);
    time_control->resize(width*41/100,height*6/100);
    time_control->move((width-time_control->width())/2+width*22/100,height*18/100);
    time_control->setObjectName("timeCtl");

    QListView *view = new QListView(time_control);
    QString str ="QListView::item{height: %1px}";
    view->setStyleSheet(str.arg(time_control->font().pixelSize()*2));
    time_control->setView(view);

    QStringListModel *taskModel = new QStringListModel(this);
    QStringList List;
    List << " 5 minutes"<< "10 minutes" << "15 minutes"<< "20 minutes"<< "25 minutes"<< "30 minutes"<< "35 minutes"<< "40 minutes"<< "45 minutes" << "Never";
    taskModel->setStringList(List);

    time_control->setModel(taskModel);

    explainLabel = new QLabel(this);
    explainLabel->setText("Minutes till auto log off :");
    explainLabel->setAlignment(Qt::AlignCenter);
    explainLabel->resize(width*45/100,height*6/100);
    explainLabel->move((width-explainLabel->width())/2-width*25/100,height*18/100);
    explainLabel->setObjectName("advanced");

    netpath = new QLabel(this);
    netpath->setText("Network Path");
    netpath->setAlignment(Qt::AlignLeft);
    netpath->resize(width*50/100,height*6/100);
    netpath->move((width-netpath->width())/2-width*21/100,height*30/100);
    netpath->setObjectName("advanced");

    QPixmap pixmap("assets:/clear.png");
    netpathEdit = new LineEdit(pixmap,2,this);
    netpathEdit->setPlaceholderText("ip_address/username/sharedfolder");
    netpathEdit->resize(width*80/100,height*5/100);
    netpathEdit->move((width-netpathEdit->width())/2-width*6/100,height*33/100);
    netpathEdit->setObjectName("inputEdit");

    passwdLabel = new QLabel(this);
    passwdLabel->setText("Password");
    passwdLabel->setAlignment(Qt::AlignLeft);
    passwdLabel->resize(width*50/100,height*6/100);
    passwdLabel->move((width-passwdLabel->width())/2-width*21/100,height*40/100);
    passwdLabel->setObjectName("advanced");

    QPixmap pixmap_1("assets:/hide.png");
    passwdEdit = new LineEdit(pixmap_1,1,this);
    passwdEdit->setPlaceholderText("Password Input");
    passwdEdit->resize(width*80/100,height*5/100);
    passwdEdit->move((width-passwdEdit->width())/2-width*6/100,height*43/100);
    passwdEdit->setEchoMode(QLineEdit::Password);
    passwdEdit->setObjectName("inputEdit");

    saveBtn = new QPushButton(this);
    saveBtn->resize(width*25/100,height*6/100);
    saveBtn->move((width-saveBtn->width())/2-width*34/100,height*68/100);
    saveBtn->setText("Save");
    saveBtn->setObjectName("taskCtrlBtn");
    connect(saveBtn,SIGNAL(clicked()),this,SLOT(saveSlot()));

    menuBt = new QPushButton(this);
    menuBt->resize(width*25/100,height*6/100);
    menuBt->move((width-menuBt->width())/2,height*68/100);
    menuBt->setText("Menu");
    menuBt->setObjectName("taskCtrlBtn");
    connect(menuBt,SIGNAL(clicked()),this,SLOT(menuShow()));

    exitBt = new QPushButton(this);
    exitBt->resize(width*25/100,height*6/100);
    exitBt->move((width-exitBt->width())/2+width*34/100,height*68/100);
    exitBt->setText("Exit");
    exitBt->setObjectName("exitCtrlBtn");
    exitBt->setEnabled(0);
    connect(exitBt,SIGNAL(clicked()),this,SLOT(appQuit()));
}
void AdvancedOption::saveSlot()
{
    if(netpathEdit->text().split('/',QString::SkipEmptyParts).length() > 2 && passwdEdit->text().length() > 0)
    {
        QFile file("./server.txt");
    //    if (file.exists())
    //    {
    //        file.remove();
    //    }
        QString out = netpathEdit->text() + "\n" + passwdEdit->text();
        if (file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream(&file);
            stream << out << endl;

        }
        file.close();
        QMessageBox::information(this,"Ok","All data was saved correctly!");
        emit saveSignal();
    }
    else {

        QMessageBox::warning(this,"Input Error!","Input all value correctly !");
    }


}
void AdvancedOption::menuShow()
{
    emit winClose();
}
void AdvancedOption::appQuit()
{
    int res = QMessageBox::warning(this,"Exit Confirm!","Would you quit app really ?",QMessageBox::Ok,QMessageBox::Cancel);

    if(res==QMessageBox::Ok)
    {
        emit appQuitSignal();

    }
    else {
        return;
    }

}

