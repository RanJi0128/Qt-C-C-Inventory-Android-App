#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "include.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    enum TableRoles{
        Pri_id = Qt::UserRole + 1,
        Key,
        Order,
        Tags

    };
public:
    explicit TableModel(QObject *parent = nullptr);
    
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    
     void getReadAllData(int key);
     bool insertData(QString oderStr, QString lctStr,int key);
     bool updateData(QString oderStr, QString lctStr,int key, QString pri_id);
     QVariant getData(int row,int columnId);
     bool deleteData(QString pri_id);
     void deleteAllData();
     QString getCSVData();

signals:

public slots:

private:

    QVector<QVector<QString>> table;
};

#endif // TABLEMODEL_H
