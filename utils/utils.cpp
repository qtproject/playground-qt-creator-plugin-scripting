/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (C) 2013 Kläralvdalens Datakonsult AB, a KDAB Group company.
**
** Contact: Kläralvdalens Datakonsult AB (info@kdab.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at info@qt.nokia.com.
**
**************************************************************************/

#include "utils.h"
#include <QDir>
#include "scriptrunner.h"

namespace Scripting {
namespace Internal {

Utils::Utils(QObject *parent) :
    QObject(parent)
{
}

QStringList Utils::subDirectories(const QString &directory) const
{
    QDir dir(ScriptRunner::absolutePath(directory));
    return dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
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


} // namespace Internal
} // namespace Scripting