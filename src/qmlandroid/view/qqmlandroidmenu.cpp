#include "qqmlandroidmenu_p.h"
#include "qqmlandroidmenuitem_p.h"

QT_BEGIN_NAMESPACE

QQmlAndroidMenu::QQmlAndroidMenu(QObject *parent) :
    QQmlAndroidContextual(parent)
{
}

QList<QQmlAndroidMenuItem *> QQmlAndroidMenu::items() const
{
    QList<QQmlAndroidMenuItem *> lst;
    foreach (QObject *child, children()) {
        QQmlAndroidMenuItem *item = qobject_cast<QQmlAndroidMenuItem *>(child);
        if (item)
            lst += item;
    }
    return lst;
}

QAndroidJniObject QQmlAndroidMenu::onCreate()
{
    return QAndroidJniObject("qt/android/view/QmlMenu");
}

void QQmlAndroidMenu::onInflate(QAndroidJniObject &instance)
{
    foreach (QQmlAndroidMenuItem *item, items()) {
        item->construct();
        if (item->isValid())
            instance.callMethod<void>("add", "(Lqt/android/view/QmlMenuItem;)V", item->instance().object());
    }
}

QT_END_NAMESPACE
