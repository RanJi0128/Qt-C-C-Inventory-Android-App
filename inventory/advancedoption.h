#ifndef ADVANCEDOPTION_H
#define ADVANCEDOPTION_H

#include "include.h"
class MyComboBox;
class LineEdit;

class AdvancedOption : public QMainWindow
{
    Q_OBJECT
public:
    explicit AdvancedOption(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event);
    void objectGeometry();

    QLabel* pageTitle;
    QLabel *explainLabel;
    QLabel *netpath;
    QLabel *passwdLabel;
    LineEdit *passwdEdit;
    LineEdit *netpathEdit;
    QPushButton *saveBtn,*menuBt,*exitBt;

    QCheckBox *cb;

    int width;
    int height;

    MyComboBox *time_control;
    QDomElement root;

    void interface();

signals:
    void winClose();
    void saveSignal();
    void appQuitSignal();
    void fullScreenSignal(int);
public slots:
    void saveSlot();
    void menuShow();
    void appQuit();
    void fullChecked(int state);
};

#endif // ADVANCEDOPTION_H
