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

#include "scriptrunner.h"

#include "objects/console.h"
#include "objects/editor.h"
#include "objects/basetexteditor.h"
#include "objects/editors.h"

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>

#include <wrap_helpers.h>
#include "scriptwrappers.h"
#include "enumwappers.h"

using namespace Scripting;
using namespace Scripting::Internal;


ScriptRunner::ScriptRunner(QObject *parent) :
   QObject(parent),
   m_engine(0)
{
}

ScriptRunner::~ScriptRunner()
{
}


ErrorMessage ScriptRunner::runScript(const QString &sourceCode, const QString fileName)
{
    ensureEngineInitialized();

    m_engine->pushContext();
    QScriptValue result = m_engine->evaluate(sourceCode, fileName);

    const bool failed = m_engine->hasUncaughtException();
    m_engine->popContext();

    // Set the focus back to the editor
    const Core::EditorManager *editorManager = Core::EditorManager::instance();
    if (editorManager->currentEditor())
        editorManager->currentEditor()->widget()->setFocus(Qt::OtherFocusReason);

    if ( failed)
        return ErrorMessage(m_engine->uncaughtExceptionLineNumber(), result.toString());

    return ErrorMessage();
}


ScriptRunner::QScriptEnginePtr ScriptRunner::ensureEngineInitialized()
{
    if (!m_engine.isNull())
        return m_engine;
    m_engine = QScriptEnginePtr(new QScriptEngine);

    qRegisterMetaType<Editor*>("Editor*");
    SharedTools::registerQObject<Editor>(m_engine.data());

    qRegisterMetaType<BaseTextEditor*>("BaseTextEditor*");
    SharedTools::registerQObject<BaseTextEditor>(m_engine.data());

    registerGlobal(new Console, QLatin1String("console"));
    registerGlobal(new Editors, QLatin1String("editors"));
    registerWrappers(m_engine.data());
    registerEnums(m_engine.data());
    return m_engine;
}

void ScriptRunner::registerGlobal(QObject *object, const QString &name)
{
    if (!m_engine.isNull()) {
        object->setParent(this);
        QScriptValue value = m_engine->newQObject(object, QScriptEngine::QtOwnership);
        m_engine->globalObject().setProperty(name, value);
    }
}
