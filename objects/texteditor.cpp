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

#include "texteditor.h"
#include "utils/position.h"

namespace Scripting {
namespace Internal {

TextEditor::TextEditor(QObject *parent) :
    Editor(parent)
{
}

int TextEditor::nativePosition(Enums::PositionOperation posOp, int at) const
{
    return editor()->position( static_cast< ::TextEditor::ITextEditor::PositionOperation>(posOp), at);
}

Position TextEditor::convertPosition(int pos) const
{
    int line, column;
    editor()->convertPosition(pos,&line,&column);
    return Position(line,column);
}

Position TextEditor::position(Enums::PositionOperation posOp, int at) const
{
    return convertPosition(nativePosition(posOp,at));
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
