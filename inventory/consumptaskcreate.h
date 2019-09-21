#ifndef CONSUMPTASKCREATE_H
#define CONSUMPTASKCREATE_H

#include "include.h"
#include "customkeyboard.h"

class LineEdit;
class TableModel;

class ConsumpTaskCreate : public QMainWindow
{
    Q_OBJECT

public:
             ConsumpTaskCreate(int key,QString pri_id, QString title,QString order,QString location, QWidget *parent = nullptr);
    explicit ConsumpTaskCreate(int key, QString title, QWidget *parent = nullptr);

             bool insertData(QString oderStr, QString lctStr,int key);
             bool updateData(QString oderStr, QString lctStr,int key, QString pri_id);


    enum STATE{Create,Edit}State;
    QLabel* pageTitle;
    QLabel* orderLabel;
    LineEdit *orderEdit;
    QLabel* locationLabel;
    LineEdit *locationEdit;

    QPushButton *orderBtn;
    QPushButton *locationBtn;

    void interface();


    int userKey;
    QString m_pri_id;
    QString wtitle;

    QPushButton *cancelBtn;
    QPushButton *continueBt;

    int width;
    int height;
    QString m_order;
    QString m_location;

    TableModel *table;
    CustomKeyBoard *customKeyboard;

    QDomElement root;

    bool eventFilter(QObject *obj, QEvent *event)
    {
//        QByteArray ba = QString::number(event->type()).toLocal8Bit();
//        const char *c_str2 = ba.data();
//      __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);

         QApplication::inputMethod()->hide();
           // standard event processing
         return QObject::eventFilter(obj, event);

    }


signals:

public slots:

    void insertTask();
    void keyboardShow();
};

#endif // CONSUMPTASKCREATE_H
