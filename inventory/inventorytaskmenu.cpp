#include "inventorytaskmenu.h"
#include "extern.h"
InventoryTaskMenu::InventoryTaskMenu(QWidget *parent,int key) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();
    this->setGeometry(0,0,width,height);

    userKey=key;

    for (int i=0;i<3;i++) {

        permission[i]=false;
    }
    interface();

}
void InventoryTaskMenu::interface()
{
    root = doc.documentElement().firstChildElement("InventoryTaskMenu");

    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText(root.firstChildElement("pageTitle").text());
    pageTitle->setObjectName("title");    

    table.getReadAllData(userKey);

    taskMenu = new QTableView(this);
    taskMenu->setModel(&table);    
    taskMenu->horizontalHeader()->setStretchLastSection(true);
    taskMenu->verticalHeader()->hide();
    taskMenu->setEditTriggers(QAbstractItemView::NoEditTriggers);
    taskMenu->setSelectionBehavior(QAbstractItemView::SelectRows);
    taskMenu->setSelectionMode(QAbstractItemView::SingleSelection);
    taskMenu->verticalHeader()->setDefaultSectionSize(taskMenu->height()*8/100);
    taskMenu->setColumnWidth(0,taskMenu->width()/3);
    connect(taskMenu,SIGNAL(clicked(const QModelIndex &)),this,SLOT(rowSelected(const QModelIndex & )));

    menuBtn = new QPushButton(this);    
    menuBtn->setText(root.firstChildElement("menuBtn").text());
    menuBtn->setObjectName("taskCtrlBtn");
    connect(menuBtn,SIGNAL(clicked()),this,SLOT(menuShow()));

    deleteBtn = new QPushButton(this);    
    deleteBtn->setText(root.firstChildElement("deleteBtn").text());
    deleteBtn->setObjectName("taskCtrlBtn");
    deleteBtn->setEnabled(0);
    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(deleteConfirm()));

    editBtn = new QPushButton(this);    
    editBtn->setText(root.firstChildElement("edit").text());
    editBtn->setObjectName("taskCtrlBtn");
    editBtn->setEnabled(0);
    connect(editBtn,SIGNAL(clicked()),this,SLOT(editShow()));

    createBtn = new QPushButton(this);    
    createBtn->setText(root.firstChildElement("create").text());
    createBtn->setObjectName("taskCtrlBtn");
    if(permission[0])
     createBtn->setEnabled(1);
    else {
        createBtn->setEnabled(0);
    }
    connect(createBtn,SIGNAL(clicked()),this,SLOT(createShow()));

    objectGeometry();
}
void InventoryTaskMenu::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    width = size.width();
    height = size.height();

    objectGeometry();
}
void InventoryTaskMenu::objectGeometry()
{
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);

    taskMenu->resize(width-30,height*70/100);
    taskMenu->move((width-taskMenu->width())/2,pageTitle->y()+pageTitle->height()+15);

    menuBtn->resize(width*19/100,height*6/100);
    menuBtn->move((width-menuBtn->width())/2-width*38/100,height*90/100);

    deleteBtn->resize(width*19/100,height*6/100);
    deleteBtn->move((width-deleteBtn->width())/2-width*13/100,height*90/100);

    editBtn->resize(width*19/100,height*6/100);
    editBtn->move((width-editBtn->width())/2+width*13/100,height*90/100);

    createBtn->resize(width*19/100,height*6/100);
    createBtn->move((width-createBtn->width())/2+width*38/100,height*90/100);


}
void InventoryTaskMenu::menuShow()
{
    this->close();
}
void InventoryTaskMenu::deleteConfirm()
{

    int res = QMessageBox::warning(this,root.firstChildElement("delConfirmTitle").text(),root.firstChildElement("delConfirmText").text(),QMessageBox::Ok,QMessageBox::Cancel);

    if(res==QMessageBox::Ok)
    {
        QItemSelectionModel *select = taskMenu->selectionModel();
        int rowNum = select->selectedRows().at(0).row();
        if(rowNum<0) return;
        taskMenu->clearSelection();
        editBtn->setEnabled(0);
        deleteBtn->setEnabled(0);
        deleteData(table.getData(rowNum,0));
        table.getReadAllData(userKey);

    }
    else {

        return;
    }
}
void InventoryTaskMenu::rowSelected(const QModelIndex & )
{

   if(permission[1])
    editBtn->setEnabled(1);
   else {
    editBtn->setEnabled(0);
   }
   if(permission[2])
    deleteBtn->setEnabled(1);
   else {
    deleteBtn->setEnabled(0);
   }


}
void InventoryTaskMenu::editShow()
{
    QItemSelectionModel *select = taskMenu->selectionModel();
    int rowNum = select->selectedRows().at(0).row();
    if(rowNum<0) return;
    taskMenu->clearSelection();
    editBtn->setEnabled(0);
    deleteBtn->setEnabled(0);

    createTaskView = new InventoryTaskCreate(userKey,table.getData(rowNum,0),root.firstChildElement("edit").text(),table.getData(rowNum,2),table.getData(rowNum,3),table.getData(rowNum,4),this);
    createTaskView->table = &table;
   if(this->isFullScreen())
    createTaskView->showFullScreen();
   else {
     createTaskView->show();
   }
}

void InventoryTaskMenu::createShow()
{
    taskMenu->clearSelection();
    editBtn->setEnabled(0);
    deleteBtn->setEnabled(0);

    createTaskView = new InventoryTaskCreate(userKey,root.firstChildElement("create").text(),this);
    createTaskView->table = &table;
    if(this->isFullScreen())
     createTaskView->showFullScreen();
    else {
        createTaskView->show();
    }
}

bool InventoryTaskMenu::deleteData(QString pri_id)
{
//      QByteArray ba = pri_id.toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);
        QSqlQuery query;
        query.prepare("DELETE FROM inventory WHERE pri_id=:pri_id;");
        query.bindValue(":pri_id", pri_id.toInt());

        if(query.exec())
        {
           return true;
        }

        return false;
}


