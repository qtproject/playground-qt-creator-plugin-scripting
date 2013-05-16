/**************************************************************************
**
** Copyright (C) 2013 Kläralvdalens Datakonsult AB, a KDAB Group company.
** Contact: Kläralvdalens Datakonsult AB (info@kdab.com)
**
** This file is part of Qt Creator.
**
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
****************************************************************************/

#ifndef SCRIPTING_INTERNAL_SCRIPTWRAPPERS_H
#define SCRIPTING_INTERNAL_SCRIPTWRAPPERS_H

#include <QScriptEngine>

namespace Scripting {
namespace Internal {

void registerWrappers(QScriptEngine* engine );


// Convert a class derived from QObject to Scriptvalue via engine->newQObject() to make
// the signals, slots and properties visible.
// To be registered as a magic creation function with qScriptRegisterMetaType().
// (see registerQObject()

template <class SomeQObject>
static QScriptValue qObjectToScriptValue(QScriptEngine *engine, SomeQObject * const &qo)
{
    return engine->newQObject(qo, QScriptEngine::AutoOwnership);
}

// Convert  Scriptvalue back to a class derived from  QObject via QScriptValue::toQObject()
// To be registered as a magic conversion function with  qScriptRegisterMetaType().
// (see registerQObject)

template <class SomeQObject>
static void scriptValueToQObject(const QScriptValue &sv, SomeQObject * &p)
{
    QObject *qObject =  sv.toQObject();
    p = qobject_cast<SomeQObject*>(qObject);
    Q_ASSERT(p);
}

// Register a QObject-derived class which has Q_DECLARE_METATYPE(Ptr*)
// with the engine using qObjectToScriptValue/scriptValueToQObject as
// conversion functions to make it possible to use for example
// Q_PROPERTY(QMainWindow*).

template <class SomeQObject>
static void registerQObject(QScriptEngine *engine)
{
    qScriptRegisterMetaType<SomeQObject*>(engine,
                                          qObjectToScriptValue<SomeQObject>,
                                          scriptValueToQObject<SomeQObject>);
}
} // namespace Internal
} // namespace Scripting

#endif // SCRIPTING_INTERNAL_SCRIPTWRAPPERS_H
