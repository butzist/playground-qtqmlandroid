#ifndef QQMLANDROIDDATEPICKER_P_H
#define QQMLANDROIDDATEPICKER_P_H

#include "qqmlandroidframelayout_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidDatePicker : public QQmlAndroidFrameLayout
{
    Q_OBJECT

public:
    explicit QQmlAndroidDatePicker(QQmlAndroidView *parent = 0);

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDDATEPICKER_P_H
