#include "usermanger.h"
#include "mainwindow.h"
#include "extern.h"

LineEdit::LineEdit(QPixmap pixmap,int flag,QWidget *parent)
    : QLineEdit(parent)
{
    ctrlButton = new QToolButton(this);
    QPixmap scaled = pixmap.scaled( QSize(80, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    ctrlButton->setIcon(QIcon(scaled));
    ctrlButton->setIconSize(scaled.size());
    ctrlButton->hide();
    ctrlButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    connect(ctrlButton, SIGNAL(clicked()), this, SLOT(changeMode()));

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit {border-radius: 20px;padding-left: 30px;padding-right: %1px; }\
                           QLineEdit:focus{border-width: 5px;border-style : solid; border-color: #fd8a15;}").arg(ctrlButton->sizeHint().width() + frameWidth + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), ctrlButton->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), ctrlButton->sizeHint().height() + frameWidth * 2 + 2));

    isHidden=true;
    btFlag=flag;

    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));


}

void LineEdit::resizeEvent(QResizeEvent *)
{


    QSize sz = ctrlButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    ctrlButton->move(rect().right() - frameWidth - sz.width(),
                      (rect().bottom() + 1 - sz.height())/2);

}
void LineEdit::updateCloseButton(const QString& text)
{
    ctrlButton->setVisible(!text.isEmpty());
}
void LineEdit::changeMode()
{
    if(btFlag==1)
    {
        isHidden=!isHidden;

        if(!isHidden)
        {
            this->setEchoMode(QLineEdit::Normal);
            QPixmap pixmap("assets:/unhide.png");
            QPixmap scaled = pixmap.scaled( QSize(80, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation );
            ctrlButton->setIcon(QIcon(scaled));

        }
        else {

            this->setEchoMode(QLineEdit::Password);
            QPixmap pixmap("assets:/hide.png");
            QPixmap scaled = pixmap.scaled( QSize(80, 80), Qt::KeepAspectRatio, Qt::SmoothTransformation );
            ctrlButton->setIcon(QIcon(scaled));

        }
    }
    else {
        clear();
    }
}

UserManger::UserManger(QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);

    table.clear();

    m = static_cast<MainWindow*>(parent);

    interface();
}

void UserManger::interface()
{

    root = doc.documentElement().firstChildElement("UserManger");

    titleLabel = new QLabel(this);
    titleLabel->setText(root.firstChildElement("titleLabel").text());
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setGeometry(0,height*11/100,width,height*6/100);
    titleLabel->setObjectName("title");

    usernameLabel = new QLabel(this);
    usernameLabel->setText(root.firstChildElement("usernameLabel").text());
    usernameLabel->setAlignment(Qt::AlignCenter);
    usernameLabel->resize(width*28/100,height*6/100);
    usernameLabel->move((width-usernameLabel->width())/2-width*27/100,height*24/100);
    usernameLabel->setObjectName("userInfo");

    passwordLabel = new QLabel(this);
    passwordLabel->setText(root.firstChildElement("passwordLabel").text());
    passwordLabel->setAlignment(Qt::AlignCenter);
    passwordLabel->resize(width*29/100,height*6/100);
    passwordLabel->move((width-passwordLabel->width())/2-width*27/100,height*37/100);
    passwordLabel->setObjectName("userInfo");

    QPixmap pixmap("assets:/hide.png");
    passwdEdit = new LineEdit(pixmap,1,this);
    passwdEdit->setPlaceholderText(root.firstChildElement("passwdEdit").text());
    passwdEdit->resize(width*50/100,height*6/100);
    passwdEdit->move((width-passwdEdit->width())/2+width*15/100,height*37/100);
    passwdEdit->setEchoMode(QLineEdit::Password);
    passwdEdit->setObjectName("inputEdit");

    user_control= new MyComboBox(this);
    user_control->resize(width*50/100,height*6/100);
    user_control->move((width-user_control->width())/2+width*15/100,height*24/100);
    user_control->setObjectName("userCtl");
    connect(user_control,SIGNAL(currentIndexChanged(int)),this,SLOT(moveFocus()));

    explainLabel = new QLabel(this);
    explainLabel->setText(root.firstChildElement("explainLabel_1").text()+"\n"+root.firstChildElement("explainLabel_2").text());
    explainLabel->setAlignment(Qt::AlignCenter);
    explainLabel->setGeometry(0,height*48/100,width,height*11/100);
    explainLabel->setObjectName("explain");

    okBtn = new QPushButton(this);
    okBtn->resize(width*27/100,height*7/100);
    okBtn->move((width-okBtn->width())/2-width*21/100,height*77/100);
    okBtn->setText(root.firstChildElement("okBtn").text());
    okBtn->setObjectName("confirmBtn");
    connect(okBtn,SIGNAL(clicked()),this,SLOT(userConfirm()));


    cancelBtn = new QPushButton(this);
    cancelBtn->resize(width*27/100,height*7/100);
    cancelBtn->move((width-cancelBtn->width())/2+width*21/100,height*77/100);
    cancelBtn->setText(root.firstChildElement("cancelBtn").text());
    cancelBtn->setObjectName("confirmBtn");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    getData();




}
void UserManger::userConfirm()
{

    if(table.size() > 0)
      {
         QByteArray passwd;
         passwd.append(passwdEdit->text());

       int key = user_control->currentIndex();
       if(table.at(key).at(1) == user_control->currentText() && table.at(key).at(2) == QString(QCryptographicHash::hash(passwd,QCryptographicHash::Md5).toHex()))
         {
              m->loginSuccess(table.at(key).at(0).toInt(),table.at(key).at(3).toInt());
              this->close();

         }
       else {
           QMessageBox::warning(this,root.firstChildElement("userErrorTitle").text(),root.firstChildElement("userErrorText").text());
       }
      }
    else {
        return;
    }

}
void UserManger::moveFocus()
{
    passwdEdit->setFocus();
}
void UserManger::getData()
{

    QSqlQuery query;
    query.prepare("SELECT * FROM login;");
    query.exec();
    int count = 0;
    while (query.next()) {

       QString key = query.value(0).toString();
       QString name = query.value(1).toString();
       QString passwd = query.value(2).toString();
       QString permission = query.value(3).toString();

       table.append({key,name,passwd,permission});

       user_control->insertItem(count,name);
       count++;

    }
}
