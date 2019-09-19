#include "consumptaskmenu.h"

ConsumpTaskMenu::ConsumpTaskMenu(QWidget *parent,int key) : QMainWindow(parent)
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
void ConsumpTaskMenu::interface()
{
    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText("Consumption Jobs/Units");
    pageTitle->setObjectName("title");
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);

    table.getReadAllData(userKey);

    taskMenu = new QTableView(this);
    taskMenu->setModel(&table);
    taskMenu->resize(width-30,height*70/100);
    taskMenu->move((width-taskMenu->width())/2,pageTitle->y()+pageTitle->height()+50);
    taskMenu->horizontalHeader()->setStretchLastSection(true);
    taskMenu->verticalHeader()->hide();
    taskMenu->setEditTriggers(QAbstractItemView::NoEditTriggers);
    taskMenu->setSelectionBehavior(QAbstractItemView::SelectRows);
    taskMenu->setSelectionMode(QAbstractItemView::SingleSelection);
    taskMenu->verticalHeader()->setDefaultSectionSize(taskMenu->height()*8/100);
    taskMenu->setColumnWidth(0,taskMenu->width()/3);
    connect(taskMenu,SIGNAL(clicked(const QModelIndex &)),this,SLOT(rowSelected(const QModelIndex & )));

    menuBtn = new QPushButton(this);
    menuBtn->resize(width*19/100,height*6/100);
    menuBtn->move((width-menuBtn->width())/2-width*38/100,height*90/100);
    menuBtn->setText("Menu");
    menuBtn->setObjectName("taskCtrlBtn");
    connect(menuBtn,SIGNAL(clicked()),this,SLOT(menuShow()));

    deleteBtn = new QPushButton(this);
    deleteBtn->resize(width*19/100,height*6/100);
    deleteBtn->move((width-deleteBtn->width())/2-width*13/100,height*90/100);
    deleteBtn->setText("Del");
    deleteBtn->setObjectName("taskCtrlBtn");
    deleteBtn->setEnabled(0);
    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(deleteConfirm()));

    editBtn = new QPushButton(this);
    editBtn->resize(width*19/100,height*6/100);
    editBtn->move((width-editBtn->width())/2+width*13/100,height*90/100);
    editBtn->setText("Edit");
    editBtn->setObjectName("taskCtrlBtn");
    editBtn->setEnabled(0);
    connect(editBtn,SIGNAL(clicked()),this,SLOT(editShow()));

    createBtn = new QPushButton(this);
    createBtn->resize(width*19/100,height*6/100);
    createBtn->move((width-createBtn->width())/2+width*38/100,height*90/100);
    createBtn->setText("Create");
    createBtn->setObjectName("taskCtrlBtn");
    if(permission[0])
     createBtn->setEnabled(1);
    else {
        createBtn->setEnabled(0);
    }
    connect(createBtn,SIGNAL(clicked()),this,SLOT(createShow()));
}

void ConsumpTaskMenu::menuShow()
{
    this->close();
}
void ConsumpTaskMenu::deleteConfirm()
{

    int res = QMessageBox::warning(this,"Delete Confirm!","Would you delete really ?",QMessageBox::Ok,QMessageBox::Cancel);

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
void ConsumpTaskMenu::rowSelected(const QModelIndex & )
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
void ConsumpTaskMenu::editShow()
{
    QItemSelectionModel *select = taskMenu->selectionModel();
    int rowNum = select->selectedRows().at(0).row();
    if(rowNum<0) return;
    taskMenu->clearSelection();
    editBtn->setEnabled(0);
    deleteBtn->setEnabled(0);

    createTaskView = new ConsumpTaskCreate(userKey,table.getData(rowNum,0),"Edit",table.getData(rowNum,2),table.getData(rowNum,3),this);
    createTaskView->table = &table;
    createTaskView->showFullScreen();
}

void ConsumpTaskMenu::createShow()
{
    taskMenu->clearSelection();
    editBtn->setEnabled(0);
    deleteBtn->setEnabled(0);

    createTaskView = new ConsumpTaskCreate(userKey,"Create",this);
    createTaskView->table = &table;
    createTaskView->showFullScreen();
}

bool ConsumpTaskMenu::deleteData(QString pri_id)
{
//      QByteArray ba = pri_id.toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);
        QSqlQuery query;
        query.prepare("DELETE FROM consump WHERE pri_id=:pri_id;");
        query.bindValue(":pri_id", pri_id.toInt());

        if(query.exec())
        {
           return true;
        }

        return false;
}
void ConsumpTaskMenu::deleteAllData()
{
   table.table.clear();
   QSqlQuery query;
   query.prepare("DELETE FROM consump");
   query.exec();

}

