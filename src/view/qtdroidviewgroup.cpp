#include "qtdroidviewgroup_p.h"
#include "qtdroidlayoutparams_p.h"
#include "qtdroidfunctions_p.h"
#include "qtdroidcontext_p.h"

QtAndroidViewGroup::QtAndroidViewGroup(QtAndroidView *parent) : QtAndroidView(parent)
{
}

QtAndroidLayoutParams *QtAndroidViewGroup::qmlAttachedProperties(QObject *object)
{
    QtAndroidView *view = qobject_cast<QtAndroidView*>(object);
    if (view)
        return new QtAndroidLayoutParams(view);
    return 0;
}

QAndroidJniObject QtAndroidViewGroup::construct()
{
    return QAndroidJniObject("android/view/ViewGroup",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QtAndroidViewGroup::inflate()
{
    QtAndroidView::inflate();

    foreach (QtAndroidView *child, m_children) {
        child->setInstance(child->construct());
        child->inflate();
        instance().callMethod<void>("addView", "(Landroid/view/View;)V", child->instance().object());
    }
}

void QtAndroidViewGroup::viewChange(ViewChange change, const ViewChangeData &data)
{
    QAndroidJniObject group = instance();
    switch (change) {
    case ViewChildAddedChange: // data.view
        if (group.isValid()) {
            QtAndroid::callFunction([=]() {
                QAndroidJniObject child = data.view->construct();
                data.view->setInstance(child);
                data.view->inflate();
                group.callMethod<void>("addView", "(Landroid/view/View;)V", child.object());
            });
        }
        break;
    case ViewChildRemovedChange: // data.view
        if (group.isValid()) {
            QAndroidJniObject child = data.view->instance();
            QtAndroid::callFunction([=]() {
                group.callMethod<void>("removeView", "(Landroid/view/View;)V", child.object());
            });
            data.view->setInstance(QAndroidJniObject());
        }
        break;
    default:
        break;
    }
}
