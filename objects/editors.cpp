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
    Core::IEditor* editor = Core::EditorManager::instance()->openEditor(ScriptRunner::absolutePath(fileName));
    if (editor) {
        Editor* wrapper = wrapEditor(editor);
        wrapper->waitForInitialized();
        return wrapper;
    }
    return 0;
}
