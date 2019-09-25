#ifndef INVENTORYTASKCREATE_H
#define INVENTORYTASKCREATE_H

#include "include.h"
#include "customkeyboard.h"

class LineEdit;
class InventoryTableModel;

class InventoryTaskCreate : public QMainWindow
{
    Q_OBJECT

public:
             InventoryTaskCreate(int key,QString pri_id, QString title,QString physical,QString location,QString sublocation, QWidget *parent = nullptr);
    explicit InventoryTaskCreate(int key, QString title, QWidget *parent = nullptr);

             bool insertData(QString phyStr, QString lctStr,QString sublctStr,int key);
             bool updateData(QString phyStr, QString lctStr,QString sublctStr,int key, QString pri_id);
             void resizeEvent(QResizeEvent *event);
             void objectGeometry();

    enum STATE{Create,Edit}State;
    QLabel* pageTitle;
    QLabel* phycalLabel;
    LineEdit *phycalEdit;
    QLabel* locationLabel;
    LineEdit *locationEdit;
    QLabel* sublocationLabel;
    LineEdit *sublocationEdit;

    QPushButton *physicalBtn;
    QPushButton *locationBtn;
    QPushButton *sublocationBtn;

    void interface();


    int userKey;
    QString m_pri_id;
    QString wtitle;

    QPushButton *cancelBtn;
    QPushButton *continueBt;

    int width;
    int height;
    QString m_physical;
    QString m_location;
    QString m_sublocation;

    InventoryTableModel *table;
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

    void keyboardShow();
    void insertTask();
};

#endif // INVENTORYTASKCREATE_H
