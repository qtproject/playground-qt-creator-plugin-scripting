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

#include <QtGui/QShortcut>
#include <QtGui/QMainWindow>

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QDebug>
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QSignalMapper>


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
    const QString &path = project->projectDirectory() + '/' + Constants::S_SCRIPTDIRECTORY;

    if (QFile::exists(path))
        return path;
    return QString();
}

ScriptManager::ScriptList ScriptManager::scriptList() const
{
    return m_scriptList;
}

QStringList scriptListFromDir(const QString &path)
{
    QDir dir(path);
    QStringList filter;
    filter << QString("*.") + Constants::S_EXTENSION;
    QStringList files = dir.entryList(filter, QDir::Files);

    for (int i=0; i<files.count(); ++i) {
        QString fileName = dir.absolutePath() + '/' + files.at(i);
        files[i] = fileName;
    }

    return files;
}

void ScriptManager::runFile(const QString &fileName)
{
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        const QString sourceCode = stream.readAll();

        Core::MessageManager::instance()->showOutputPane();
        Core::MessageManager::instance()->printToOutputPane(tr("Start %1...").arg(fileName),
                                                            Utils::NormalMessageFormat);
        if(m_runner->runScript(sourceCode, fileName))
            Core::MessageManager::instance()->printToOutputPane(tr("The script  exited normally\n"),
                                                                Utils::NormalMessageFormat);
        else
            Core::MessageManager::instance()->printToOutputPane(tr("The script has unexpectedly finished.\n"),
                                                                Utils::ErrorMessageFormat);
    }
    else {
        Core::MessageManager::instance()->printToOutputPane(tr("Error: %1 doesn't exist.\n").arg(fileName),
                                                            Utils::ErrorMessageFormat);
    }
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

        if (fi.isReadable()) {
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

    const Core::Id scriptId(makeScriptId(script));

    Core::ICore::actionManager()->registerShortcut(shortcut, scriptId, globalContext);
    connect(shortcut, SIGNAL(activated()), m_mapper, SLOT(map()));
    m_mapper->setMapping(shortcut, script.fileName);
}

void ScriptManager::removeScriptShortcut(const ScriptManager::Script &script)
{
    // Remove shortcut
    const Core::Id scriptId(makeScriptId(script));
    Core::ICore::actionManager()->unregisterShortcut(scriptId);
}
