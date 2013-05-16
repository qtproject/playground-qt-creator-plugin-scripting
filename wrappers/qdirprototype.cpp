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

#include "qdirprototype.h"
#include <QScriptValue>
#include <qscriptcontext.h>
#include <QScriptEngine>

namespace Scripting {
namespace Internal {

QScriptValue QDirPrototype::construct(QScriptContext *context, QScriptEngine *engine)
{
    if ( context->argumentCount() == 1 )
        return engine->toScriptValue( QDir(context->argument(0).toString()));
    else
        return engine->toScriptValue( QDir() );
}

#define DIR qscriptvalue_cast<QDir>(thisObject())

//XXX void setPath(const QString &path);

QString QDirPrototype::path() const
{
    return DIR.path();
}

QString QDirPrototype::absolutePath() const
{
    return DIR.absolutePath();
}

QString QDirPrototype::canonicalPath() const
{
    return DIR.canonicalPath();
}

void QDirPrototype::addResourceSearchPath(const QString &path)
{
    DIR.addResourceSearchPath(path);
}

void QDirPrototype::setSearchPaths(const QString &prefix, const QStringList &searchPaths)
{
    DIR.setSearchPaths(prefix,searchPaths);
}

void QDirPrototype::addSearchPath(const QString &prefix, const QString &path)
{
    DIR.addSearchPath(prefix,path);
}

QStringList QDirPrototype::searchPaths(const QString &prefix)
{
    return DIR.searchPaths(prefix);
}

QString QDirPrototype::dirName() const
{
    return DIR.dirName();
}

QString QDirPrototype::filePath(const QString &fileName) const
{
    return DIR.filePath(fileName);
}

QString QDirPrototype::absoluteFilePath(const QString &fileName) const
{
    return DIR.absoluteFilePath(fileName);
}

QString QDirPrototype::relativeFilePath(const QString &fileName) const
{
    return DIR.relativeFilePath(fileName);
}

QString QDirPrototype::toNativeSeparators(const QString &pathName)
{
    return DIR.toNativeSeparators(pathName);
}

QString QDirPrototype::fromNativeSeparators(const QString &pathName)
{
    return DIR.fromNativeSeparators(pathName);
}

QDir QDirPrototype::cd(const QString &dirName)
{
    QDir d = DIR;
    d.cd(dirName);
    return d;
}

QDir QDirPrototype::cdUp()
{
    QDir d = DIR;
    d.cdUp();
    return d;
}

//XXX QStringList nameFilters() const;
//XXX void setNameFilters(const QStringList &nameFilters);

//XXX Filters filter() const;
//XXX void setFilter(Filters filter);
//XXX SortFlags sorting() const;
//XXX void setSorting(SortFlags sort);

uint QDirPrototype::count() const
{
    return DIR.count();
}

QString QDirPrototype::at(int i) const
{
    return DIR[i];
}


QStringList QDirPrototype::entryList(const QStringList &nameFilters, int filters, int sort) const
{
    return DIR.entryList(nameFilters, Enums::convertFilters(filters), Enums::convertSortFlag(sort));
}

//XXX QFileInfoList entryInfoList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
//XXX QFileInfoList entryInfoList(const QStringList &nameFilters, Filters filters = NoFilter,
//XXX                             SortFlags sort = NoSort) const;

bool QDirPrototype::mkdir(const QString &dirName) const
{
    return DIR.mkdir(dirName);
}

bool QDirPrototype::rmdir(const QString &dirName) const
{
    return DIR.rmdir(dirName);
}

bool QDirPrototype::mkpath(const QString &dirPath) const
{
    return DIR.mkpath(dirPath);
}

bool QDirPrototype::rmpath(const QString &dirPath) const
{
    return DIR.rmpath(dirPath);
}


bool QDirPrototype::isReadable() const
{
    return DIR.isReadable();
}

bool QDirPrototype::exists() const
{
    return DIR.exists();
}

bool QDirPrototype::isRoot() const
{
    return DIR.isRoot();
}

bool QDirPrototype::isRelativePath(const QString &path)
{
    return DIR.isRelativePath(path);
}

bool QDirPrototype::isRelative() const
{
    return DIR.isRelative();
}

bool QDirPrototype::isAbsolute() const
{
    return DIR.isAbsolute();
}

//XXX bool makeAbsolute();

bool QDirPrototype::remove(const QString &fileName)
{
    return DIR.remove(fileName);
}

bool QDirPrototype::rename(const QString &oldName, const QString &newName)
{
    return DIR.rename(oldName, newName);
}

bool QDirPrototype::exists(const QString &name) const
{
    return DIR.exists(name);
}


QFileInfoList QDirPrototype::drives()
{
    return DIR.drives();
}

QChar QDirPrototype::separator()
{
    return DIR.separator();
}

bool QDirPrototype::setCurrent(const QString &path)
{
    return DIR.setCurrent(path);
}

QString QDirPrototype::currentPath()
{
    return DIR.currentPath();
}

QString QDirPrototype::homePath()
{
    return DIR.homePath();
}

QString QDirPrototype::rootPath()
{
    return DIR.rootPath();
}

QString QDirPrototype::tempPath()
{
    return DIR.tempPath();
}

#ifndef QT_NO_REGEXP
bool QDirPrototype::match(const QStringList &filters, const QString &fileName)
{
    return DIR.match(filters, fileName);
}

bool QDirPrototype::match(const QString &filter, const QString &fileName)
{
    return DIR.match(filter,fileName);
}
#endif

QString QDirPrototype::cleanPath(const QString &path)
{
    return DIR.cleanPath(path);
}

//XXX void refresh() const;
} // namespace Internal
} // namespace Scripting

