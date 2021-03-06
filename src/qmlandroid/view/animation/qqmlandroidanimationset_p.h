#ifndef QQMLANDROIDANIMATIONSET_P_H
#define QQMLANDROIDANIMATIONSET_P_H

#include "qqmlandroidanimation_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidAnimationSet : public QQmlAndroidAnimation
{
    Q_OBJECT
    Q_PROPERTY(bool shareInterpolator READ shareInterpolator WRITE setShareInterpolator NOTIFY shareInterpolatorChanged)

public:
    explicit QQmlAndroidAnimationSet(QObject *parent = 0);

    bool shareInterpolator() const;
    void setShareInterpolator(bool share);

Q_SIGNALS:
    void shareInterpolatorChanged();

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;

private:
    bool m_shareInterpolator;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDANIMATIONSET_P_H
