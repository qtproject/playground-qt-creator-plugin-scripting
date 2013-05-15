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

#include "scriptingplugin.h"
#include "scriptingconstants.h"
#include "scriptmanager.h"
#include "runscriptlocatorfilter.h"
#include <coreplugin/messagemanager.h>

#include <QtPlugin>
#include <QFileInfo>

using namespace Scripting::Internal;

ScriptingPlugin::ScriptingPlugin()
{
}

ScriptingPlugin::~ScriptingPlugin()
{
    delete m_scriptManager;
}

bool ScriptingPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(errorString)

    addAutoReleasedObject(new RunScriptLocatorFilter);

    m_scriptManager = new ScriptManager(this);

    for ( int i=0; i< arguments.count(); ++i )
        if ( arguments[i] == QLatin1String("-execute-script"))
            m_startUpScript = arguments[i+1];

    return true;
}

void ScriptingPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // "In the extensionsInitialized method, a plugin can be sure that all
    //  plugins that depend on it are completely initialized."
}

bool ScriptingPlugin::delayedInitialize()
{
    if ( m_startUpScript.isNull() )
        return false;
    if (!QFileInfo(m_startUpScript).exists())
        Core::MessageManager::instance()->printToOutputPane(tr("File %1 doesn't exists").arg(m_startUpScript),
                                                            Core::MessageManager::Flash);
    else
        m_scriptManager->runFile(m_startUpScript);
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag ScriptingPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

Q_EXPORT_PLUGIN2(Scripting, ScriptingPlugin)
