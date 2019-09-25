#include "inventorytask.h"
#include "extern.h"

InventoryTableModel::InventoryTableModel(QObject *parent) : QAbstractTableModel(parent)
{

    root = doc.documentElement().firstChildElement("InventoryTaskMenu");
}

int InventoryTableModel::rowCount(const QModelIndex &) const
{

    return table.size();//Number of rows
}

int InventoryTableModel::columnCount(const QModelIndex &) const
{
//      QByteArray ba = QString::number(rowCount()).toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);

    if(rowCount() > 0)
      return 2;//Columns
    else
      return 0;

}

QVariant InventoryTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if(rowCount() > 0)
    {
        switch(role){

            case Qt::DisplayRole:

               if(col > 0)
                 return table.at(row).at(2);
               else {
                   return row+1;
               }

            case Qt::TextAlignmentRole:

                return Qt::AlignCenter;

            }

    }

    return QVariant();

}
QVariant InventoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
                case 0:
                    return QString(root.firstChildElement("taskModelCol_1").text());
                case 1:
                    return QString(root.firstChildElement("taskModelCol_2").text());

            }
        }
    }
    return QVariant();
}
QString InventoryTableModel::getData(int row, int columnId)
{

    if(rowCount() > 0)
      return table.at(row).at(columnId);

    return nullptr;
}



void InventoryTableModel::getReadAllData(int key_id)
{
    beginInsertRows(QModelIndex(),0,rowCount());
    QSqlQuery query;
    query.prepare("SELECT * FROM inventory;");
    query.exec();
    table.clear();
    while (query.next()) {

       int key = query.value(1).toInt();
       if(key == key_id)
       {
           QString pri_id = query.value(0).toString();
           QString join_id = query.value(1).toString();
           QString physical = query.value(2).toString();
           QString location = query.value(3).toString();
           QString sub_location = query.value(4).toString();
           QString c_time = query.value(5).toString();
           QString m_time = query.value(6).toString();

           table.append({pri_id,join_id,physical,location,sub_location,c_time,m_time});

       }
    
    }
    endInsertRows();
 
}
QString InventoryTableModel::getCSVData(int key_id)
{
    getReadAllData(key_id);
    QString data=" ";
    data="pri_id,key,physical,location,sub_location,c_time,m_time\n";
    for(int i=0;i<rowCount();i++)
    {
        data = data + table.at(i).at(0)+","+table.at(i).at(1)+","+table.at(i).at(2)+","+table.at(i).at(3)+","+table.at(i).at(4)+","+table.at(i).at(5)+","+table.at(i).at(6)+"\n";
    }
    return data;

}

void InventoryTableModel::deleteAllData()
{
   table.clear();
   QSqlQuery query;
   query.prepare("DELETE FROM inventory");
   query.exec();

}
