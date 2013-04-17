#include "enumwappers.h"
#include <QScriptEngine>
#include "objects/enums.h"

namespace Scripting {
namespace Internal {

#define createEnumStatics(CLASS,ENUM) \
static QScriptValue toScriptValue##ENUM(QScriptEngine *engine, const CLASS::ENUM &p)\
 {\
     return engine->newVariant((int)p);\
 }\
\
 static void fromScriptValue##ENUM(const QScriptValue &obj,CLASS::ENUM  &s)\
 {\
     s = (CLASS::ENUM)obj.toInt32();\
 }\

#define registerEnum(ENGINE,CLASS,ENUM) \
{\
    qScriptRegisterMetaType(ENGINE, toScriptValue##ENUM, fromScriptValue##ENUM);\
    QScriptValue metaObject = ENGINE->newQMetaObject( &CLASS::staticMetaObject );\
    ENGINE->globalObject().setProperty( QLatin1String(#ENUM), metaObject );\
}

createEnumStatics(Enums,PositionOperation)

void registerEnums(QScriptEngine* engine )
{
    registerEnum(engine, Enums, PositionOperation);
}

} // namespace Internal
} // namespace Scripting
