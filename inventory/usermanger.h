#ifndef USERMANGER_H
#define USERMANGER_H

#include "include.h"
#include <QCryptographicHash>

class MyComboBox;
class MainWindow;

class LineEdit : public QLineEdit
{
    Q_OBJECT

public:
    LineEdit(QPixmap pixmap,int flag,QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *);

public:

    QToolButton *ctrlButton;
    bool isHidden;
    int btFlag;

public slots:

   void updateCloseButton(const QString &text);
   void changeMode();
};


class UserManger : public QMainWindow
{
    Q_OBJECT
public:
    explicit UserManger(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event)override;
    void objectGeometry();
    QLabel *titleLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    MyComboBox *user_control;
    LineEdit *passwdEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    QLabel *explainLabel;
    QVector<QVector<QString>> table;

    MainWindow *m;

    QDomElement root;

    int width;
    int height;

    void interface();
    void getData();


signals:

public slots:
    void userConfirm();
    void moveFocus();
};

#endif // USERMANGER_H
