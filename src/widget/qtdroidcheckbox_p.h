#ifndef QTDROIDCHECKBOX_P_H
#define QTDROIDCHECKBOX_P_H

#include "qtdroidcompoundbutton_p.h"

QT_BEGIN_NAMESPACE

class QtAndroidCheckBox : public QtAndroidCompoundButton
{
    Q_OBJECT

public:
    explicit QtAndroidCheckBox(QtAndroidView *parent = 0);

protected:
    QAndroidJniObject construct() Q_DECL_OVERRIDE;
    void inflate() Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QTDROIDCHECKBOX_P_H
