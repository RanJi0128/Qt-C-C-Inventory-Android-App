#ifndef USERMANGER_H
#define USERMANGER_H

#include "include.h"


class MyComboBox;

class LineEdit : public QLineEdit
{
    Q_OBJECT

public:
    LineEdit(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *);
    virtual void focusInEvent( QFocusEvent* )
    {
        QGuiApplication::inputMethod()->hide();
    }


public:

    QToolButton *hideButton;
    QPixmap pixmap;
    bool isHidden;

public slots:

   void changeMode();
};


class UserManger : public QMainWindow
{
    Q_OBJECT
public:
    explicit UserManger(QWidget *parent = nullptr);

    QLabel *titleLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    MyComboBox *user_control;
    LineEdit *passwdEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    QLabel *explainLabel;

    int width;
    int height;

    void interface();

    bool eventFilter(QObject *obj, QEvent *event)
    {
//        QByteArray ba = QString::number(event->type()).toLocal8Bit();
//        const char *c_str2 = ba.data();
//      __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);

         QGuiApplication::inputMethod()->hide();
           // standard event processing
         return QObject::eventFilter(obj, event);

    }
signals:

public slots:
    void userConfirm();
};

#endif // USERMANGER_H
