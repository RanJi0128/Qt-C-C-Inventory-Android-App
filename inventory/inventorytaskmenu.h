#ifndef INVENTORYTASKMENU_H
#define INVENTORYTASKMENU_H

#include "include.h"
#include "inventorytask.h"
#include "inventorytaskcreate.h"


class InventoryTaskMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit InventoryTaskMenu(QWidget *parent = nullptr,int key=0);


    bool deleteData(QString pri_id);


    QTableView *taskMenu;
    InventoryTableModel table;
    QLabel* pageTitle;

    QPushButton *createBtn;
    QPushButton *deleteBtn;
    QPushButton *editBtn;
    QPushButton *menuBtn;

    QDomElement root;

    InventoryTaskCreate *createTaskView;
    bool permission[3];

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

#endif // INVENTORYTASKMENU_H
