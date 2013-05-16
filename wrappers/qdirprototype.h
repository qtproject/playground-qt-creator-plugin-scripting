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

#ifndef SCRIPTING_INTERNAL_QDIRPROTOTYPE_H
#define SCRIPTING_INTERNAL_QDIRPROTOTYPE_H

#include <QObject>
#include <QDir>
#include <QMetaType>
#include <QScriptable>
#include "objects/enums.h"

namespace Scripting {
namespace Internal {

/**
 * @brief Wrapper for QDir, which makes it available in scripts
 */
class QDirPrototype : public QObject, public QScriptable
{
    // Methods comments out using //XXX are methods from QDir, which are not wrapped
    // The reason is that they make no sense, as this wrapper wraps a QDir, not a QDir*,
    // so the QDir is copied, and therefore read only.

    Q_OBJECT
    Q_PROPERTY(QString path READ path)
    Q_PROPERTY(QString absolutePath READ absolutePath)
    Q_PROPERTY(QString canonicalPath READ canonicalPath)
    Q_PROPERTY(QString dirName READ dirName)
    Q_PROPERTY(uint count READ count)
    Q_PROPERTY(bool isReadable READ isReadable)
    // Q_PROPERTY(bool exists READ exists) - not wrapped as that would shadow exists(fileName)
    Q_PROPERTY(bool isRoot READ isRoot)
    Q_PROPERTY(bool isRelative READ isRelative)
    Q_PROPERTY(bool isAbsolute READ isAbsolute)

public:
    static QScriptValue construct(QScriptContext* context, QScriptEngine* engine);

public slots:
    //XXX void setPath(const QString &path);
    QString path() const;
    QString absolutePath() const;
    QString canonicalPath() const;

    void addResourceSearchPath(const QString &path);

    void setSearchPaths(const QString &prefix, const QStringList &searchPaths);
    void addSearchPath(const QString &prefix, const QString &path);
    QStringList searchPaths(const QString &prefix);

    QString dirName() const;
    QString filePath(const QString &fileName) const;
    QString absoluteFilePath(const QString &fileName) const;
    QString relativeFilePath(const QString &fileName) const;

    QString toNativeSeparators(const QString &pathName);
    QString fromNativeSeparators(const QString &pathName);

    // The signature of these are changed to return a QDir
    QDir cd(const QString &dirName);
    QDir cdUp();

    //XXX QStringList nameFilters() const;
    //XXX void setNameFilters(const QStringList &nameFilters);
    //XXX Filters filter() const;
    //XXX void setFilter(Filters filter);
    //XXX SortFlags sorting() const;
    //XXX void setSorting(SortFlags sort);

    uint count() const;
    QString at(int i) const; // Was operator[]


    QStringList entryList(const QStringList &nameFilters = QStringList(), int filters = Enums::NoFilter,
                          int sort = QDir::NoSort) const;

    //XXX QFileInfoList entryInfoList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
    //XXX QFileInfoList entryInfoList(const QStringList &nameFilters, Filters filters = NoFilter,
    //XXX                             SortFlags sort = NoSort) const;

    bool mkdir(const QString &dirName) const;
    bool rmdir(const QString &dirName) const;
    bool mkpath(const QString &dirPath) const;
    bool rmpath(const QString &dirPath) const;

    bool isReadable() const;
    bool exists() const;
    bool isRoot() const;

    bool isRelativePath(const QString &path);
    bool isAbsolutePath(const QString &path) { return !isRelativePath(path); }
    bool isRelative() const;
    bool isAbsolute() const;
    //XXX bool makeAbsolute();

    bool remove(const QString &fileName);
    bool rename(const QString &oldName, const QString &newName);
    bool exists(const QString &name) const;

    QFileInfoList drives();

    QChar separator();

    bool setCurrent(const QString &path);
    inline QDir current() { return QDir(currentPath()); }
    QString currentPath();

    QDir home() { return QDir(homePath()); }
    QString homePath();
    QDir root() { return QDir(rootPath()); }
    QString rootPath();
    QDir temp() { return QDir(tempPath()); }
    QString tempPath();

#ifndef QT_NO_REGEXP
    bool match(const QStringList &filters, const QString &fileName);
    bool match(const QString &filter, const QString &fileName);
#endif

    QString cleanPath(const QString &path);
    //XXX void refresh() const;
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTING_INTERNAL_QDIRPROTOTYPE_H

Q_DECLARE_METATYPE(QDir)
