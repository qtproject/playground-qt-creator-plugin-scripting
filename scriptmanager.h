/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (C) 2011 Kläralvdalens Datakonsult AB, a KDAB Group company.
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

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>

QT_BEGIN_NAMESPACE
class QFileSystemWatcher;
class QSignalMapper;
QT_END_NAMESPACE

namespace ProjectExplorer {
class Project;
}

namespace Scripting {
namespace Internal {

class ScriptRunner;

/* Manager for scripts.
 * Manage all scripts available to the user, and run them.
 * The scripts are could be:
 *  - in the default script directory: userRessource/scripts
 *  - in a qtc-scripts directory of a project
 *
 * Scripts directory are watched using a QFileSystemWatcher, to update
 * the list of script in case one is added or deleted.
 */
class ScriptManager : public QObject
{
    Q_OBJECT

public:
    struct Script {
        QString name;
        QString fileName;
        QString projectName;
    };

    typedef QList<Script> ScriptList;

    explicit ScriptManager(QObject *parent = 0);
    ~ScriptManager();

    static ScriptManager *instance();

    QString defaultDirectory() const;
    QString scriptDirectory(ProjectExplorer::Project *project) const;
    ScriptList scriptList() const;

public slots:
    void runFile(const QString &scriptName);

private:
    void addScriptShortcut(const Script &script);
    void removeScriptShortcut(const Script &script);

private slots:
    void directoryChanged(const QString &path, bool initialize=false);
    void slotProjectAdded(ProjectExplorer::Project *project);
    void slotProjectRemoved(ProjectExplorer::Project *project);

private:
    static ScriptManager *m_instance;

    QString m_defaultDirectory;
    QFileSystemWatcher * m_watcher;
    ScriptList m_scriptList;
    QMap<QString,QString> m_projectMap; // name, directory
    QSignalMapper *m_mapper;

    ScriptRunner *m_runner;
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTMANAGER_H
