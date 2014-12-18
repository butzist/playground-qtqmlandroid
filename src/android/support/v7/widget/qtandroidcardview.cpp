#include "qtandroidcardview_p.h"

QT_BEGIN_NAMESPACE

QtAndroidCardView::QtAndroidCardView(QtAndroidView *parent) :
    QtAndroidFrameLayout(parent)
{
}

QAndroidJniObject QtAndroidCardView::onCreate()
{
    return QAndroidJniObject("android/support/v7/widget/CardView",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QtAndroidCardView::onInflate(QAndroidJniObject &instance)
{
    QtAndroidFrameLayout::onInflate(instance);
}

QT_END_NAMESPACE