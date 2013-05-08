#include "scriptwrappers.h"
#include <QPoint>
#include <QRect>
#include "utils/position.h"

namespace Scripting {
namespace Internal {

QScriptValue scriptValueFromQPoint(QScriptEngine *engine, const QPoint &point)
{
  QScriptValue obj = engine->newObject();
  obj.setProperty(QLatin1String("x"), point.x());
  obj.setProperty(QLatin1String("y"), point.y());
  return obj;
}

void QPointFromScriptValue(const QScriptValue &obj, QPoint& point)
{
    point.setX( obj.property(QLatin1String("x")).toInt32() );
    point.setY( obj.property(QLatin1String("y")).toInt32() );
}

QScriptValue scriptValueFromPosition(QScriptEngine *engine, const Position &pos)
{
  QScriptValue obj = engine->newObject();
  obj.setProperty(QLatin1String("line"), pos.line());
  obj.setProperty(QLatin1String("column"), pos.column());
  return obj;
}

void PositionFromScriptValue(const QScriptValue &obj, Position& pos)
{
    pos.setLine( obj.property(QLatin1String("line")).toInt32() );
    pos.setColumn( obj.property(QLatin1String("column")).toInt32() );
}

QScriptValue scriptValueFromQRect(QScriptEngine *engine, const QRect &rect)
{
  QScriptValue obj = engine->newObject();
  obj.setProperty(QLatin1String("x"), rect.x());
  obj.setProperty(QLatin1String("y"), rect.y());
  obj.setProperty(QLatin1String("width"), rect.width());
  obj.setProperty(QLatin1String("height"), rect.height());
  return obj;
}

void QRectFromScriptValue(const QScriptValue &obj, QRect& rect)
{
    rect.setX( obj.property(QLatin1String("x")).toInt32() );
    rect.setY( obj.property(QLatin1String("y")).toInt32() );
    rect.setWidth( obj.property(QLatin1String("width")).toInt32() );
    rect.setHeight( obj.property(QLatin1String("height")).toInt32() );
}


void registerWrappers(QScriptEngine* engine )
{
    qScriptRegisterMetaType(engine, scriptValueFromQPoint, QPointFromScriptValue );
    qScriptRegisterMetaType(engine, scriptValueFromPosition, PositionFromScriptValue );
    qScriptRegisterMetaType(engine, scriptValueFromQRect, QRectFromScriptValue );
}

} // namespace Internal
} // namespace Scripting
