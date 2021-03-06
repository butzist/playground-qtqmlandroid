#include "qqmlandroidactionbardrawertoggle_p.h"

QT_BEGIN_NAMESPACE

QQmlAndroidActionBarDrawerToggle::QQmlAndroidActionBarDrawerToggle(QObject *parent) :
    QQmlAndroidObject(parent)
{
}

void QQmlAndroidActionBarDrawerToggle::onCreate(const QAndroidJniObject &activity, const QAndroidJniObject &drawer)
{
    QAndroidJniObject toggle("android/support/v7/app/ActionBarDrawerToggle",
                             "(Landroid/app/Activity;Landroid/support/v4/widget/DrawerLayout;II)V",
                             activity.object(),
                             drawer.object(),
                             17039375,  // TODO: R.string.drawer_open
                             17039375); // TODO: R.string.drawer_close
    drawer.callMethod<void>("setDrawerListener", "(Landroid/support/v4/widget/DrawerLayout$DrawerListener;)V", toggle.object());
    toggle.callMethod<void>("syncState");
    inflate(toggle);
}

QT_END_NAMESPACE
