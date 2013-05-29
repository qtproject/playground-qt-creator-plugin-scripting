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

#include "scriptmanager.h"
#include "scriptingconstants.h"
#include "scriptrunner.h"

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/session.h>
#include <projectexplorer/project.h>

#include <coreplugin/icore.h>
#include <coreplugin/messagemanager.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/id.h>
#include <coreplugin/icontext.h>

#include <utils/outputformat.h>

#include <QShortcut>
#include <QMainWindow>
#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QSignalMapper>


using namespace Scripting;
using namespace Scripting::Internal;

ScriptManager *ScriptManager::m_instance = 0;

ScriptManager::ScriptManager(QObject *parent) :
    QObject(parent)
{
    m_watcher = new QFileSystemWatcher(this);
    connect(m_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(directoryChanged(QString)));

    m_mapper = new QSignalMapper(this);
    connect(m_mapper, SIGNAL(mapped(QString)), this, SLOT(runFile(QString)));

    m_defaultDirectory = defaultDirectory();
    if (!m_defaultDirectory.isEmpty()) {
        m_watcher->addPath(m_defaultDirectory);
        directoryChanged(m_defaultDirectory, true);
    }

    ProjectExplorer::SessionManager *sm = ProjectExplorer::ProjectExplorerPlugin::instance()->session();
    connect(sm, SIGNAL(projectAdded(ProjectExplorer::Project*)),
            this, SLOT(slotProjectAdded(ProjectExplorer::Project*)));
    connect(sm, SIGNAL(projectRemoved(ProjectExplorer::Project*)),
            this, SLOT(slotProjectRemoved(ProjectExplorer::Project*)));

    m_runner = new ScriptRunner(this);

    m_instance = this;
}

ScriptManager::~ScriptManager()
{
}

ScriptManager * ScriptManager::instance()
{
    return m_instance;
}

QString ScriptManager::defaultDirectory() const
{
    const QString &path =
            Core::ICore::userResourcePath() + QLatin1String("/scripts");
    if (QFile::exists(path) || QDir().mkpath(path))
        return path;
    qWarning() << "could not create " << path;
    return QString();
}

QString ScriptManager::scriptDirectory(ProjectExplorer::Project *project) const
{
    const QString &path = project->projectDirectory() + QLatin1Char('/') + Constants::S_SCRIPTDIRECTORY;

    if (QFile::exists(path))
        return path;
    return QString();
}

ScriptManager::ScriptList ScriptManager::scriptList() const
{
    return m_scriptList;
}

void ScriptManager::addScriptPath(const QString &path)
{
    m_watcher->addPath(path);
    directoryChanged(path, true);
}

QStringList scriptListFromDir(const QString &path)
{
    QDir dir(path);
    QStringList filter;
    filter << QLatin1String("*.") + Constants::S_EXTENSION;
    QStringList files = dir.entryList(filter, QDir::Files);

    for (int i=0; i<files.count(); ++i) {
        QString fileName = dir.absolutePath() + QLatin1Char('/') + files.at(i);
        files[i] = fileName;
    }

    return files;
}

void ScriptManager::runFile(const QString &fileName)
{
    ErrorMessage message = m_runner->runScript(fileName);
    if (message.hasError)
        Core::MessageManager::instance()->printToOutputPane(tr("Error in %1 at line %3: %4\n").arg(message.fileName).arg(message.line).arg(message.message),
                                                            Core::MessageManager::NoModeSwitch);
}

void ScriptManager::directoryChanged(const QString &path, bool initialize)
{
    QString projectName = m_projectMap.key(path);
    QStringList files = scriptListFromDir(path);

    if (!initialize) {
        // Remove deleted scripts
        QMutableListIterator<Script> i(m_scriptList);
        while (i.hasNext()) {
            Script script = i.next();
            if (files.contains(script.fileName)) {
                files.removeAll(script.fileName);
            } else {
                removeScriptShortcut(script);
                i.remove();
            }
        }
    }

    // Add new scripts
    foreach (const QString &fileName, files) {
        QFileInfo fi(fileName);

        if (fi.isReadable() && fi.fileName() != QLatin1String("init.qs")) {
            Script script;
            script.fileName = fileName;
            script.name = fi.baseName();
            script.projectName = projectName;
            addScriptShortcut(script);
            m_scriptList.append(script);
        }
    }
}

void ScriptManager::slotProjectAdded(ProjectExplorer::Project *project)
{
    QString scriptPath = scriptDirectory(project);
    if (!scriptPath.isEmpty()) {
        m_watcher->addPath(scriptPath);
        m_projectMap[project->displayName()] = scriptPath;
        directoryChanged(scriptPath, true);
    }
}

void ScriptManager::slotProjectRemoved(ProjectExplorer::Project *project)
{
    QString projectName = project->displayName();
    if (m_projectMap.contains(projectName)) {
        m_watcher->removePath(m_projectMap.value(projectName));
        m_projectMap.remove(projectName);

        QMutableListIterator<Script> i(m_scriptList);
        while (i.hasNext()) {
            Script script = i.next();
            if (script.projectName == projectName) {
                removeScriptShortcut(script);
                i.remove();
            }
        }
    }
}

QString makeScriptId(const ScriptManager::Script &script)
{
    QString scriptId;
    if (script.projectName.isEmpty())
        scriptId = Constants::S_GLOBAL_NAME;
    else
        scriptId = script.projectName;
    return scriptId + QLatin1String(Constants::S_SHORTCUT_SUFFIX) + script.name;
}

void ScriptManager::addScriptShortcut(const ScriptManager::Script &script)
{
    // Add shortcut for this script
    Core::Context globalContext(Core::Constants::C_GLOBAL);
    QShortcut *shortcut = new QShortcut(Core::ICore::mainWindow());

    // FIXME: fromString should not be used.
    const Core::Id scriptId = Core::Id::fromString(makeScriptId(script));

    Core::ICore::actionManager()->registerShortcut(shortcut, scriptId, globalContext);
    connect(shortcut, SIGNAL(activated()), m_mapper, SLOT(map()));
    m_mapper->setMapping(shortcut, script.fileName);
}

void ScriptManager::removeScriptShortcut(const ScriptManager::Script &script)
{
    // Remove shortcut
    // FIXME: fromString should not be used.
    const Core::Id scriptId = Core::Id::fromString(makeScriptId(script));
    Core::ICore::actionManager()->unregisterShortcut(scriptId);
}
