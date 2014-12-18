#ifndef QTANDROIDEDITTEXT_P_H
#define QTANDROIDEDITTEXT_P_H

#include "qtandroidtextview_p.h"

QT_BEGIN_NAMESPACE

class QtAndroidEditText : public QtAndroidTextView
{
    Q_OBJECT

public:
    explicit QtAndroidEditText(QtAndroidView *parent = 0);

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QTANDROIDEDITTEXT_P_H