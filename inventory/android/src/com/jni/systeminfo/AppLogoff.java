
package com.jni.systeminfo;

import android.content.IntentFilter;
import android.content.Intent;

import android.content.pm.PackageManager;
import android.content.Context;
import android.provider.Settings;

public class AppLogoff {

    public static native void logoff();

    public static void startLogoff(){

        logoff();
    }

}
