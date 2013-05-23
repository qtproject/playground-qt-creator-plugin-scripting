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

#include "ast.h"
#include <cplusplus/ASTPath.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <texteditor/basetexteditor.h>
#include <texteditor/basetextdocument.h>
#include <cpptools/cppmodelmanagerinterface.h>
#include <typeinfo>
#include <cpptools/cpprefactoringchanges.h>
#include <utils/changeset.h>
#include <QStringList>

namespace Scripting {
namespace Internal {

QStringList Ast::argumentsToFunction(int line, int column)
{
    // Fetch information about file
    Core::IEditor* editor = Core::EditorManager::instance()->currentEditor();
    const QString fileName = editor->document()->fileName();

    // Fetch the content of the file
    QString content = qobject_cast< ::TextEditor::BaseTextDocument*>(editor->document())->contents();

    // Fetch the AST of the document
    const CPlusPlus::Snapshot snapshot = CppTools::CppModelManagerInterface::instance()->snapshot();
    const CPlusPlus::Document::Ptr document = snapshot.preprocessedDocument(content, fileName);
    document->check();
    QList<CPlusPlus::AST *> path = CPlusPlus::ASTPath(document)(line, column);

    // Get our hand on the refactoring tools, so we can convert an AST to a string.
    CppTools::CppRefactoringChanges changes(snapshot);
    CppTools::CppRefactoringFilePtr ptr = changes.file(fileName);

    // Now find the call and extract the arguments.
    foreach (CPlusPlus::AST* ast, path ) {
        if ( CPlusPlus::CallAST * call  = ast->asCall() ) {
            QStringList result;
            for ( CPlusPlus::ExpressionListAST* list = call->expression_list; list; list = list->next ) {
                result.append(ptr->textOf(list->value));
            }
            return result;
        }
    }
    return QStringList();
}

} // namespace Internal
} // namespace Scripting
