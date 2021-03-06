#ifndef GENERALOPTION_H
#define GENERALOPTION_H

#include "include.h"
#include <QTextEdit>
#include <QProgressBar>
class GeneralOption : public QMainWindow
{
    Q_OBJECT
public:
    explicit GeneralOption(QWidget *parent = nullptr);

    QLabel* pageTitle;
    QTextEdit *sysinfo;
    QProgressBar *batteryBar;
    QLabel* batteryLabel;
    QPushButton *menuBtn;
    QPushButton *networkBtn;

    QDomElement root;

    int width;
    int height;


    void interface();
    void batteryInfoShow(int batteryLevel,bool onCharge);
    void sysInfoShow(QString sysInfo);
    void resizeEvent(QResizeEvent *event)override;
    void objectGeometry();



signals:
    void winClose();

public slots:
    void menuShow();
    void openNetworkSetting();
};

#endif // GENERALOPTION_H
