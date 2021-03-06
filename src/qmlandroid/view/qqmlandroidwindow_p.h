#ifndef QQMLANDROIDWINDOW_P_H
#define QQMLANDROIDWINDOW_P_H

#include "qqmlandroidcontextual_p.h"
#include "qqmlandroidoptional_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidWindow : public QQmlAndroidContextual
{
    Q_OBJECT
    Q_PROPERTY(int statusBarColor READ statusBarColor WRITE setStatusBarColor NOTIFY statusBarColorChanged)

public:
    explicit QQmlAndroidWindow(QQmlAndroidContext *context);

    int statusBarColor() const;
    void setStatusBarColor(int color);

Q_SIGNALS:
    void statusBarColorChanged();

protected:
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;

private:
    QQmlAndroidOptional<int> m_statusBarColor;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDWINDOW_P_H
