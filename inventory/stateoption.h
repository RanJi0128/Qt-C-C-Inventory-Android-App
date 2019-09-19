#ifndef STATEOPTION_H
#define STATEOPTION_H

#include "include.h"
#include "downloadstate.h"

class StateOption : public QMainWindow
{
    Q_OBJECT
public:
    explicit StateOption(QWidget *parent = nullptr,int key=0);

    QLabel* pageTitle;
    QTableView *taskMenu;
    DownloadStateModel table;

    int userKey;
    int width;
    int height;

    void interface();

signals:

public slots:
};

#endif // GENERALOPTION_H
