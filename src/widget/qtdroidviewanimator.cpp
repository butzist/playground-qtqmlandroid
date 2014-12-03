#include "qtdroidviewanimator_p.h"
#include "qtdroidfunctions_p.h"

QtDroidViewAnimator::QtDroidViewAnimator(QtDroidView *parent) : QtDroidFrameLayout(parent)
{
}

int QtDroidViewAnimator::displayedChild() const
{
    if (m_displayedChild.isNull())
        return 0;
    return m_displayedChild.value();
}

void QtDroidViewAnimator::setDisplayedChild(int child)
{
    if (child != displayedChild()) {
        m_displayedChild = child;
        QtDroid::callIntMethod(instance(), "setDisplayedChild", child);
        emit displayedChildChanged();
    }
}

void QtDroidViewAnimator::showNext()
{
    QtDroid::callVoidMethod(instance(), "showNext");
}

void QtDroidViewAnimator::showPrevious()
{
    QtDroid::callVoidMethod(instance(), "showPrevious");
}

QAndroidJniObject QtDroidViewAnimator::construct(jobject context)
{
    return QAndroidJniObject("android/widget/ViewAnimator",
                             "(Landroid/content/Context;)V",
                             context);
}

void QtDroidViewAnimator::inflate(jobject context)
{
    QtDroidFrameLayout::inflate(context);

    if (!m_displayedChild.isNull())
        QtDroid::callIntMethod(instance(), "setDisplayedChild", m_displayedChild.value());
}
