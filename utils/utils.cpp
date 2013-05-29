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

#include "utils.h"
#include <QDir>
#include "scriptrunner.h"
#include <QFile>
#include <scriptmanager.h>

namespace Scripting {
namespace Internal {

Utils::Utils(QObject *parent) :
    QObject(parent)
{
}

QStringList Utils::backtrace() const
{
    QStringList result;
    foreach ( const QString& str, ScriptRunner::instance()->scriptEngine()->currentContext()->backtrace() ) {
        // Remove internal calls that is of no use to the script side
        if ( !str.startsWith(QLatin1String("<")))
            result.append(QLatin1String("\t") + str);
    }
    return result;
}

QString Utils::currentScripRoot() const
{
    return ScriptRunner::currentScriptRoot();
}

bool Scripting::Internal::Utils::copyFile(const QString &from, const QString &to)
{
    QFile fromFile(from);
    if ( !fromFile.open(QFile::ReadOnly)) {
        return false;
    }

    QFile toFile(to);
    if (!toFile.open(QFile::WriteOnly)) {
        return false;
    }

    QByteArray content = fromFile.readAll();
    toFile.write(content);
    fromFile.close();
    toFile.close();
    return true;
}

void Utils::touchFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QFile::Append);
    file.close();
}

void Utils::addScriptPath(const QString &path)
{
    ScriptManager::instance()->addScriptPath(path);
}


} // namespace Internal
} // namespace Scripting
