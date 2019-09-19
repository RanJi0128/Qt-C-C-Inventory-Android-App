
#include "mainwindow.h"
#include "database.h"

static QObject *pRootObject = nullptr;

void AndroidBatteryStateChanged(JNIEnv *env, jobject thiz, jint level, jboolean onCharge)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

   static_cast<MainWindow*>(pRootObject)->androidBatteryStateChanged(level,onCharge);

}

void InitializeForAndroidBattery()
{

    JNINativeMethod methods[] = {

            {  "BatteryStateChanged","(IZ)V",reinterpret_cast<void*>(AndroidBatteryStateChanged) }
        };

    QAndroidJniObject batteryLevel_j("com/jni/systeminfo/BatteryLevelListener");

    QAndroidJniEnvironment env;

    jclass objectClass = env->GetObjectClass(batteryLevel_j.object<jobject>());

    env->RegisterNatives(objectClass,methods,sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);

   // batteryLevel_j.callMethod<void>("InstallBatteryListener");
    QAndroidJniObject::callStaticMethod<void>("com/jni/systeminfo/BatteryLevelListener", "InstallBatteryListener");

}
void AndroidSystemInformation(JNIEnv *env, jobject thiz, jstring body)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    if(pRootObject != nullptr)
    {
        QAndroidJniObject string = body;
        QString qstring = string.toString();

        static_cast<MainWindow*>(pRootObject)->androidSysteminfo(qstring);

    }

}
void InitializeForAndroidInformation()
{
    JNINativeMethod methods[] = {

            {  "SystemInformation","(Ljava/lang/String;)V",reinterpret_cast<void*>(AndroidSystemInformation) }
        };
     QAndroidJniObject sysInfor_j("com/jni/systeminfo/DeviceInformation");

     QAndroidJniEnvironment env;

     jclass objectClass = env->GetObjectClass(sysInfor_j.object<jobject>());

     env->RegisterNatives(objectClass,methods,sizeof(methods) / sizeof(methods[0]));
     env->DeleteLocalRef(objectClass);


     QAndroidJniObject::callStaticMethod<void>("com/jni/systeminfo/DeviceInformation", "sendInformation","(Landroid/content/Context;)V",
                                               QtAndroid::androidContext().object<jobject>());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//  QFile file("./assets/style.qss" );  //--desktop

    QFile file("assets:/style.qss" );

    QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
    QAndroidJniObject mediaPath = mediaDir.callObjectMethod( "getAbsolutePath", "()Ljava/lang/String;" );
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject package = activity.callObjectMethod("getPackageName", "()Ljava/lang/String;");

    QString dataAbsPath = mediaPath.toString()+"/Android/data/"+package.toString()+"/style";

    QDir dir;
    dir.mkpath(dataAbsPath);
    dataAbsPath=dataAbsPath+"/style.qss";
//    if (QFile::exists(dataAbsPath))
//    {
//        QFile::remove(dataAbsPath);
//    }

    file.copy(dataAbsPath);
    QFile::setPermissions(dataAbsPath,QFile::WriteOwner | QFile::ReadOwner | QFile::ExeOwner);

    QFile file_e(dataAbsPath );
    file_e.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file_e.readAll());
    a.setStyleSheet(styleSheet);
    file_e.close();

    DataBase db;
    db.connectToDataBase();

    MainWindow w(db.m_dbState);
    w.showFullScreen();

    pRootObject=&w;
    InitializeForAndroidBattery();
    InitializeForAndroidInformation();

   return a.exec();
}
