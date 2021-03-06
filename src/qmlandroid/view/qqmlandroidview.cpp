#include "qqmlandroidview_p.h"
#include "qqmlandroiddrawable_p.h"
#include "qqmlandroidcolordrawable_p.h"
#include "qqmlandroidlayoutparams_p.h"
#include "qqmlandroidanimation_p.h"
#include "qtqmlandroidfunctions_p.h"
#include <QtCore/qcoreapplication.h>
#include <QtCore/qcoreevent.h>
#include <QtCore/qhash.h>

QT_BEGIN_NAMESPACE

QQmlAndroidView::QQmlAndroidView(QQmlAndroidView *parent) :
    QQmlAndroidContextual(parent), m_parent(0), m_background(0), m_backgroundResource(0),
    m_animation(0), m_polishing(false), m_visible(true), m_layoutParams(0),
    m_top(0), m_left(0), m_right(0), m_bottom(0)
{
    static int id = 0;
    m_id = ++id;

    if (parent)
        setParentView(parent);

    // TODO: find a better place for this (upon construction of the native control perhaps?)
    requestPolish();
}

QQmlAndroidView::~QQmlAndroidView()
{
    foreach (QQmlAndroidView *child, m_children)
        child->setParentView(0);
    if (m_parent)
        setParentView(0);
}

int QQmlAndroidView::identifier() const
{
    return m_id;
}

void QQmlAndroidView::setIdentifier(int identifier)
{
    m_id = identifier;
}

QQmlAndroidView *QQmlAndroidView::parentView() const
{
    return m_parent;
}

void QQmlAndroidView::setParentView(QQmlAndroidView *parent)
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

QList<QQmlAndroidView *> QQmlAndroidView::childViews() const
{
    return m_children;
}

QQmlListProperty<QQmlAndroidView> QQmlAndroidView::children()
{
    return QQmlListProperty<QQmlAndroidView>(this, 0, &QQmlAndroidView::children_append, &QQmlAndroidView::children_count,
                                                   &QQmlAndroidView::children_at, &QQmlAndroidView::children_clear);
}

QQmlAndroidLayoutParams *QQmlAndroidView::layoutParams() const
{
    return m_layoutParams;
}

void QQmlAndroidView::setLayoutParams(QQmlAndroidLayoutParams *params)
{
    if (m_layoutParams != params) {
        if (m_layoutParams) {
            disconnect(m_layoutParams, &QQmlAndroidObject::instanceChanged, this, &QQmlAndroidView::updateLayoutParams);
            m_layoutParams->destruct();
        }
        m_layoutParams = params;
        if (m_layoutParams) {
            connect(m_layoutParams, &QQmlAndroidObject::instanceChanged, this, &QQmlAndroidView::updateLayoutParams);
            if (isValid())
                m_layoutParams->construct();
        }
    }
}

QQmlAndroidDrawable *QQmlAndroidView::background() const
{
    return m_background;
}

void QQmlAndroidView::setBackground(QQmlAndroidDrawable *background, int resource)
{
    if (m_background != background) {
        if (m_background) {
            disconnect(m_background, &QQmlAndroidObject::instanceChanged, this, &QQmlAndroidView::updateBackground);
            m_background->destruct();
        }
        m_background = background;
        m_backgroundResource = resource;
        if (m_background) {
            connect(m_background, &QQmlAndroidObject::instanceChanged, this, &QQmlAndroidView::updateBackground);
            if (!resource)
                m_background->construct();
        }
        emit backgroundChanged();
    }
}

QQmlAndroidAnimation *QQmlAndroidView::animation() const
{
    return m_animation;
}

void QQmlAndroidView::setAnimation(QQmlAndroidAnimation *animation)
{
    if (m_animation != animation) {
        if (m_animation) {
            disconnect(m_animation, &QQmlAndroidObject::instanceChanged, this, &QQmlAndroidView::updateAnimation);
            m_animation->destruct();
        }
        m_animation = animation;
        if (m_animation) {
            connect(m_animation, &QQmlAndroidObject::instanceChanged, this, &QQmlAndroidView::updateAnimation);
            if (isValid())
                m_animation->construct();
        }
        emit animationChanged();
    }
}

