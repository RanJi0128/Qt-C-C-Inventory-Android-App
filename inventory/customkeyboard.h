#ifndef CUSTOMKEYBOARD_H
#define CUSTOMKEYBOARD_H

#include "include.h"

class CustomKeyBoard : public QDialog
{
      Q_OBJECT
public:
    CustomKeyBoard(QWidget *parent = nullptr);

    QPushButton *alphabet[26];
    QPushButton *numeric[10];
    QPushButton *specNum;
    QPushButton *point;
    QLabel *txtlabel;

    QPushButton *enterValue[3];

    QLineEdit *inputTarget;

    void interface();

    int width;
    int height;
    bool isUpcase;

signals:

public slots:

   void keyClickedSlot();
   void changeAlphaKey();
   void speckeyClickedSlot();
   void cancelSlot();
   void okSlot();



};

#endif // CUSTOMKEYBOARD_H
