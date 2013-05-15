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

#ifndef SCRIPTING_H
#define SCRIPTING_H

#include "scripting_global.h"

#include <extensionsystem/iplugin.h>

/**
    \mainpage

    <h1>Overall design</h1>

    \li It all starts in \ref Scripting::Internal::ScriptingPlugin which is executed by Qt Creator at startup.
    \li The script runner registers a locator action called <b>rs</b> - see \ref Scripting::Internal::RunScriptLocatorFilter
    \li The ground work of finding scripts, registering shortcuts and starting their execution is done in \ref Scripting::Internal::ScriptManager
    \li \ref Scripting::Internal::ScriptRunner contains the JavaScript engine and register the objects available in the scripts

    <h1>Objects available in the scripts</h1>

    \li <b>console</b> accesses an instance of \ref Scripting::Internal::Console
    \code console.log("Hello world")\endcode

    \li <b>editors</b> accesses an instance of \ref Scripting::Internal::Editors.
    \code editors.current().selectAll()\endcode
*/

namespace Scripting {
namespace Internal {

class ScriptManager;

class ScriptingPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT

public:
    ScriptingPlugin();
    ~ScriptingPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private:
    ScriptManager *m_scriptManager;
    QString m_startUpScript;
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTING_H
