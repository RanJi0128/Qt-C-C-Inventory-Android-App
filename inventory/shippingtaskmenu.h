#ifndef SHIPPINGTASKMENU_H
#define SHIPPINGTASKMENU_H

#include "include.h"
#include "shippingtask.h"
#include "shippingtaskcreate.h"


class ShippingTaskMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit ShippingTaskMenu(QWidget *parent = nullptr,int key=0);


    bool deleteData(QString pri_id);

    QTableView *taskMenu;
    ShippingTableModel table;
    QLabel* pageTitle;

    QPushButton *createBtn;
    QPushButton *deleteBtn;
    QPushButton *editBtn;
    QPushButton *menuBtn;

    ShippingTaskCreate *createTaskView;
    bool permission[3];

    QDomElement root;

    void interface();

    int userKey;
    int width;
    int height;

signals:

public slots:

    void menuShow();
    void deleteConfirm();
    void editShow();
    void createShow();
    void rowSelected(const QModelIndex & index);
};

#endif // SHIPPINGTASKMENU_H
