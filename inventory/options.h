#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMainWindow>
#include <QTabWidget>
#include "generaloption.h"
#include "advancedoption.h"
#include "languageoption.h"
#include "stateoption.h"

class MainWindow;

class Options : public QMainWindow
{
    Q_OBJECT
public:
    explicit Options(QWidget *parent = nullptr);

    QTabWidget *optionTabs;

    AdvancedOption *advancedOption;
    GeneralOption *generalOption;
    LanguageOption *languageOption;
    StateOption *stateOption;

    int width;
    int height;

    bool exitPermission;

    MainWindow *m;

    void interface();


signals:

public slots:
    void winClose();
    void serverInfoUpdate();
    void appQuit();
};

#endif // OPTIONS_H
