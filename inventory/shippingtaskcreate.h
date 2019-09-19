#ifndef SHIPPINGTASKCREATE_H
#define SHIPPINGTASKCREATE_H

#include "include.h"
#include "customkeyboard.h"
class LineEdit;
class ShippingTableModel;

class ShippingTaskCreate : public QMainWindow
{
    Q_OBJECT

public:
             ShippingTaskCreate(int key,QString pri_id, QString title,QString order,QString ship, QWidget *parent = nullptr);
    explicit ShippingTaskCreate(int key, QString title, QWidget *parent = nullptr);

             bool insertData(QString oderStr, QString shipStr,int key);
             bool updateData(QString oderStr, QString shipStr,int key, QString pri_id);


    enum STATE{Create,Edit}State;
    QLabel* pageTitle;
    QLabel* orderLabel;
    LineEdit *orderEdit;
    QLabel* shipLabel;
    LineEdit *shipEdit;

    QPushButton *orderBtn;
    QPushButton *shipBtn;

    void interface();


    int userKey;
    QString m_pri_id;
    QString wtitle;

    QPushButton *cancelBtn;
    QPushButton *continueBt;

    int width;
    int height;
    QString m_order;
    QString m_ship;

    ShippingTableModel *table;
    CustomKeyBoard *customKeyboard;

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

    void keyboardShow();
    void insertTask();
};

#endif // SHIPPINGTASKCREATE_H
