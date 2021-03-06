/****************************************************************************
**
** Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Marc Mutz <marc.mutz@kdab.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQMLANDROIDOPTIONAL_P_H
#define QQMLANDROIDOPTIONAL_P_H

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE

template <typename T>
class QQmlAndroidOptional
{
public:
    QQmlAndroidOptional() : t(), exists(false) {}
    explicit QQmlAndroidOptional(const T &t) : t(t), exists(true) {}
    explicit QQmlAndroidOptional(T &&t) : t(std::move(t)), exists(true) {}
    QQmlAndroidOptional &operator=(const T &o) { t = o; exists = true; return *this; }

    operator T&() Q_DECL_NOTHROW { return t; }
    operator const T&() const Q_DECL_NOTHROW { return t; }

    bool isNull() const Q_DECL_NOTHROW { return !exists; }

private:
    T t;
    bool exists;
};

template <typename T>
inline bool operator==(const QQmlAndroidOptional<T> &lhs, const QQmlAndroidOptional<T> &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(static_cast<const T&>(lhs) == static_cast<const T&>(rhs)))
{ return lhs.isNull() == rhs.isNull() && !lhs.isNull() && static_cast<const T&>(lhs) == static_cast<const T&>(rhs); }

template <typename T>
inline bool operator==(const QQmlAndroidOptional<T> &lhs, const T &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(static_cast<const T&>(lhs) == rhs))
{ return !lhs.isNull() && static_cast<const T&>(lhs) == rhs; }

template <typename T>
inline bool operator==(const T &lhs, const QQmlAndroidOptional<T> &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(lhs == static_cast<const T&>(rhs)))
{ return !rhs.isNull() && lhs == static_cast<const T&>(rhs); }

template <typename T>
inline bool operator!=(const QQmlAndroidOptional<T> &lhs, const QQmlAndroidOptional<T> &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(lhs == rhs))
{ return !operator==(lhs, rhs); }

template <typename T>
inline bool operator!=(const QQmlAndroidOptional<T> &lhs, const T &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(lhs == rhs))
{ return !operator==(lhs, rhs); }

template <typename T>
inline bool operator!=(const T &lhs, const QQmlAndroidOptional<T> &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(lhs == rhs))
{ return !operator==(lhs, rhs); }

QT_END_NAMESPACE

#endif // QQMLANDROIDOPTIONAL_P_H
