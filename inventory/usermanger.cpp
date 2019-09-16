#include "usermanger.h"
#include "mainwindow.h"


LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    hideButton = new QToolButton(this);
    QPixmap pixmap("assets:/hide.png");
    QPixmap scaled = pixmap.scaled( QSize(80, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    hideButton->setIcon(QIcon(scaled));
    hideButton->setIconSize(scaled.size());
    hideButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    hideButton->hide();
    connect(hideButton, SIGNAL(clicked()), this, SLOT(changeMode()));

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit {border-radius: 20px;padding-left: 30px;padding-right: %1px; } ").arg(hideButton->sizeHint().width() + frameWidth + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), hideButton->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), hideButton->sizeHint().height() + frameWidth * 2 + 2));

    isHidden=true;
}

void LineEdit::resizeEvent(QResizeEvent *)
{


    QSize sz = hideButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    hideButton->move(rect().right() - frameWidth - sz.width(),
                      (rect().bottom() + 1 - sz.height())/2);
}
void LineEdit::changeMode()
{
    isHidden=!isHidden;

    if(!isHidden)
    {
        this->setEchoMode(QLineEdit::Normal);
        QPixmap pixmap("assets:/unhide.png");
        QPixmap scaled = pixmap.scaled( QSize(80, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation );
        hideButton->setIcon(QIcon(scaled));

    }
    else {

        this->setEchoMode(QLineEdit::Password);
        QPixmap pixmap("assets:/hide.png");
        QPixmap scaled = pixmap.scaled( QSize(80, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation );
        hideButton->setIcon(QIcon(scaled));

    }
}

UserManger::UserManger(QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);

    interface();
}

void UserManger::interface()
{
    titleLabel = new QLabel(this);
    titleLabel->setText("Login");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setGeometry(0,height*11/100,width,height*6/100);
    titleLabel->setObjectName("title");

    usernameLabel = new QLabel(this);
    usernameLabel->setText("Operator Name");
    usernameLabel->setAlignment(Qt::AlignCenter);
    usernameLabel->resize(width*28/100,height*6/100);
    usernameLabel->move((width-usernameLabel->width())/2-width*27/100,height*24/100);
    usernameLabel->setObjectName("userInfo");

    passwordLabel = new QLabel(this);
    passwordLabel->setText("Password");
    passwordLabel->setAlignment(Qt::AlignCenter);
    passwordLabel->resize(width*29/100,height*6/100);
    passwordLabel->move((width-passwordLabel->width())/2-width*27/100,height*37/100);
    passwordLabel->setObjectName("userInfo");

    passwdEdit = new LineEdit(this);
    passwdEdit->setPlaceholderText("Password Input");
    passwdEdit->resize(width*50/100,height*6/100);
    passwdEdit->move((width-passwdEdit->width())/2+width*15/100,height*37/100);
    passwdEdit->setEchoMode(QLineEdit::Password);
    passwdEdit->hideButton->show();
    passwdEdit->setObjectName("inputEdit");

    user_control= new MyComboBox(this);
    user_control->resize(width*50/100,height*6/100);
    user_control->move((width-user_control->width())/2+width*15/100,height*24/100);
    user_control->setObjectName("userCtl");
    user_control->insertItem(1,"Inventory");
    user_control->insertItem(2,"Consumption");

    explainLabel = new QLabel(this);
    explainLabel->setText("Select an Operator from list.To enter the password.\n Click ok and start using program.");
    explainLabel->setAlignment(Qt::AlignCenter);
    explainLabel->setGeometry(0,height*48/100,width,height*11/100);
    explainLabel->setObjectName("explain");

    okBtn = new QPushButton(this);
    okBtn->resize(width*27/100,height*7/100);
    okBtn->move((width-okBtn->width())/2-width*21/100,height*77/100);
    okBtn->setText("OK");
    okBtn->setObjectName("confirmBtn");
    connect(okBtn,SIGNAL(clicked()),this,SLOT(userConfirm()));


    cancelBtn = new QPushButton(this);
    cancelBtn->resize(width*27/100,height*7/100);
    cancelBtn->move((width-cancelBtn->width())/2+width*21/100,height*77/100);
    cancelBtn->setText("Cancel");
    cancelBtn->setObjectName("confirmBtn");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));



}
void UserManger::userConfirm()
{

    QMessageBox::warning(this,"Input Error","UserName or Password Wrong!");
}
