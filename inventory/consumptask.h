#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "include.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);
    
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

     void getReadAllData(int key);
     QString getData(int row,int columnId);
     QString getCSVData(int key_id);
     void deleteAllData();

     QDomElement root;


signals:

public slots:

public:

    QVector<QVector<QString>> table;
};

#endif // TABLEMODEL_H
