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

#include "mark.h"
#include "basetexteditor.h"
#include <texteditor/basetexteditor.h>
#include "utils/position.h"

namespace Scripting {
namespace Internal {

Mark::Mark(BaseTextEditor *editor, int line, int column)
    :m_editor(editor)
{
    m_pos = convertPosition(line,column);
    ::TextEditor::BaseTextEditorWidget* widget = editor->textEditorWidget();
    QTextDocument* document = widget->document();
    connect( document, SIGNAL(contentsChange(int,int,int)), this, SLOT(update(int,int,int)));
}

int Mark::convertPosition(int line, int column)
{
    const int origLine = m_editor->currentLine();
    const int origColumn = m_editor->currentColumn();

    m_editor->gotoLine(line, column);
    const int result = m_editor->nativePosition();

    m_editor->gotoLine(origLine, origColumn);

    return result;
}

QString Mark::fileName() const
{
    return m_editor->fileName();
}

int Mark::line() const
{
    return m_editor->convertPosition(m_pos).line();
}

int Mark::column() const
{
    return m_editor->convertPosition(m_pos).column();
}

void Mark::update(int from, int charsRemoved, int charsAdded)
{
    if (m_pos <= from )
        return;

    const int delta = charsAdded - charsRemoved;

    // Overlap the position
    if ( m_pos <= from+charsRemoved )
        m_pos = from;
    else
        m_pos += delta;
}

Mark *Mark::create(BaseTextEditor *editor, int line, int column)
{
    // Object is owned by Qt Script
    return new Mark(editor, line, column);
}

} // namespace Internal
} // namespace Scripting
