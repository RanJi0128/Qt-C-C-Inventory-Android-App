
#include "mainwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("assets:/style.qss" );
//    QFile file("./assets/style.qss" );
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    DataBase db;
    db.connectToDataBase();

    MainWindow w(db.m_dbState);
    w.showFullScreen();

   return a.exec();
}
