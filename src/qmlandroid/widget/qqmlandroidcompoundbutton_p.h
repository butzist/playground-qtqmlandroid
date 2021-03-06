#ifndef QQMLANDROIDCOMPOUNDBUTTON_P_H
#define QQMLANDROIDCOMPOUNDBUTTON_P_H

#include "qqmlandroidbutton_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidCompoundButton : public QQmlAndroidButton
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY checkedChanged)

public:
    explicit QQmlAndroidCompoundButton(QQmlAndroidView *parent = 0);

    bool isChecked() const;
    void setChecked(bool checked);

public Q_SLOTS:
    void toggle();

Q_SIGNALS:
    void checkedChanged();

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;

    static void onRegisterNativeMethods(jobject listener);
    static void onCheckedChanged(JNIEnv *env, jobject object, jlong instance, jboolean isChecked);

private Q_SLOTS:
    bool updateChecked(bool checked);

private:
    bool m_checked;
    QAndroidJniObject m_listener;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDCOMPOUNDBUTTON_P_H
