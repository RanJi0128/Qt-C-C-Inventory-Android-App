#ifndef LANGUAGEOPTION_H
#define LANGUAGEOPTION_H

#include "include.h"
class LanguageOption : public QMainWindow
{
    Q_OBJECT
public:
    explicit LanguageOption(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event)override;
    void objectGeometry();
    QLabel* pageTitle;
    QDomElement root;

    int width;
    int height;

    void interface();

signals:

public slots:
};

#endif // GENERALOPTION_H
