#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "usermanger.h"
#include "shippingtaskmenu.h"
#include "consumptaskmenu.h"
#include "inventorytaskmenu.h"
#include "options.h"
#include "downloadstate.h"
#include "deletedatadlg.h"

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
     explicit MainWindow(int dbState,QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event);

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
     Options *options;

     DownloadStateModel stateTable;
     TableModel consumpTable;
     ShippingTableModel shippingTable;
     InventoryTableModel inventoryTable;

     DeleteDataDlg *deleteDlg;
     int m_dbState;

     QDomElement root;

     bool fullScreenFlag;

     bool m_permission[4];
     bool isCtrlEnable;

     int width;
     int height;
     int userKey;
     int logoffTime;

     void loadXml();
     void interface();
     void dbErrorShow();
     void loginSuccess(int key, int permission);

     void consumpTaskShow();
     void shippingTaskShow();
     void inventoryTaskShow();

     void androidBatteryStateChanged(int level, bool onCharge);
     void androidSysteminfo(QString info);

     void serverInfoRead();
     void logoffTimeRead();
     bool download(QString,QString,QString,QString,QString);
     void downloadConfirm(bool state,QString filename,QString taskName,QString out);
     void downloadAllData(int);
     void dataConfirm();
     void dbDataDelete(int tableNum);
     void downloadDataDel(QString,QString,QString,QString,QString,bool);
     void objectGeometry();
     void appLogoff();

     struct SysInfo{
         SysInfo()
         {
             init();
         }
         void init()
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
             init();
         }
         void init()
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
     void dataDelDlg();
     void deleteData(int flag);


};

#endif // MAINWINDOW_H
