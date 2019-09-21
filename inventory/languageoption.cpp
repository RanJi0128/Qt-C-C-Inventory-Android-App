#include "languageoption.h"
#include "extern.h"

LanguageOption::LanguageOption(QWidget *parent) : QMainWindow(parent)
{
    QSize size = qApp->screens()[0]->size();
    width = size.width();
    height = size.height();

    interface();
}
void LanguageOption::interface()
{
    root = doc.documentElement().firstChildElement("LanguageOption");

    pageTitle = new QLabel(this);
    pageTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageTitle->setAlignment(Qt::AlignHCenter);
    pageTitle->setText(root.firstChildElement("pageTitle").text());
    pageTitle->setObjectName("title");
    pageTitle->setGeometry(0,height*11/100,width,height*6/100);


}
