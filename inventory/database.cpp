#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    m_dbState = 0;
}
DataBase::~DataBase()
{
    closeDataBase();
}
void DataBase::connectToDataBase()
{
    QFile file("./log.txt");
    if(file.exists())
    {
        m_dbState = 1;
        return;
    }
    QFile dfile("assets:/db/" DATABASE_NAME);

    if(!dfile.exists()){

        m_dbState = 1;

    } else {

//        if (QFile::exists("./" DATABASE_NAME))
//        {
//            QFile::remove("./" DATABASE_NAME);
//        }
        dfile.copy("./" DATABASE_NAME);
        QFile::setPermissions("./" DATABASE_NAME,QFile::WriteOwner | QFile::ReadOwner | QFile::ExeOwner);
        this->openDataBase();
    }

}
void DataBase::openDataBase()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("./" DATABASE_NAME);

    if(db.open()){

        m_dbState = 0;

    } else {

        m_dbState = 2;
    }
}
void DataBase::closeDataBase()
{
    db.close();
}

