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

#include "qfileinfoprototype.h"
#include <QFileInfo>
#include <QScriptEngine>
#include "scriptrunner.h"

namespace Scripting {
namespace Internal {

QScriptValue QFileInfoPrototype::construct(QScriptContext *context, QScriptEngine *engine)
{
    if ( context->isCalledAsConstructor() ) {
        if ( context->argumentCount() != 1 ) {
            context->throwError(tr("QFileInfo object must be constructed with a filename as parameter"));
            return engine->undefinedValue();
        }
        return engine->toScriptValue( QFileInfo(context->argument(0).toString()));
    }
    else {
        return engine->undefinedValue();
    }
}

#define FILE qscriptvalue_cast<QFileInfo>(thisObject())

bool QFileInfoPrototype::exists() const
{
    return FILE.exists();
}

QString QFileInfoPrototype::filePath() const
{
    return FILE.filePath();
}

QString QFileInfoPrototype::absoluteFilePath() const
{
    return FILE.absoluteFilePath();
}

QString QFileInfoPrototype::canonicalFilePath() const
{
    return FILE.canonicalFilePath();
}

QString QFileInfoPrototype::fileName() const
{
    return FILE.fileName();
}

QString QFileInfoPrototype::baseName() const
{
    return FILE.baseName();
}

QString QFileInfoPrototype::completeBaseName() const
{
    return FILE.completeBaseName();
}

QString QFileInfoPrototype::suffix() const
{
    return FILE.suffix();
}

QString QFileInfoPrototype::bundleName() const
{
    return FILE.bundleName();
}

QString QFileInfoPrototype::completeSuffix() const
{
    return FILE.completeSuffix();
}

QString QFileInfoPrototype::path() const
{
    return FILE.path();
}

QString QFileInfoPrototype::absolutePath() const
{
    return FILE.absolutePath();
}

QString QFileInfoPrototype::canonicalPath() const
{
    return FILE.canonicalPath();
}

QDir QFileInfoPrototype::dir() const
{
    return FILE.dir();
}

QDir QFileInfoPrototype::absoluteDir() const
{
    return FILE.absoluteDir();
}

bool QFileInfoPrototype::isReadable() const
{
    return FILE.isReadable();
}

bool QFileInfoPrototype::isWritable() const
{
    return FILE.isWritable();
}

bool QFileInfoPrototype::isExecutable() const
{
    return FILE.isExecutable();
}

bool QFileInfoPrototype::isHidden() const
{
    return FILE.isHidden();
}

bool QFileInfoPrototype::isRelative() const
{
    return FILE.isRelative();
}

bool QFileInfoPrototype::isAbsolute() const
{
    return FILE.isAbsolute();
}

bool QFileInfoPrototype::isFile() const
{
    return FILE.isFile();
}

bool QFileInfoPrototype::isDir() const
{
    return FILE.isDir();
}

bool QFileInfoPrototype::isSymLink() const
{
    return FILE.isSymLink();
}

bool QFileInfoPrototype::isRoot() const
{
    return FILE.isRoot();
}

bool QFileInfoPrototype::isBundle() const
{
    return FILE.isBundle();
}

QString QFileInfoPrototype::readLink() const
{
    return FILE.readLink();
}

QString QFileInfoPrototype::symLinkTarget() const
{
    return FILE.symLinkTarget();
}

QString QFileInfoPrototype::owner() const
{
    return FILE.owner();
}

uint QFileInfoPrototype::ownerId() const
{
    return FILE.ownerId();
}

QString QFileInfoPrototype::group() const
{
    return FILE.group();
}

uint QFileInfoPrototype::groupId() const
{
    return FILE.groupId();
}

qint64 QFileInfoPrototype::size() const
{
    return FILE.size();
}

QDateTime QFileInfoPrototype::created() const
{
    return FILE.created();
}

QDateTime QFileInfoPrototype::lastModified() const
{
    return FILE.lastModified();
}

QDateTime QFileInfoPrototype::lastRead() const
{
    return FILE.lastRead();
}

} // namespace Internal
} // namespace Scripting
