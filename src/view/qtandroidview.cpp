#include "qtandroidview_p.h"
#include "qtandroidcontext_p.h"
#include "qtandroidfunctions_p.h"
#include "qtandroidlayoutparams_p.h"
#include <QtCore/qcoreapplication.h>
#include <QtCore/qhash.h>

QtAndroidView::QtAndroidView(QtAndroidView *parent) : QtAndroidObject(parent),
    m_context(0), m_parent(0), m_layoutParamsDirty(false), m_layoutParams(0), m_x(0), m_y(0), m_width(0), m_height(0)
{
    static int id = 0;
    m_id = ++id;

    if (parent)
        setParentView(parent);
}

QtAndroidView::~QtAndroidView()
{
    if (m_parent)
        setParentView(0);
}

int QtAndroidView::identifier() const
{
    return m_id;
}

void QtAndroidView::setIdentifier(int identifier)
{
    m_id = identifier;
}

QAndroidJniObject QtAndroidView::ctx() const
{
    if (!m_context)
        return QAndroidJniObject();
    return m_context->instance();
}

QtAndroidContext *QtAndroidView::context() const
{
    return m_context;
}

void QtAndroidView::setContext(QtAndroidContext *context)
{
    if (m_context != context) {
        m_context = context;
        foreach (QtAndroidView *child, m_children)
            child->setContext(context);
        viewChange(ViewContextChange, context);
        emit contextChanged();
    }
}

QtAndroidView *QtAndroidView::parentView() const
{
    return m_parent;
}

void QtAndroidView::setParentView(QtAndroidView *parent)
{
    if (m_parent != parent) {
        if (m_parent)
            m_parent->removeChild(this);
        m_parent = parent;
        viewChange(ViewParentChange, parent);
        if (parent)
            parent->addChild(this);
        emit parentChanged();
    }
}

QList<QtAndroidView *> QtAndroidView::childViews() const
{
    return m_children;
}

QQmlListProperty<QtAndroidView> QtAndroidView::children()
{
    return QQmlListProperty<QtAndroidView>(this, 0, &QtAndroidView::children_append, &QtAndroidView::children_count,
                                                   &QtAndroidView::children_at, &QtAndroidView::children_clear);
}

bool QtAndroidView::hasFocus() const
{
    if (m_focus.isNull())
        return false;
    return m_focus.value();
}

bool QtAndroidView::updateFocus(bool arg)
{
    if (arg != hasFocus()) {
        m_focus = arg;
        emit focusChanged();
        return true;
    }
    return false;
}

qreal QtAndroidView::x() const
{
    return m_x;
    //return jniObject().callMethod<jfloat>("getX");
}

void QtAndroidView::setX(qreal x)
{
    if (m_x != x) {
        m_x = x;
        //jniObject().callMethod<jfloat>("setX", "(F)V", x);
    }
}

qreal QtAndroidView::y() const
{
    return m_y;
    //return jniObject().callMethod<jfloat>("getY");
}

void QtAndroidView::setY(qreal y)
{
    if (m_y != y) {
        m_y = y;
        //jniObject().callMethod<jfloat>("setX", "(F)V", y);
    }
}

qreal QtAndroidView::width() const
{
    return m_width;
    //return jniObject().callMethod<jfloat>("getWidth");
}

void QtAndroidView::setWidth(qreal width)
{
    if (m_width != width) {
        m_width = width;
        //jniObject().callMethod<jfloat>("setWidth", "(F)V", width);
    }
}

qreal QtAndroidView::height() const
{
    return m_height;
    //return jniObject().callMethod<jfloat>("getHeight");
}

void QtAndroidView::setHeight(qreal height)
{
    if (m_height != height) {
        m_height = height;
        //jniObject().callMethod<jfloat>("setHeight", "(F)V", height);
    }
}

void QtAndroidView::viewChange(ViewChange change, const ViewChangeData &data)
{
    switch (change) {
    case ViewContextChange:      // data.context
    case ViewParentChange:       // data.view
    case ViewChildAddedChange:   // data.view
    case ViewChildRemovedChange: // data.view
    case ViewVisibilityChange:   // data.boolean
    default:
        break;
    }
}

void QtAndroidView::addChild(QtAndroidView *child)
{
    if (!m_children.contains(child)) {
        m_children.append(child);
        child->setContext(m_context);
        viewChange(ViewChildAddedChange, child);
        emit childrenChanged();
    }
}

