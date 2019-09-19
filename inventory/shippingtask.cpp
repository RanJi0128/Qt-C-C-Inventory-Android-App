#include "shippingtask.h"


ShippingTableModel::ShippingTableModel(QObject *parent) : QAbstractTableModel(parent)
{


}

int ShippingTableModel::rowCount(const QModelIndex &) const
{

    return table.size();//Number of rows
}

int ShippingTableModel::columnCount(const QModelIndex &) const
{
//      QByteArray ba = QString::number(rowCount()).toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);

    if(rowCount() > 0)
      return 2;//Columns
    else
      return 0;

}

QVariant ShippingTableModel::data(const QModelIndex &index, int role) const
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
QVariant ShippingTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
                case 0:
                    return QString("Tags");
                case 1:
                    return QString("OrderNumber");

            }
        }
    }
    return QVariant();
}
QString ShippingTableModel::getData(int row, int columnId)
{

    if(rowCount() > 0)
      return table.at(row).at(columnId);

    return nullptr;
}



void ShippingTableModel::getReadAllData(int key_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM shipping ;");
    query.exec();
    table.clear();
    while (query.next()) {

       int key = query.value(1).toInt();
       if(key == key_id)
       {
           QString pri_id = query.value(0).toString();
           QString join_id = query.value(1).toString();
           QString order = query.value(2).toString();
           QString ship_val = query.value(3).toString();
           
           table.append({pri_id,join_id,order,ship_val});
       }
    
    }
 
}
QString ShippingTableModel::getCSVData()
{
    QString data=" ";
    data="pri_id,key,order_val,ship_val\n";
    for(int i=0;i<rowCount();i++)
    {
        data = data + table.at(i).at(0)+","+table.at(i).at(1)+","+table.at(i).at(2)+","+table.at(i).at(3)+"\n";
    }
    return data;

}
