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

#ifndef SCRIPTING_INTERNAL_CPPFUNCTION_H
#define SCRIPTING_INTERNAL_CPPFUNCTION_H

#include <QObject>
#include <QMetaType>
#include <QList>
#include "utils/position.h"

namespace CPlusPlus {
    class Function;
}

namespace Scripting {
namespace Internal {

class CppArgument;

class CppFunction : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString name READ name )
    Q_PROPERTY( QString returnType READ returnType )
    Q_PROPERTY( QList<CppArgument*> arguments READ arguments )
    Q_PROPERTY( bool isVirtual READ isVirtual )
    Q_PROPERTY( bool isOverride READ isOverride )
    Q_PROPERTY( bool isFinal READ isFinal )
    Q_PROPERTY( bool isVariadic READ isVariadic )
    Q_PROPERTY( bool isConst READ isConst )
    Q_PROPERTY( bool isVolatile READ isVolatile )
    Q_PROPERTY( bool isPureVirtual READ isPureVirtual )
    Q_PROPERTY( Position start READ start)

public:
    static CppFunction* create(int line, int column, const QString& fileName);
    QString name() const;
    QString returnType() const;
    QList<CppArgument*> arguments() const;
    bool isVirtual() const;
    bool isOverride() const;
    bool isFinal() const;
    bool isVariadic() const;
    bool isConst() const;
    bool isVolatile() const;
    bool isPureVirtual() const;
    Position start() const;

private:
    CppFunction();
    static CPlusPlus::Function* function(int line,int column, const QString& fileName);
    static QString extractName(const CPlusPlus::Function* function);
    static QString extractReturnType(const CPlusPlus::Function* function);
    static QList<CppArgument *> extractArguments(const CPlusPlus::Function* function);

    QString m_name;
    QString m_returnType;
    QList<CppArgument*> m_arguments;
    bool m_isVirtual;
    bool m_isOverride;
    bool m_isFinal;
    bool m_isVariadic;
    bool m_isConst;
    bool m_isVolatile;
    bool m_isPureVirtual;
    Position m_start;
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(Scripting::Internal::CppFunction*)

#endif // SCRIPTING_INTERNAL_CPPFUNCTION_H
