#include "downloadstate.h"


DownloadStateModel::DownloadStateModel(QObject *parent) : QAbstractTableModel(parent)
{


}

int DownloadStateModel::rowCount(const QModelIndex &) const
{

    return table.size();//Number of rows
}

int DownloadStateModel::columnCount(const QModelIndex &) const
{
//      QByteArray ba = QString::number(rowCount()).toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);

    if(rowCount() > 0)
      return 2;//Columns
    else
      return 0;

}

QVariant DownloadStateModel::data(const QModelIndex &index, int role) const
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
QVariant DownloadStateModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
                case 0:
                    return QString("Tags");
                case 1:
                    return QString("Downloading");

            }
        }
    }
    return QVariant();
}

void DownloadStateModel::getReadAllData(int key_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM download;");
    query.exec();
    table.clear();
    while (query.next()) {

       int key = query.value(1).toInt();
       if(key == key_id)
       {
           QString pri_id = query.value(0).toString();
           QString join_id = query.value(1).toString();
           QString filename = query.value(2).toString();
           table.append({pri_id,join_id,filename});
       }
    
    }
 
}
bool DownloadStateModel::insertData(QString filename,int key)
{

       QSqlQuery query;
       query.prepare("SELECT name FROM download WHERE name = :name");
       query.bindValue(":name", filename);
       if(query.exec())
       {
           if(query.first())
           {
             return false;
           }

       }
       else {
         return false;
       }
       query.prepare("INSERT INTO download (key_id, name) VALUES (:key_id, :name)");
       query.bindValue(":key_id", key);
       query.bindValue(":name", filename);
       if(query.exec())
       {
           return true;
       }

       return false;
}
bool DownloadStateModel::deleteData(QString filename)
{
//      QByteArray ba = pri_id.toLocal8Bit();
//      const char *c_str2 = ba.data();
//    __android_log_write(ANDROID_LOG_INFO,"call-------------->",c_str2);
        QSqlQuery query;
        query.prepare("DELETE FROM download WHERE name=:name;");
        query.bindValue(":name", filename);

        if(query.exec())
        {
           return true;
        }

        return false;
}
