#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "usermanger.h"
#include "shippingtaskmenu.h"
#include "consumptaskmenu.h"
#include "inventorytaskmenu.h"
#include "options.h"
#include "downloadstate.h"

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
    ~MainWindow();

public :

     QLabel *mainTitle;
     QLabel *taskLabel;
     QPushButton *loginBtn;
     QPushButton *downloadBtn;
     QPushButton *scanBtn;
     QPushButton *purgeBtn;
     QPushButton *optionBtn;
     QTimer *mainTimer;
     MyComboBox *task_control;

     QStringListModel *taskModel;

     UserManger *loginPage;

     ShippingTaskMenu *shippingTask;
     ConsumpTaskMenu *consumpTask;
     InventoryTaskMenu *inventoryTask;

     DownloadStateModel stateTable;
     TableModel consumpTable;
     ShippingTableModel shippingTable;
     InventoryTableModel inventoryTable;

     Options *options;


     QString m_dbState;

     bool m_permission[4];
     bool isCtrlEnable;

     int width;
     int height;
     int userKey;

     void interface();
     void dbErrorShow();
     void loginSuccess(int key, int permission);

     void consumpTaskShow();
     void shippingTaskShow();
     void inventoryTaskShow();

     void androidBatteryStateChanged(int level, bool onCharge);
     void androidSysteminfo(QString info);

     void serverInfoRead();
     bool download(QString,QString,QString,QString,QString);
     void downloadConfirm(bool state,QString filename,QString out);
     void dataConfirm();


     struct SysInfo{
         SysInfo()
         {
             batteryLevel=0;
             onCharge=false;
             sysInfo=" ";
         }
         SysInfo(const SysInfo &info) {

             batteryLevel=info.batteryLevel;
             onCharge=info.onCharge;
             sysInfo = info.sysInfo;

           }
         int batteryLevel;
         bool onCharge;
         QString sysInfo;

     }sysInfo;

     struct ServerInfo{

         QString ip_address;
         QString userName;
         QString password;
         QString sharedFolderPath;

         ServerInfo()
         {
             ip_address="";
             userName="";
             password="";
             sharedFolderPath="";
         }


     }serverInfo;


signals:

public slots:

     void taskShow();
     void loginPageShow();
     void optionsShow();
     void downloadFile();
     void backgroundTransfer();

};

#endif // MAINWINDOW_H