int QQmlAndroidView::backgroundColor() const
{
    QQmlAndroidColorDrawable *drawable = qobject_cast<QQmlAndroidColorDrawable *>(m_background);
    if (drawable)
        return drawable->color();
    return 0; // TODO
}

void QQmlAndroidView::setBackgroundColor(int color)
{
    setBackground(new QQmlAndroidColorDrawable(color, this));
}

int QQmlAndroidView::backgroundResource() const
{
    return m_backgroundResource;
}

void QQmlAndroidView::setBackgroundResource(int resource)
{
    if (m_backgroundResource != resource) {
        setBackground(new QQmlAndroidDrawable(this), resource);
        emit backgroundResourceChanged();
    }
}

bool QQmlAndroidView::isVisible() const
{
    return m_visible;
}

void QQmlAndroidView::setVisible(bool visible)
{
    if (m_visible != visible) {
        m_visible = visible;
        // TODO: VISIBLE(0), INVISIBLE(4), GONE(8)
        QtQmlAndroid::callIntMethod(instance(), "setVisibility", visible ? 0 : 4);
        emit visibleChanged();
    }
}

bool QQmlAndroidView::hasFocus() const
{
    if (m_focus.isNull())
        return false;
    return m_focus;
}

bool QQmlAndroidView::updateFocus(bool arg)
{
    if (arg != hasFocus()) {
        m_focus = arg;
        emit focusChanged();
        return true;
    }
    return false;
}

qreal QQmlAndroidView::x() const
{
    return left(); // TODO: + translationX
}

qreal QQmlAndroidView::y() const
{
    return top(); // TODO: + translationY
}

int QQmlAndroidView::top() const
{
    if (m_top.isNull())
        return 0;
    return m_top;
}

void QQmlAndroidView::setTop(int top)
{
    if (m_top.isNull() || m_top != top) {
        m_top = top;
        QtQmlAndroid::callIntMethod(instance(), "setTop", top);
        emit topChanged();
    }
}

int QQmlAndroidView::left() const
{
    if (m_left.isNull())
        return 0;
    return m_left;
}

void QQmlAndroidView::setLeft(int left)
{
    if (m_left.isNull() || m_left != left) {
        m_left = left;
        QtQmlAndroid::callIntMethod(instance(), "setLeft", left);
        emit leftChanged();
    }
}

int QQmlAndroidView::right() const
{
    if (m_right.isNull())
        return 0;
    return m_right;
}

void QQmlAndroidView::setRight(int right)
{
    if (m_right.isNull() || m_right != right) {
        m_right = right;
        QtQmlAndroid::callIntMethod(instance(), "setRight", right);
        emit rightChanged();
    }
}

int QQmlAndroidView::bottom() const
{
    if (m_bottom.isNull())
        return 0;
    return m_bottom;
}

void QQmlAndroidView::setBottom(int bottom)
{
    if (m_bottom.isNull() || m_bottom != bottom) {
        m_bottom = bottom;
        QtQmlAndroid::callIntMethod(instance(), "setBottom", bottom);
        emit bottomChanged();
    }
}

int QQmlAndroidView::width() const
{
    return right() - left();
}

void QQmlAndroidView::setWidth(int width)
{
    setRight(left() + width);
}

int QQmlAndroidView::height() const
{
    return bottom() - top();
}

void QQmlAndroidView::setHeight(int height)
{
    setBottom(top() + height);
}

void QQmlAndroidView::updateGeometry(int t, int l, int r, int b)
{
    if (t != top()) {
        m_top = t;
        emit topChanged();
        emit yChanged();
    }
    if (l != left()) {
        m_left = l;
        emit leftChanged();
        emit xChanged();
    }
    if (r != right()) {
        m_right = r;
        emit rightChanged();
        emit widthChanged();
    }
    if (b != bottom()) {
        m_bottom = b;
        emit bottomChanged();
        emit heightChanged();
    }
}

int QQmlAndroidView::padding() const
{
    if (!m_padding.isNull())
        return m_padding;
    return 0;
}

void QQmlAndroidView::setPadding(int padding)
{
    if (m_padding.isNull() || m_padding != padding) {
        m_padding = padding;
        emit paddingChanged();
    }
}

