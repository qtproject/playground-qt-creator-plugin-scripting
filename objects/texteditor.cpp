#include "texteditor.h"

namespace Scripting {
namespace Internal {

TextEditor::TextEditor(QObject *parent) :
    Editor(parent)
{
}

int TextEditor::position(Enums::PositionOperation posOp, int at) const
{
    return editor()->position( static_cast< ::TextEditor::ITextEditor::PositionOperation>(posOp), at);
}

QPoint TextEditor::convertPosition(int pos) const
{
    int line, column;
    editor()->convertPosition(pos,&line,&column);
    return QPoint(column,line);
}

QRect TextEditor::cursorRect(int pos) const
{
    return editor()->cursorRect(pos);
}

int TextEditor::columnCount() const
{
    return editor()->columnCount();
}

int TextEditor::rowCount() const
{
    return editor()->rowCount();
}

void TextEditor::remove(int length)
{
    editor()->remove(length);
}

void TextEditor::insert(const QString &string)
{
    editor()->insert(string);
}

void TextEditor::replace(int length, const QString &string)
{
    editor()->replace(length, string);
}

void TextEditor::setCursorPosition(int pos)
{
    editor()->setCursorPosition(pos);
}

void TextEditor::select(int toPos)
{
    editor()->select(toPos);
}

::TextEditor::ITextEditor *TextEditor::editor() const
{
    return qobject_cast< ::TextEditor::ITextEditor*>(Editor::editor());
}

} // namespace Internal
} // namespace Scripting
