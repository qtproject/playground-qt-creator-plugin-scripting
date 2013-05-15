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

#ifndef SCRIPTING_INTERNAL_CPPCLASS_H
#define SCRIPTING_INTERNAL_CPPCLASS_H

#include <QObject>
#include <QMetaType>
#include "utils/position.h"
#include <QStringList>

namespace CPlusPlus {
    class Class;
}
namespace Scripting {
namespace Internal {

class CppClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name);
    Q_PROPERTY(Position start READ start)
    Q_PROPERTY(bool isClass READ isClass)
    Q_PROPERTY(bool isStruct READ isStruct)
    Q_PROPERTY(bool isUnion READ isUnion)
    Q_PROPERTY(QStringList baseClasses READ baseClasses)

public:
    static CppClass* create(int line, int column, const QString& fileName);
    QString name() const;
    Position start() const;
    bool isClass() const;
    bool isStruct() const;
    bool isUnion() const;
    QStringList baseClasses() const;

private:
    explicit CppClass() {}
    static CPlusPlus::Class* fetchClass(int line, int column, const QString& fileName);

    QString m_name;
    Position m_start;
    bool m_isClass;
    bool m_isStruct;
    bool m_isUnion;
    QStringList m_baseClasses;
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(Scripting::Internal::CppClass*)

#endif // SCRIPTING_INTERNAL_CPPCLASS_H