void QtAndroidView::removeChild(QtAndroidView *child)
{
    if (m_children.removeOne(child)) {
        viewChange(ViewChildRemovedChange, child);
        emit childrenChanged();
    }
}

void QtAndroidView::children_append(QQmlListProperty<QtAndroidView> *list, QtAndroidView *child)
{
    if (QtAndroidView *that = qobject_cast<QtAndroidView *>(list->object))
        that->addChild(child);
}

int QtAndroidView::children_count(QQmlListProperty<QtAndroidView> *list)
{
    if (QtAndroidView *that = qobject_cast<QtAndroidView *>(list->object))
        return that->m_children.count();
    return 0;
}

QtAndroidView *QtAndroidView::children_at(QQmlListProperty<QtAndroidView> *list, int index)
{
    if (QtAndroidView *that = qobject_cast<QtAndroidView *>(list->object))
        return that->m_children.at(index);
    return 0;
}

void QtAndroidView::children_clear(QQmlListProperty<QtAndroidView> *list)
{
    if (QtAndroidView *that = qobject_cast<QtAndroidView *>(list->object)) {
        while (!that->m_children.isEmpty())
            that->m_children.first()->setParentView(0);
    }
}

QAndroidJniObject QtAndroidView::construct()
{
    return QAndroidJniObject("android/view/View",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QtAndroidView::inflate()
{
    QAndroidJniObject view = instance();
    m_listener = QAndroidJniObject("qt/android/view/QtViewListener",
                                   "(Landroid/view/View;J)V",
                                   view.object(),
                                   reinterpret_cast<jlong>(this));

    view.callMethod<void>("setId", "(I)V", m_id);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeMethods(m_listener.object());
        nativeMethodsRegistered = true;
    }

    invalidateLayoutParams();
}

void QtAndroidView::registerNativeMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onClick", "(J)V", reinterpret_cast<void *>(onClick)},
                               {"onFocusChange", "(JZ)V", reinterpret_cast<void *>(onFocusChange)},
                               {"onLayoutChange", "(JIIII)V", reinterpret_cast<void *>(onLayoutChange)}
                               /*{"onLongClick", "(J)V", reinterpret_cast<void *>(onLongClick)}*/};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

void QtAndroidView::onClick(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QtAndroidView *view = reinterpret_cast<QtAndroidView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "click", Qt::QueuedConnection);
}

void QtAndroidView::onFocusChange(JNIEnv *env, jobject object, jlong instance, jboolean hasFocus)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QtAndroidView *view = reinterpret_cast<QtAndroidView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "updateFocus", Qt::QueuedConnection, Q_ARG(bool, hasFocus));
}

#include <QtDebug>
void QtAndroidView::onLayoutChange(JNIEnv *env, jobject object, jlong instance, jint top, jint left, jint right, jint bottom)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QtAndroidView *view = reinterpret_cast<QtAndroidView *>(instance);
    if (view) {
        //qDebug() << "onLayoutChange:" << view << top << left << right << bottom;
    }
}

bool QtAndroidView::onLongClick(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QtAndroidView *view = reinterpret_cast<QtAndroidView *>(instance);
    if (view) {
        //qDebug() << "onLongClick:" << view;
        QMetaObject::invokeMethod(view, "longClick", Qt::QueuedConnection);
    }
    return true; // TODO: accept
}

bool QtAndroidView::event(QEvent *event)
{
    if (event->type() == QEvent::Polish) {
        QtAndroidView *view = qobject_cast<QtAndroidView *>(parent());
        if (view)
            setParentView(view);
    }
    return QtAndroidObject::event(event);
}

void QtAndroidView::customEvent(QEvent *event)
{
    Q_UNUSED(event);
    if (m_layoutParamsDirty && m_layoutParams && instance().isValid()) {
        m_layoutParams->apply(this);
        m_layoutParamsDirty = false;
    }
}

void QtAndroidView::invalidateLayoutParams()
{
    if (!m_layoutParamsDirty && m_layoutParams && instance().isValid()) {
        m_layoutParamsDirty = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::User));
    }
}

void QtAndroidView::setLayoutParams(QtAndroidLayoutParams *params)
{
    if (m_layoutParams != params) {
        m_layoutParams = params;
        invalidateLayoutParams();
    }
}