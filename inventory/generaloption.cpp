#include "generaloption.h"
#include "extern.h"

GeneralOption::GeneralOption(QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();

    interface();

}
void GeneralOption::interface()
{
    root = doc.documentElement().firstChildElement("GeneralOption");

    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText(root.firstChildElement("pageTitle").text());
    pageTitle->setObjectName("title");

    sysinfo = new QTextEdit(this);    
    sysinfo->setReadOnly(1);


    batteryBar = new QProgressBar(this);

    batteryLabel= new QLabel(this);    
    batteryLabel->setObjectName("battery");


    menuBtn = new QPushButton(this);    
    menuBtn->setText(root.firstChildElement("menuBtn").text());
    menuBtn->setObjectName("taskCtrlBtn");
    connect(menuBtn,SIGNAL(clicked()),this,SLOT(menuShow()));

    networkBtn = new QPushButton(this);    
    networkBtn->setText(root.firstChildElement("networkBtn").text());
    networkBtn->setObjectName("taskCtrlBtn");
    connect(networkBtn,SIGNAL(clicked()),this,SLOT(openNetworkSetting()));

    objectGeometry();


}
void GeneralOption::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    width = size.width();
    height = size.height();

    objectGeometry();
}
void GeneralOption::objectGeometry()
{
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);

    sysinfo->resize(width*91/100,height*20/100);
    sysinfo->move((width-sysinfo->width())/2,height*18/100);

    batteryBar->resize(width*86/100,height*3/100);
    batteryBar->move((width-batteryBar->width())/2,height*46/100);
    batteryLabel->resize(width*91/100,height*4/100);
    batteryLabel->move((width-batteryLabel->width())/2,height*41/100);

    menuBtn->resize(width*27/100,height*7/100);
    menuBtn->move((width-menuBtn->width())/2-width*25/100,height*69/100);

    networkBtn->resize(width*29/100,height*7/100);
    networkBtn->move((width-networkBtn->width())/2+width*22/100,height*69/100);


}
void GeneralOption::batteryInfoShow(int batteryLevel,bool onCharge)
{

    batteryBar->setValue(batteryLevel);
    QString str_1 =root.firstChildElement("batteryLabel_1").text();
    QString str_2 =root.firstChildElement("batteryLabel_2").text();
    QString str =str_1+":%1 (" +str_2+ ":%2"+")";
    batteryLabel->setText(str.arg(batteryBar->text()).arg(onCharge ? "Yes" :"No" ));
}
void GeneralOption::sysInfoShow(QString sysInfo)
{
    sysinfo->setText(sysInfo);
}
void GeneralOption::menuShow()
{

    emit winClose();

}
void GeneralOption::openNetworkSetting()
{
    QAndroidJniObject::callStaticMethod<void>("com/jni/systeminfo/OpenOtherApp", "openApp","(Landroid/content/Context;)V",
                                              QtAndroid::androidContext().object<jobject>());
}


