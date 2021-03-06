#include "qqmlandroidrotateanimation_p.h"

QT_BEGIN_NAMESPACE

QQmlAndroidRotateAnimation::QQmlAndroidRotateAnimation(QObject *parent) :
    QQmlAndroidAnimation(parent), m_from(0), m_to(0),
    m_pivotX(0), m_pivotY(0), m_pivotXType(ABSOLUTE), m_pivotYType(ABSOLUTE)
{
}

qreal QQmlAndroidRotateAnimation::fromDegrees() const
{
    return m_from;
}

void QQmlAndroidRotateAnimation::setFromDegrees(qreal degrees)
{
    if (m_from != degrees) {
        m_from = degrees;
        emit fromDegreesChanged();
    }
}

qreal QQmlAndroidRotateAnimation::toDegrees() const
{
    return m_to;
}

void QQmlAndroidRotateAnimation::setToDegrees(qreal degrees)
{
    if (m_to != degrees) {
        m_to = degrees;
        emit toDegreesChanged();
    }
}

qreal QQmlAndroidRotateAnimation::pivotX() const
{
    return m_pivotX;
}

void QQmlAndroidRotateAnimation::setPivotX(qreal pivotX)
{
    if (m_pivotX != pivotX) {
        m_pivotX = pivotX;
        emit pivotXChanged();
    }
}

qreal QQmlAndroidRotateAnimation::pivotY() const
{
    return m_pivotY;
}

void QQmlAndroidRotateAnimation::setPivotY(qreal pivotY)
{
    if (m_pivotY != pivotY) {
        m_pivotY = pivotY;
        emit pivotYChanged();
    }
}

QQmlAndroidRotateAnimation::Relation QQmlAndroidRotateAnimation::pivotXType() const
{
    return m_pivotXType;
}

void QQmlAndroidRotateAnimation::setPivotXType(Relation type)
{
    if (m_pivotXType != type) {
        m_pivotXType = type;
        emit pivotXTypeChanged();
    }
}

QQmlAndroidRotateAnimation::Relation QQmlAndroidRotateAnimation::pivotYType() const
{
    return m_pivotYType;
}

void QQmlAndroidRotateAnimation::setPivotYType(Relation type)
{
    if (m_pivotYType != type) {
        m_pivotYType = type;
        emit pivotYTypeChanged();
    }
}

QAndroidJniObject QQmlAndroidRotateAnimation::onCreate()
{
    return QAndroidJniObject("android/view/animation/RotateAnimation",
                             "(FFIFIF)V",
                             m_from, m_to,
                             m_pivotXType, m_pivotX, m_pivotYType, m_pivotY);
}

QT_END_NAMESPACE
