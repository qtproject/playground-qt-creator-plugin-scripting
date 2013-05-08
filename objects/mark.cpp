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
    const int result = m_editor->position();

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