int QQmlAndroidView::paddingTop() const
{
    if (m_paddingTop.isNull())
        return padding();
    return m_paddingTop;
}

void QQmlAndroidView::setPaddingTop(int padding)
{
    if (m_paddingTop.isNull() || m_paddingTop != padding) {
        m_paddingTop = padding;
        emit paddingTopChanged();
    }
}

int QQmlAndroidView::paddingLeft() const
{
    if (m_paddingLeft.isNull())
        return padding();
    return m_paddingLeft;
}

void QQmlAndroidView::setPaddingLeft(int padding)
{
    if (m_paddingLeft.isNull() || m_paddingLeft != padding) {
        m_paddingLeft = padding;
        emit paddingLeftChanged();
    }
}

int QQmlAndroidView::paddingRight() const
{
    if (m_paddingRight.isNull())
        return padding();
    return m_paddingRight;
}

void QQmlAndroidView::setPaddingRight(int padding)
{
    if (m_paddingRight.isNull() || m_paddingRight != padding) {
        m_paddingRight = padding;
        emit paddingRightChanged();
    }
}

int QQmlAndroidView::paddingBottom() const
{
    if (m_paddingBottom.isNull())
        return padding();
    return m_paddingBottom;
}

void QQmlAndroidView::setPaddingBottom(int padding)
{
    if (m_paddingBottom.isNull() || m_paddingBottom != padding) {
        m_paddingBottom = padding;
        emit paddingBottomChanged();
    }
}

void QQmlAndroidView::viewChange(ViewChange change, const ViewChangeData &data)
{
    switch (change) {
    case ViewParentChange:       // data.view
    case ViewChildAddedChange:   // data.view
    case ViewChildRemovedChange: // data.view
    case ViewVisibilityChange:   // data.boolean
    default:
        break;
    }
}

void QQmlAndroidView::addChild(QQmlAndroidView *child)
{
    if (!m_children.contains(child)) {
        m_children.append(child);
        viewChange(ViewChildAddedChange, child);
        emit childrenChanged();
    }
}

void QQmlAndroidView::removeChild(QQmlAndroidView *child)
{
    if (m_children.removeOne(child)) {
        viewChange(ViewChildRemovedChange, child);
        emit childrenChanged();
    }
}

void QQmlAndroidView::children_append(QQmlListProperty<QQmlAndroidView> *list, QQmlAndroidView *child)
{
    if (QQmlAndroidView *that = qobject_cast<QQmlAndroidView *>(list->object))
        that->addChild(child);
}

int QQmlAndroidView::children_count(QQmlListProperty<QQmlAndroidView> *list)
{
    if (QQmlAndroidView *that = qobject_cast<QQmlAndroidView *>(list->object))
        return that->m_children.count();
    return 0;
}

QQmlAndroidView *QQmlAndroidView::children_at(QQmlListProperty<QQmlAndroidView> *list, int index)
{
    if (QQmlAndroidView *that = qobject_cast<QQmlAndroidView *>(list->object))
        return that->m_children.at(index);
    return 0;
}

void QQmlAndroidView::children_clear(QQmlListProperty<QQmlAndroidView> *list)
{
    if (QQmlAndroidView *that = qobject_cast<QQmlAndroidView *>(list->object)) {
        while (!that->m_children.isEmpty())
            that->m_children.first()->setParentView(0);
    }
}

