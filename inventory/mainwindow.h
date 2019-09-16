#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"
#include "usermanger.h"

class MyComboBox : public QComboBox
{
    Q_OBJECT

    public:
        explicit MyComboBox(QWidget *parent = nullptr) : QComboBox(parent){

            setEditable(false);


        }

        //On Windows this is not needed as long as the combobox is editable
        //This is untested since I don't have Linux
        void showPopup(){

            QComboBox::showPopup();
            QWidget *popup = this->findChild<QFrame*>();
            popup->move(this->x()+10, this->y()+this->height()+5);
            popup->resize(this->width()-20,popup->height());

        }

};
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
     explicit MainWindow(QString dbState,QWidget *parent = nullptr);

public :

     QLabel *mainTitle;
     QLabel *taskLabel;
     QPushButton *loginBtn;
     QPushButton *downloadBtn;
     QPushButton *scanBtn;
     QPushButton *purgeBtn;
     QPushButton *optionBtn;
     MyComboBox *task_control;

     UserManger *loginPage;

     QString m_dbState;

     int width;
     int height;

     void interface();
     void dbErrorShow();

signals:

public slots:
     void loginPageShow();
};

#endif // MAINWINDOW_H
