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

#ifndef SCRIPTING_INTERNAL_QFILEINFOPROTOTYPE_H
#define SCRIPTING_INTERNAL_QFILEINFOPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QMetaType>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>

namespace Scripting {
namespace Internal {

/**
 * @brief Wrapper for QFileInfo, which makes it available in scripts
 */
class QFileInfoPrototype : public QObject, public QScriptable
{
    // Methods comments out using //XXX are methods from QFileInfo, which are not wrapped
    // The reason is that they make no sense, as this wrapper wraps a QFileInfo, not a QFileInfo*,
    // so the QFileInfo is copied, and therefore read only.
    Q_OBJECT

    Q_PROPERTY( bool exists READ exists)
    Q_PROPERTY( QString filePath READ filePath)
    Q_PROPERTY( QString absoluteFilePath READ absoluteFilePath)
    Q_PROPERTY( QString canonicalFilePath READ canonicalFilePath)
    Q_PROPERTY( QString fileName READ fileName)
    Q_PROPERTY( QString baseName READ baseName)
    Q_PROPERTY( QString completeBaseName READ completeBaseName)
    Q_PROPERTY( QString suffix READ suffix)
    Q_PROPERTY( QString bundleName READ bundleName)
    Q_PROPERTY( QString completeSuffix READ completeSuffix)
    Q_PROPERTY( QString path READ path)
    Q_PROPERTY( QString absolutePath READ absolutePath)
    Q_PROPERTY( QString canonicalPath READ canonicalPath)
    Q_PROPERTY( QDir dir READ dir)
    Q_PROPERTY( QDir absoluteDir READ absoluteDir)
    Q_PROPERTY( bool isReadable READ isReadable)
    Q_PROPERTY( bool isWritable READ isWritable)
    Q_PROPERTY( bool isExecutable READ isExecutable)
    Q_PROPERTY( bool isHidden READ isHidden)
    Q_PROPERTY( bool isRelative READ isRelative)
    Q_PROPERTY( bool isAbsolute READ isAbsolute)
    Q_PROPERTY( bool isFile READ isFile)
    Q_PROPERTY( bool isDir READ isDir)
    Q_PROPERTY( bool isSymLink READ isSymLink)
    Q_PROPERTY( bool isRoot READ isRoot)
    Q_PROPERTY( bool isBundle READ isBundle)
    Q_PROPERTY( QString readLink READ readLink)
    Q_PROPERTY( QString symLinkTarget READ symLinkTarget)
    Q_PROPERTY( QString owner READ owner)
    Q_PROPERTY( uint ownerId READ ownerId)
    Q_PROPERTY( QString group READ group)
    Q_PROPERTY( uint groupId READ groupId)
    Q_PROPERTY( qint64 size READ size)
    Q_PROPERTY( QDateTime created READ created)
    Q_PROPERTY( QDateTime lastModified READ lastModified)
    Q_PROPERTY( QDateTime lastRead READ lastRead)

public:
    static QScriptValue construct(QScriptContext* context, QScriptEngine* engine);

    //XXX void setFile(const QString &file);
    //XXX void setFile(const QFile &file);
    //XXX void setFile(const QDir &dir, const QString &file);
    bool exists() const;
    //XXX void refresh();

    QString filePath() const;
    QString absoluteFilePath() const;
    QString canonicalFilePath() const;
    QString fileName() const;
    QString baseName() const;
    QString completeBaseName() const;
    QString suffix() const;
    QString bundleName() const;
    QString completeSuffix() const;

    QString path() const;
    QString absolutePath() const;
    QString canonicalPath() const;
    QDir dir() const;
    QDir absoluteDir() const;

    bool isReadable() const;
    bool isWritable() const;
    bool isExecutable() const;
    bool isHidden() const;

    bool isRelative() const;
    bool isAbsolute() const;
    // bool makeAbsolute();

    bool isFile() const;
    bool isDir() const;
    bool isSymLink() const;
    bool isRoot() const;
    bool isBundle() const;

    QString readLink() const;
    QString symLinkTarget() const;

    QString owner() const;
    uint ownerId() const;
    QString group() const;
    uint groupId() const;

    // Not yet implemented, but could be.
    // bool permission(QFile::Permissions permissions) const;
    // QFile::Permissions permissions() const;

    qint64 size() const;

    QDateTime created() const;
    QDateTime lastModified() const;
    QDateTime lastRead() const;

    //XXX void detach();
    //XXX bool caching() const;
    //XXX void setCaching(bool on);
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(QFileInfo)

#endif // SCRIPTING_INTERNAL_QFILEINFOPROTOTYPE_H
