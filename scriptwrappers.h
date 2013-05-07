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
