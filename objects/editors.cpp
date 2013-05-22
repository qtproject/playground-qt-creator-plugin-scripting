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

#include "editors.h"
#include "cppeditor.h"
#include "editor.h"
#include "basetexteditor.h"

#include <coreplugin/editormanager/editormanager.h>
#include <texteditor/basetexteditor.h>
#include <coreplugin/idocument.h>
#include <coreplugin/editormanager/ieditor.h>
#include <cpptools/cppmodelmanagerinterface.h>
#include "scriptrunner.h"
#include <designer/formwindoweditor.h>
#include <texteditor/plaintexteditor.h>
#include <coreplugin/coreconstants.h>
using namespace Scripting;
using namespace Scripting::Internal;

Editors::Editors(QObject *parent) :
    QObject(parent)
{
}

static Editor *wrapEditor(Core::IEditor *editor) {
    Editor *wrapper;

    const QString fileName = editor->document()->fileName();
    if ( CppTools::CppModelManagerInterface::instance()->isCppEditor(editor) )
        wrapper = new Scripting::Internal::CppEditor;
    else if (qobject_cast<TextEditor::BaseTextEditor*>(editor))
        wrapper = new BaseTextEditor;
    else if ( Designer::FormWindowEditor* designerEditor = qobject_cast<Designer::FormWindowEditor*>(editor) ) {
        wrapper = new BaseTextEditor;
        wrapper->setEditor(designerEditor->textEditor());
        return wrapper;
    }
    else
        wrapper = new Editor;

    wrapper->setEditor(editor);
    return wrapper;
}

Editor * Editors::current()
{
    Core::IEditor *editor = Core::EditorManager::instance()->currentEditor();
    if ( editor )
        return wrapEditor(editor);
    else
        return 0;
}

bool Editors::hasEditor(const QString &fileName)
{
    return Core::EditorManager::instance()->hasEditor(fileName);
}

QStringList Editors::existingEditors()
{
    QStringList result;
    foreach (Core::IEditor* editor, Core::EditorManager::instance()->openedEditors()) {
        result.append(editor->document()->fileName());
    }
    return result;
}

Editor *Editors::openFile(const QString &fileName)
{
    Core::IEditor* editor;
    if (fileName.endsWith(QLatin1String(".ui"))) {
        // Force the text editor for UI files, otherwise it will be read only in text mode.
        editor = Core::EditorManager::instance()->openEditor(ScriptRunner::absolutePath(fileName), Core::Constants::K_DEFAULT_TEXT_EDITOR_ID);
    }
    else
        editor = Core::EditorManager::instance()->openEditor(ScriptRunner::absolutePath(fileName) );
    if (editor) {
        Editor* wrapper = wrapEditor(editor);
        wrapper->waitForInitialized();
        return wrapper;
    }
    return 0;
}
