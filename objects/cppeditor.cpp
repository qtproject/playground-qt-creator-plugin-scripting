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

#include "cppeditor.h"
#include <cppeditor/cppeditor.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <cppeditor/cppeditorconstants.h>
#include "utils/signalwaiter.h"
#include "cppfunction.h"
#include <cpptools/cppmodelmanagerinterface.h>
#include "cppclass.h"
#include <cpptools/cpptoolsplugin.h>

namespace Scripting {
namespace Internal {

CppEditor::CppEditor(QObject *parent) :
    BaseTextEditor(parent)
{
}

void CppEditor::switchDeclarationDefinition()
{
    Core::ActionManager::command(::CppEditor::Constants::SWITCH_DECLARATION_DEFINITION)->action()->trigger();
}

void CppEditor::switchHeaderSourceFile()
{
    CppTools::Internal::CppToolsPlugin::instance()->switchHeaderSource();
}

CppFunction *CppEditor::currentFunction() const
{
    return functionAt(editor()->currentLine(), editor()->currentColumn());
}

CppClass *CppEditor::classAt(int line, int column) const
{
    return CppClass::create(line, column, editor()->document()->fileName());
}

CppClass* CppEditor::currentClass() const
{
    return classAt(editor()->currentLine(), editor()->currentColumn());
}

CppFunction* CppEditor::functionAt(int line, int column) const
{
    return CppFunction::create(line, column, editor()->document()->fileName());
}

/**
 \brief Wait for the editor to signal that it has been initialized after opening a file

  When opening a C++ file, the editor will asyncronicly parse the file. Until that has completed switchDeclarationDefinition() will not work.
*/
void CppEditor::waitForInitialized()
{
    CPlusPlus::Snapshot snapshot = CppTools::CppModelManagerInterface::instance()->snapshot();
    if (!snapshot.isEmpty())
        return;

    SignalWaiter waiter;
    const bool received = waiter.wait(CppTools::CppModelManagerInterface::instance(), SIGNAL(sourceFilesRefreshed(QStringList)), 1000);
    if ( !received )
        qWarning("editor did not complete initialization in time");
}

} // namespace Internal
} // namespace Scripting


