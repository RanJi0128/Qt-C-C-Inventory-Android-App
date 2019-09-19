#include "generaloption.h"

GeneralOption::GeneralOption(QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();

    interface();

}
void GeneralOption::interface()
{
    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText("General");
    pageTitle->setObjectName("title");
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);

    sysinfo = new QTextEdit(this);
    sysinfo->resize(width*91/100,height*20/100);
    sysinfo->move((width-sysinfo->width())/2,height*18/100);
    sysinfo->setReadOnly(1);


    batteryBar = new QProgressBar(this);
    batteryBar->resize(width*86/100,height*3/100);
    batteryBar->move((width-batteryBar->width())/2,height*46/100);


    batteryLabel= new QLabel(this);
    batteryLabel->resize(width*91/100,height*4/100);
    batteryLabel->move((width-batteryLabel->width())/2,height*41/100);
    batteryLabel->setObjectName("battery");


    menuBtn = new QPushButton(this);
    menuBtn->resize(width*27/100,height*7/100);
    menuBtn->move((width-menuBtn->width())/2-width*25/100,height*69/100);
    menuBtn->setText("Menu");
    menuBtn->setObjectName("taskCtrlBtn");
    connect(menuBtn,SIGNAL(clicked()),this,SLOT(menuShow()));

    networkBtn = new QPushButton(this);
    networkBtn->resize(width*29/100,height*7/100);
    networkBtn->move((width-networkBtn->width())/2+width*22/100,height*69/100);
    networkBtn->setText("NetWork");
    networkBtn->setObjectName("taskCtrlBtn");
    connect(networkBtn,SIGNAL(clicked()),this,SLOT(openNetworkSetting()));



}
void GeneralOption::batteryInfoShow(int batteryLevel,bool onCharge)
{

    batteryBar->setValue(batteryLevel);
    QString str ="Main Battery:%1 (On charging: %2)";
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


