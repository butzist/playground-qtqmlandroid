#ifndef QQMLANDROIDDECELERATEINTERPOLATOR_P_H
#define QQMLANDROIDDECELERATEINTERPOLATOR_P_H

#include "qqmlandroidinterpolator_p.h"
#include "qqmlandroidoptional_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidDecelerateInterpolator : public QQmlAndroidInterpolator
{
    Q_OBJECT
    Q_PROPERTY(qreal factor READ factor WRITE setFactor NOTIFY factorChanged)

public:
    explicit QQmlAndroidDecelerateInterpolator(QObject *parent = 0);

    qreal factor() const;
    void setFactor(qreal factor);

Q_SIGNALS:
    void factorChanged();

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;

private:
    QQmlAndroidOptional<qreal> m_factor;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDDECELERATEINTERPOLATOR_P_H
