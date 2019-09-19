#ifndef DOWNLOADSTATEMODEL_H
#define DOWNLOADSTATEMODEL_H

#include "include.h"

class DownloadStateModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DownloadStateModel(QObject *parent = nullptr);
    
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool insertData(QString filename,int key);
    bool deleteData(QString filename);
    void getReadAllData(int key);


signals:

public slots:

public:

    QVector<QVector<QString>> table;
};

#endif // TABLEMODEL_H
