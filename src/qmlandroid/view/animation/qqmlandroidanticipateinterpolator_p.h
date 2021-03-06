#ifndef QQMLANDROIDANTICIPATEINTERPOLATOR_P_H
#define QQMLANDROIDANTICIPATEINTERPOLATOR_P_H

#include "qqmlandroidinterpolator_p.h"
#include "qqmlandroidoptional_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidAnticipateInterpolator : public QQmlAndroidInterpolator
{
    Q_OBJECT
    Q_PROPERTY(qreal tension READ tension WRITE setTension NOTIFY tensionChanged)

public:
    explicit QQmlAndroidAnticipateInterpolator(QObject *parent = 0);

    qreal tension() const;
    void setTension(qreal tension);

Q_SIGNALS:
    void tensionChanged();

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;

private:
    QQmlAndroidOptional<qreal> m_tension;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDANTICIPATEINTERPOLATOR_P_H
