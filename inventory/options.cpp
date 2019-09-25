#include "options.h"
#include "mainwindow.h"
#include "extern.h"

Options::Options(QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);
    exitPermission=false;

    m = static_cast<MainWindow*>(parent);

    interface();
}
void Options::interface()
{
    root = doc.documentElement().firstChildElement("Options");

    optionTabs = new QTabWidget(this);
    optionTabs->setTabPosition(QTabWidget::South);

    advancedOption =new AdvancedOption(this);
    generalOption = new GeneralOption(this);
    languageOption = new LanguageOption(this);
    stateOption = new StateOption(this,m->userKey);

    objectGeometry();
    setCentralWidget(optionTabs);
    //optionTabs->setFixedSize(width,height);
    optionTabs->addTab(generalOption,root.firstChildElement("optionTab_1").text());
    optionTabs->addTab(advancedOption,root.firstChildElement("optionTab_2").text());
    optionTabs->addTab(languageOption,root.firstChildElement("optionTab_3").text());
    optionTabs->addTab(stateOption,root.firstChildElement("optionTab_4").text());

    connect(generalOption,SIGNAL(winClose()),this,SLOT(winClose()));
    connect(advancedOption,SIGNAL(winClose()),this,SLOT(winClose()));
    connect(advancedOption,SIGNAL(saveSignal()),this,SLOT(serverInfoUpdate()));
    connect(advancedOption,SIGNAL(appQuitSignal()),this,SLOT(appQuit()));
    connect(advancedOption,SIGNAL(fullScreenSignal(int)),this,SLOT(fullscreenMode(int)));

    exitPermission = m->m_permission[3];

    if(exitPermission)
        advancedOption->exitBt->setEnabled(1);
    else {
        advancedOption->exitBt->setEnabled(0);
    }
    advancedOption->cb->setChecked(m->fullScreenFlag);
    if(m->serverInfo.ip_address!=nullptr)
     {
        QString str = m->serverInfo.ip_address+'/'+ m->serverInfo.userName+'/'+m->serverInfo.sharedFolderPath;
        advancedOption->netpathEdit->setText(str.mid(0,str.length()-1));
        advancedOption->passwdEdit->setText(m->serverInfo.password);
     }
    advancedOption->time_control->setCurrentIndex(m->logoffTime==0 ? 9 : (m->logoffTime-5)/5);


}
void Options::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    width = size.width();
    height = size.height();

    objectGeometry();
}
void Options::objectGeometry()
{
    QString sheet ="QTabBar::tab { height: %1px; width: %2px; }";
    optionTabs->setStyleSheet(sheet.arg(this->height/20).arg(this->width/4));
}
void Options::winClose()
{

    m->isCtrlEnable=false;
    close();
    if(m->fullScreenFlag)
        m->showFullScreen();
    else {
        m->show();
    }
}
void Options::fullscreenMode(int state)
{
    if(state)
    {
       m->fullScreenFlag = true;
       this->showFullScreen();
    }
    else {
        m->fullScreenFlag = false;
        this->showNormal();
    }

}
void Options::serverInfoUpdate()
{
    m->serverInfoRead();
    m->logoffTimeRead();
}
void Options::appQuit()
{
    m->mainTimer->stop();
    qApp->quit();
}

