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

#include "scriptwrappers.h"
#include "enumwappers.h"
#include "utils/dialogs.h"
#include "objects/cppfunction.h"
#include "objects/cppargument.h"
#include <QTextStream>
#include <QFile>
#include <coreplugin/messagemanager.h>
#include <utils/outputformat.h>
#include <QFileInfo>
#include "objects/mark.h"

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

// Path to the topmost script loaded.
static QString currentPath;

// The backtrace does unfortunately not include the file in which an error occurred,
// we therefore need this variable to store this information.
static QString errorFileName;

static QScriptValue run(QScriptEngine* engine, const QString& fileName, bool recursive)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {

        QTextStream stream(&file);
        const QString sourceCode = stream.readAll();

        if ( recursive ) {
            // A script context is pushed by the include function call.
            // Link that context to the one of the script that called include
            // Only do that, however, when called from the scipt
            QScriptContext *context = engine->currentContext();
            QScriptContext *parent=context->parentContext();
            context->setActivationObject(parent->activationObject());
            context->setThisObject(parent->thisObject());
        }

        QScriptValue result = engine->evaluate(sourceCode, fileName);
        if (engine->hasUncaughtException() && errorFileName.isNull() )
            errorFileName = fileName;

        return result;
    }
    else {
        Core::MessageManager::instance()->printToOutputPane(QObject::tr("Error: %1 doesn't exist.\n").arg(fileName),
                                                            Core::MessageManager::Flash);
        engine->abortEvaluation();
        return QScriptValue();
    }
}

static QScriptValue load(QScriptContext *context, QScriptEngine *engine)
{
    QScriptValue callee = context->callee();
    if (context->argumentCount() == 1)
        return run(engine, currentPath + QLatin1String("/") + context->argument(0).toString(), true);
    else
        context->throwError(QObject::tr("Wrong number of arguments given to import"));
    return QScriptValue();
}

ErrorMessage ScriptRunner::runScript(const QString fileName)
{
    errorFileName = QString();
    currentPath = QFileInfo(fileName).absolutePath();
    ensureEngineInitialized();

    // Ensure no polution of environment between script runs
    m_engine->pushContext();
    QScriptValue result = run(m_engine.data(), fileName, false);
    const bool failed = m_engine->hasUncaughtException();
    m_engine->popContext();

    // Set the focus back to the editor
    const Core::EditorManager *editorManager = Core::EditorManager::instance();
    if (editorManager->currentEditor())
        editorManager->currentEditor()->widget()->setFocus(Qt::OtherFocusReason);

    m_engine->collectGarbage();

    if (failed)
        return ErrorMessage(errorFileName, m_engine->uncaughtExceptionLineNumber(), result.toString());

    return ErrorMessage();
}

Q_DECLARE_METATYPE(QList<CppArgument*>)

ScriptRunner::QScriptEnginePtr ScriptRunner::ensureEngineInitialized()
{
    if (!m_engine.isNull())
        return m_engine;
    m_engine = QScriptEnginePtr(new QScriptEngine);

    qRegisterMetaType<Editor*>("Editor*");
    registerQObject<Editor>(m_engine.data());

    qRegisterMetaType<CppFunction*>("CppFunction*");
    registerQObject<CppFunction>(m_engine.data());

    qRegisterMetaType<CppArgument*>("CppArgument*");
    registerQObject<CppArgument>(m_engine.data());

    qRegisterMetaType<Mark*>("Mark*");
    registerQObject<Mark>(m_engine.data());

    qRegisterMetaType<Position>("Position");

    qScriptRegisterSequenceMetaType< QList<CppArgument*> >(m_engine.data());

    registerGlobal(new Console, QLatin1String("console"));
    registerGlobal(new Editors, QLatin1String("editors"));
    registerGlobal(new Dialogs, QLatin1String("dialogs"));
    registerWrappers(m_engine.data());
    registerEnums(m_engine.data());

    m_engine->globalObject().setProperty(QLatin1String("include"), m_engine->newFunction(load));
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
