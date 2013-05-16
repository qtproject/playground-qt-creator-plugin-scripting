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

#include "scriptwrappers.h"
#include <QRect>
#include "utils/position.h"

namespace Scripting {
namespace Internal {

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
    qScriptRegisterMetaType(engine, scriptValueFromPosition, PositionFromScriptValue );
    qScriptRegisterMetaType(engine, scriptValueFromQRect, QRectFromScriptValue );
}

} // namespace Internal
} // namespace Scripting
