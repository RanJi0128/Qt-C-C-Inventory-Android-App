#include "customkeyboard.h"

CustomKeyBoard::CustomKeyBoard(QWidget *parent) : QDialog(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height()/2;
    this->setGeometry(0,height,width,height);

    isUpcase=false;

    interface();
}
void CustomKeyBoard::interface()
{
    for(int i =0;i<26;i++)
    {
        alphabet[i]=new QPushButton(QString(65+i),this);        
        connect(alphabet[i],SIGNAL(clicked()),this,SLOT(keyClickedSlot()));
        alphabet[i]->setObjectName("keyboard");

        if(i<10)
        {
            numeric[i] = new QPushButton(QString::number((i+1)%10),this);            
            connect(numeric[i],SIGNAL(clicked()),this,SLOT(keyClickedSlot()));
            numeric[i]->setObjectName("keyboard");
        }
    }

    specNum = new QPushButton("Spc",this);    
    specNum->setObjectName("keyboard");
    connect(specNum,SIGNAL(clicked()),this,SLOT(speckeyClickedSlot()));

    point = new QPushButton(".",this);    
    point->setObjectName("keyboard");
    connect(point,SIGNAL(clicked()),this,SLOT(keyClickedSlot()));


    txtlabel = new QLabel("Enter Value",this);
    txtlabel->setAlignment(Qt::AlignCenter);

    for(int i=0;i<3;i++)
    {
        enterValue[i]=new QPushButton(this);        
        enterValue[i]->setObjectName("keyboard");

    }
    objectGeometry();
    enterValue[0]->setText("Cancel");
    enterValue[1]->setText("->abc");
    enterValue[2]->setText("Ok");

    connect(enterValue[0],SIGNAL(clicked()),this,SLOT(cancelSlot()));
    connect(enterValue[1],SIGNAL(clicked()),this,SLOT(changeAlphaKey()));
    connect(enterValue[2],SIGNAL(clicked()),this,SLOT(okSlot()));
}
void CustomKeyBoard::cancelSlot()
{
    inputTarget->clear();
    this->close();
}
void CustomKeyBoard::okSlot()
{
    this->close();
}
void CustomKeyBoard::speckeyClickedSlot()
{
    inputTarget->setText(inputTarget->text()+" ");
}
void CustomKeyBoard::keyClickedSlot()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());

    inputTarget->setText(inputTarget->text()+btn->text());


}
void CustomKeyBoard::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    width = size.width();
    height = size.height()/2;
    this->setGeometry(0,height,width,height);

    objectGeometry();
}
void CustomKeyBoard::objectGeometry()
{
    for(int i =0;i<26;i++)
    {
        alphabet[i]->setGeometry(width*7/100+(i%6)*width*15/100,height*3/100+height*12/100*(i/6),width*9/100,height*10/100);

        if(i<10)
        {
            numeric[i]->setGeometry(width*34/100+(i%5)*width*12/100,height*51/100+height*12/100*(i/5),width*9/100,height*10/100);
        }
    }
    specNum->setGeometry(width*7/100,height*63/100,width*16/100,height*10/100);
    point->setGeometry(width*24/100,height*63/100,width*8/100,height*10/100);
    txtlabel->setGeometry(0,height*74/100,width,height*8/100);

    for(int i=0;i<3;i++)
    {
        enterValue[i]->setGeometry(width*7/100+width*33/100*i,height*83/100,width*19/100,height*10/100);
    }

}
void CustomKeyBoard::changeAlphaKey()
{
   isUpcase=!isUpcase;
   if(isUpcase)
    {
       for(int i =0;i<26;i++)
        {
            alphabet[i]->setText(QString(97+i));
        }
        enterValue[1]->setText("->ABC");
    }
   else {
       for(int i =0;i<26;i++)
       {
           alphabet[i]->setText(QString(65+i));
       }
       enterValue[1]->setText("->abc");
   }
}
