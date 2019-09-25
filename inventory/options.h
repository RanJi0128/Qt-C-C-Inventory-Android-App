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
    void resizeEvent(QResizeEvent *event)override;
    void objectGeometry();
    QTabWidget *optionTabs;

    AdvancedOption *advancedOption;
    GeneralOption *generalOption;
    LanguageOption *languageOption;
    StateOption *stateOption;

    int width;
    int height;

    bool exitPermission;

    MainWindow *m;
    QDomElement root;

    void interface();



signals:

public slots:
    void winClose();
    void serverInfoUpdate();
    void appQuit();
    void fullscreenMode(int);
};

#endif // OPTIONS_H
