#include "consumptask.h"


TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{


}

int TableModel::rowCount(const QModelIndex &) const
{

    return table.size();//Number of rows
}

int TableModel::columnCount(const QModelIndex &) const
{
//      QByteArray ba = QString::number(rowCount()).toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);

    if(rowCount() > 0)
      return 2;//Columns
    else
      return 0;

}

QVariant TableModel::data(const QModelIndex &index, int role) const
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
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
                case 0:
                    return QString("Tags");
                case 1:
                    return QString("Work Order");

            }
        }
    }
    return QVariant();
}
QString TableModel::getData(int row, int columnId)
{

    if(rowCount() > 0)
      return table.at(row).at(columnId);

    return nullptr;
}



void TableModel::getReadAllData(int key_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM consump;");
    query.exec();
    table.clear();
    while (query.next()) {

       int key = query.value(1).toInt();
       if(key == key_id)
       {
           QString pri_id = query.value(0).toString();
           QString join_id = query.value(1).toString();
           QString order = query.value(2).toString();
           QString location = query.value(3).toString();
           
           table.append({pri_id,join_id,order,location});
       }
    
    }
 
}
QString TableModel::getCSVData()
{
    QString data=" ";
    data="pri_id,key,order_val,location\n";
    for(int i=0;i<rowCount();i++)
    {
        data = data + table.at(i).at(0)+","+table.at(i).at(1)+","+table.at(i).at(2)+","+table.at(i).at(3)+"\n";
    }
    return data;

}
