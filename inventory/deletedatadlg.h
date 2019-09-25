#ifndef DELETEDATADLG_H
#define DELETEDATADLG_H

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QToolButton>
#include <QPushButton>
#include <QDomElement>

class DeleteDataDlg : public QDialog
{
    Q_OBJECT
public:
    DeleteDataDlg(QWidget *parent = nullptr);

    QLabel *line;
    QToolButton *imgButton;
    QLabel *title;
    QLabel *text;
    QCheckBox *cb_1,*cb_2;
    QPushButton *okBtn, *cancelBtn;
    int width;
    int height;

    QDomElement root;

    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event)override;
    void objectGeometry();

signals:
    void allDelete(int);
    void oneDelete(int);
    void downloadDelete(int);
    void downloadAllDelete(int);


public slots:

    void okSlot();



};

#endif // DELETEDATADLG_H