QAndroidJniObject QQmlAndroidView::onCreate()
{
    Q_ASSERT(!QtQmlAndroid::isMainQtThread());

    return QAndroidJniObject("android/view/View",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QQmlAndroidView::onInflate(QAndroidJniObject &instance)
{
    Q_ASSERT(!QtQmlAndroid::isMainQtThread());

    QQmlAndroidContextual::onInflate(instance);

    m_listener = QAndroidJniObject("qt/android/view/QmlViewListener",
                                   "(Landroid/view/View;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    instance.callMethod<void>("setId", "(I)V", m_id);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        onRegisterNativeMethods(m_listener.object());
        nativeMethodsRegistered = true;
    }

    // TODO: VISIBLE(0), INVISIBLE(4), GONE(8)
    instance.callMethod<void>("setVisibility", "(I)V", m_visible ? 0 : 4);
    if (!m_padding.isNull() || !m_paddingTop.isNull() || !m_paddingLeft.isNull() || !m_paddingRight.isNull() || !m_paddingBottom.isNull())
        instance.callMethod<void>("setPadding", "(IIII)V", paddingLeft(), paddingTop(), paddingRight(), paddingBottom());
    if (!m_top.isNull())
        instance.callMethod<void>("setTop", "(I)V", m_top);
    if (!m_left.isNull())
        instance.callMethod<void>("setLeft", "(I)V", m_left);
    if (!m_right.isNull())
        instance.callMethod<void>("setRight", "(I)V", m_right);
    if (!m_bottom.isNull())
        instance.callMethod<void>("setBottom", "(I)V", m_bottom);

    if (m_backgroundResource != 0) {
        QAndroidJniObject background = ctx().callObjectMethod("getDrawable", "(I)Landroid/graphics/drawable/Drawable;", m_backgroundResource);
        m_background->inflate(background);
    }
}

void QQmlAndroidView::onRegisterNativeMethods(jobject listener)
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

void QQmlAndroidView::onClick(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QQmlAndroidView *view = reinterpret_cast<QQmlAndroidView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "click", Qt::QueuedConnection);
}

void QQmlAndroidView::onFocusChange(JNIEnv *env, jobject object, jlong instance, jboolean hasFocus)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QQmlAndroidView *view = reinterpret_cast<QQmlAndroidView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "updateFocus", Qt::QueuedConnection, Q_ARG(bool, hasFocus));
}

void QQmlAndroidView::onLayoutChange(JNIEnv *env, jobject object, jlong instance, jint left, jint top, jint right, jint bottom)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QQmlAndroidView *view = reinterpret_cast<QQmlAndroidView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "updateGeometry", Qt::QueuedConnection, Q_ARG(int, top), Q_ARG(int, left), Q_ARG(int, right), Q_ARG(int, bottom));
}

bool QQmlAndroidView::onLongClick(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QQmlAndroidView *view = reinterpret_cast<QQmlAndroidView *>(instance);
    if (view) {
        //qDebug() << "onLongClick:" << view;
        QMetaObject::invokeMethod(view, "longClick", Qt::QueuedConnection);
    }
    return true; // TODO: accept
}

void QQmlAndroidView::requestPolish()
{
    if (!m_polishing) {
        m_polishing = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::PolishRequest));
    }
}

void QQmlAndroidView::polish()
{
}

bool QQmlAndroidView::event(QEvent *event)
{
    if (event->type() == QEvent::PolishRequest) {
        QQmlAndroidView *view = qobject_cast<QQmlAndroidView *>(parent());
        if (view)
            setParentView(view);
        polish();
        m_polishing = false;
    }
    return QQmlAndroidContextual::event(event);
}

void QQmlAndroidView::objectChange(ObjectChange change)
{
    QQmlAndroidContextual::objectChange(change);
    if (change == InstanceChange) {
        updateLayoutParams();
        updateBackground();
        updateAnimation();
    }
}

void QQmlAndroidView::updateBackground()
{
    if (!isValid() || !m_background)
        return;

    QAndroidJniObject view = instance();
    QAndroidJniObject background = m_background->instance();
    QtQmlAndroid::callFunction([=]() {
        view.callMethod<void>("setBackground", "(Landroid/graphics/drawable/Drawable;)V", background.object());
    });
}

void QQmlAndroidView::updateAnimation()
{
    if (!isValid() || !m_animation || !m_animation->isValid())
        return;

    QAndroidJniObject view = instance();
    QAndroidJniObject animation = m_animation->instance();
    QtQmlAndroid::callFunction([=]() {
        view.callMethod<void>("startAnimation", "(Landroid/view/animation/Animation;)V", animation.object());
    });
}

void QQmlAndroidView::updateLayoutParams()
{
    if (!isValid() || !m_layoutParams)
        return;

    QAndroidJniObject view = instance();
    QAndroidJniObject params = m_layoutParams->instance();
    QtQmlAndroid::callFunction([=]() {
        view.callMethod<void>("setLayoutParams",
                              "(Landroid/view/ViewGroup$LayoutParams;)V",
                              params.object());
    });
}

QT_END_NAMESPACE
