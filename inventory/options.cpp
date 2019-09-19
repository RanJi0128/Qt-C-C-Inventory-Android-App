#include "options.h"
#include "mainwindow.h"
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
    optionTabs = new QTabWidget(this);
    optionTabs->setTabPosition(QTabWidget::South);

    advancedOption =new AdvancedOption(this);
    generalOption = new GeneralOption(this);
    languageOption = new LanguageOption(this);
    stateOption = new StateOption(this,m->userKey);

    //setCentralWidget(optionTabs);
    optionTabs->setFixedSize(width,height);
    optionTabs->addTab(generalOption,"General");
    optionTabs->addTab(advancedOption,"Advanced");
    optionTabs->addTab(languageOption,"Language");
    optionTabs->addTab(stateOption,"State");

    QString sheet ="QTabBar::tab { height: %1px; width: %2px; }";
    optionTabs->setStyleSheet(sheet.arg(this->height/20).arg(this->width/4));

    connect(generalOption,SIGNAL(winClose()),this,SLOT(winClose()));
    connect(advancedOption,SIGNAL(winClose()),this,SLOT(winClose()));
    connect(advancedOption,SIGNAL(saveSignal()),this,SLOT(serverInfoUpdate()));
    connect(advancedOption,SIGNAL(appQuitSignal()),this,SLOT(appQuit()));

    exitPermission = m->m_permission[3];

    if(exitPermission)
        advancedOption->exitBt->setEnabled(1);
    else {
        advancedOption->exitBt->setEnabled(0);
    }
    if(m->serverInfo.ip_address!=nullptr)
     {
        QString str = m->serverInfo.ip_address+'/'+ m->serverInfo.userName+'/'+m->serverInfo.sharedFolderPath;
        advancedOption->netpathEdit->setText(str);
        advancedOption->passwdEdit->setText(m->serverInfo.password);
     }


}
void Options::winClose()
{

    m->isCtrlEnable=false;
    close();
}
void Options::serverInfoUpdate()
{
    m->serverInfoRead();
}
void Options::appQuit()
{
    m->mainTimer->stop();
    qApp->quit();
}

