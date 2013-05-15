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

#ifndef SCRIPTRUNNER_H
#define SCRIPTRUNNER_H

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QScriptEngine>

namespace Scripting {
namespace Internal {

struct ErrorMessage {
    ErrorMessage() : hasError(false) {}
    ErrorMessage(const QString& fileName, int line, const QString& message) : hasError(true), fileName(fileName), line(line), message(message) {}

    bool hasError;
    QString fileName;
    int line;
    QString message;
};

/**
 * \brief Script Runner
 *
 * Provide a script engine and a way to run scripts.
 * The script engine is initialized with interfaces.
 */
class ScriptRunner : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<QScriptEngine> QScriptEnginePtr;

    explicit ScriptRunner(QObject *parent = 0);
    static ScriptRunner* instance();
    virtual ~ScriptRunner();

    // Run a script
    ErrorMessage runScript(const QString fileName);

    QScriptEnginePtr scriptEngine() { return ensureEngineInitialized(); }
    static QString absolutePath(const QString& path);

private:
    QScriptEnginePtr ensureEngineInitialized();
    void registerGlobal(QObject *object, const QString &name);

private:
    QScriptEnginePtr m_engine;
    static ScriptRunner* m_instance;
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTMANAGER_H
