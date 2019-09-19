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

    QLabel* pageTitle;
    QLabel *explainLabel;
    QLabel *netpath;
    QLabel *passwdLabel;
    LineEdit *passwdEdit;
    LineEdit *netpathEdit;
    QPushButton *saveBtn,*menuBt,*exitBt;


    int width;
    int height;

    MyComboBox *time_control;

    void interface();

signals:
    void winClose();
    void saveSignal();
    void appQuitSignal();
public slots:
    void saveSlot();
    void menuShow();
    void appQuit();
};

#endif // ADVANCEDOPTION_H
