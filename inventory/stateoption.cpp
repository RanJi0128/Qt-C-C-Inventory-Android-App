#include "stateoption.h"
#include "extern.h"

StateOption::StateOption(QWidget *parent,int key) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();

    userKey = key;
    interface();
}
void StateOption::interface()
{
    root = doc.documentElement().firstChildElement("StateOption");

    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText(root.firstChildElement("pageTitle").text());
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
    taskMenu->setSelectionMode(QAbstractItemView::NoSelection);
    taskMenu->verticalHeader()->setDefaultSectionSize(taskMenu->height()*8/100);
    taskMenu->setColumnWidth(0,taskMenu->width()/3);

}
