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

#include "editor.h"

#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/idocument.h>
#include <coreplugin/editormanager/editormanager.h>

using namespace Scripting;
using namespace Scripting::Internal;


Editor::Editor(QObject *parent):
    QObject(parent),
    m_editor(0)
{
}

void Editor::setEditor(Core::IEditor *editor)
{
    m_editor = editor;
}

bool Editor::exists() const
{
    return m_editor->widget()!=0;
}

bool Editor::save()
{
    QString errorString;
    return m_editor->document()->save(&errorString);
}

/**
  @brief Returns the current line of the cursor
  The line number is 1 based, therefore the first line of the document is line 1
*/
int Editor::currentLine() const
{
    return m_editor->currentLine();
}

/*!
  \brief return the column of the cursor.
  The column is zero based, so the column before the first character is column 0
 */
int Editor::currentColumn() const
{
    // Work around:
    // Core::IEditor::currentColumn() is 1 based, while gotoLine is 0 based for the column.
    return m_editor->currentColumn() -1;
}

/**
  @brief goto the given line in the current document
  line is one base, column is zero based. Therfore the position before the first character is line 1 column 0
*/
void Editor::gotoLine(int line, int column)
{
    m_editor->gotoLine(line, column);
}

void Editor::gotoPosition(const Position &pos)
{
    gotoLine(pos.line(), pos.column());
}

QString Editor::fileName() const
{
    if (m_editor->document())
        return m_editor->document()->fileName();
    return QString();
}

void Editor::close()
{
    Core::EditorManager::instance()->closeEditors(QList<Core::IEditor*>() << m_editor, false);
}

Core::IEditor * Editor::editor() const
{
    return m_editor;
}
