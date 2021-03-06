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

#include "basetexteditor.h"

#include <texteditor/basetexteditor.h>

#include <coreplugin/messagemanager.h>

#include <QTextCursor>
#include "mark.h"

using namespace Scripting::Internal;

BaseTextEditor::BaseTextEditor(QObject *parent) :
    TextEditor(parent)
{
}

void BaseTextEditor::copy()
{
    if (textEditorWidget())
        textEditorWidget()->copy();
}

void BaseTextEditor::paste()
{
    if (textEditorWidget())
        textEditorWidget()->paste();
}

void BaseTextEditor::cut()
{
    if (textEditorWidget())
        textEditorWidget()->cut();
}

void BaseTextEditor::cutLine()
{
    if (textEditorWidget())
        textEditorWidget()->cutLine();
}

void BaseTextEditor::copyLine()
{
    if (textEditorWidget())
        textEditorWidget()->copyLine();
}

void BaseTextEditor::deleteSelection()
{
    if (textEditorWidget() && hasSelection())
        textEditorWidget()->textCursor().deleteChar();
}

void BaseTextEditor::deleteLine(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->deleteLine();
}

void BaseTextEditor::deleteEndOfWord(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->deleteEndOfWord();
}

void BaseTextEditor::deleteEndOfWordCamelCase(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->deleteEndOfWordCamelCase();
}

void BaseTextEditor::deleteStartOfWord(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->deleteStartOfWord();
}

void BaseTextEditor::deleteStartOfWordCamelCase(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->deleteStartOfWordCamelCase();
}

void BaseTextEditor::gotoBlockStart(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoBlockStart();
}

void BaseTextEditor::gotoBlockEnd(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoBlockEnd();
}

void BaseTextEditor::gotoLineStart(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoLineStart();
}

void BaseTextEditor::gotoLineEnd(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoLineEnd();
}

void BaseTextEditor::gotoNextLine(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoNextLine();
}

void BaseTextEditor::gotoPreviousLine(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoPreviousLine();
}

void BaseTextEditor::gotoPreviousCharacter(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoPreviousCharacter();
}

void BaseTextEditor::gotoNextCharacter(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoNextCharacter();
}

void BaseTextEditor::gotoPreviousWord(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoPreviousWord();
}

void BaseTextEditor::gotoNextWord(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoNextWord();
}

void BaseTextEditor::gotoPreviousWordCamelCase(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoPreviousWordCamelCase();
}

void BaseTextEditor::gotoNextWordCamelCase(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoNextWordCamelCase();
}

void BaseTextEditor::clearSelection()
{
    if (textEditorWidget())
        textEditorWidget()->textCursor().clearSelection();
}

bool BaseTextEditor::hasSelection()
{
    if (textEditorWidget())
        return textEditorWidget()->textCursor().hasSelection();
    return false;
}

void BaseTextEditor::selectAll()
{
    if (textEditorWidget())
        textEditorWidget()->selectAll();
}

void BaseTextEditor::selectBlockStart(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoBlockStartWithSelection();
}

void BaseTextEditor::selectBlockEnd(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoBlockEndWithSelection();
}

void BaseTextEditor::selectLineStart(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoLineStartWithSelection();
}

void BaseTextEditor::selectLineEnd(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoLineEndWithSelection();
}

void BaseTextEditor::selectNextLine(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoNextLineWithSelection();
}

void BaseTextEditor::selectPreviousLine(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoPreviousLineWithSelection();
}

void BaseTextEditor::selectPreviousCharacter(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoPreviousCharacterWithSelection();
}

void BaseTextEditor::selectNextCharacter(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoNextCharacterWithSelection();
}

void BaseTextEditor::selectPreviousWord(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoPreviousWordWithSelection();
}

void BaseTextEditor::selectNextWord(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoNextWordWithSelection();
}

void BaseTextEditor::selectPreviousWordCamelCase(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoPreviousWordCamelCaseWithSelection();
}

void BaseTextEditor::selectNextWordCamelCase(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->gotoNextWordCamelCaseWithSelection();
}

void BaseTextEditor::selectBlockUp(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->selectBlockUp();
}

void BaseTextEditor::selectBlockDown(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->selectBlockDown();
}

void BaseTextEditor::moveLineUp(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->moveLineUp();
}

void BaseTextEditor::moveLineDown(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->moveLineDown();
}

void BaseTextEditor::copyLineUp(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->copyLineUp();
}

void BaseTextEditor::copyLineDown(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->copyLineDown();
}

void BaseTextEditor::joinLines(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->joinLines();
}

void BaseTextEditor::insertLineAbove(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->insertLineAbove();
}

void BaseTextEditor::insertLineBelow(int count)
{
    if (textEditorWidget())
        for(int i=0; i<count; ++i)
            textEditorWidget()->insertLineBelow();
}

void BaseTextEditor::uppercaseSelection()
{
    if (textEditorWidget())
        textEditorWidget()->uppercaseSelection();
}

void BaseTextEditor::lowercaseSelection()
{
    if (textEditorWidget())
        textEditorWidget()->lowercaseSelection();
}

void BaseTextEditor::cleanWhitespace()
{
    if (textEditorWidget())
        textEditorWidget()->cleanWhitespace();
}

void BaseTextEditor::insertText(const QString &text)
{
    if (textEditorWidget())
        textEditorWidget()->insertPlainText(text);
}

QString BaseTextEditor::selectedText()
{
    if (textEditorWidget())
        return textEditorWidget()->textCursor().selectedText();
    return QString();
}

QString BaseTextEditor::text()
{
    if (textEditorWidget())
        return textEditorWidget()->toPlainText();
    return QString();
}

/**
 * @brief Create a mark for the given line and column
 *
 * If line and column isn't provided, the currentline and column is used.
 */
Mark *BaseTextEditor::createMark(int line, int column)
{
    if (line == -1)
        line = currentLine();
    if (column == -1)
        column = currentColumn();
    return Mark::create(this, line, column);
}

void BaseTextEditor::gotoMark(Mark * mark)
{
    gotoLine(mark->line(), mark->column());
}

/**
 * @brief Search for the given text
 *
 * In the case of search forward, the cursor will be placed after the match.
 * In the case of seatch backeard, the cursor will be place before the match.
 * @return true if a match is found
 */
bool BaseTextEditor::find(const QString &text, bool backward, bool caseSensitively, bool wholeWords)
{
    if (!textEditorWidget())
        return false;
    QTextDocument* doc = textEditorWidget()->document();

    QTextCursor cursor = doc->find(text, nativePosition(), flags(backward,caseSensitively,wholeWords));

    if (cursor.isNull())
        return false;

    if (backward)
        setCursorPosition(cursor.anchor());
    else
        setCursorPosition(cursor.position());

    return true;
}

/**
 * @brief Search for the given regular expression.
 *
 * In the case of search forward, the cursor will be placed after the match.
 * In the case of search backeard, the cursor will be place before the match.
 * @return true if a match is found
 */
bool BaseTextEditor::findRegexp(const QString &regexp, bool backward, bool caseSensitively, bool wholeWords)
{
    if (!textEditorWidget())
        return false;
    QTextDocument* doc = textEditorWidget()->document();


    QTextCursor cursor = doc->find(QRegExp(regexp), nativePosition(), flags(backward,caseSensitively,wholeWords));
    if (cursor.isNull())
        return false;

    if (backward) {
        // Unfortunately is the implementation of QTextDocument::find not greety,
        // we therefore need to run the search until it no longer matches.
        // Further the regexp object is copied in find(), so we will not be able to use it for capturing.
        // We might consider roling our own copy similar to QTextDocument::find
        const int endPoint = cursor.position();
        int pos = cursor.anchor();
        do {
            --pos;
            cursor = doc->find(QRegExp(regexp), pos, flags(false, caseSensitively, wholeWords));
        } while ( !cursor.isNull() && cursor.position() == endPoint && cursor.anchor() == pos);
        setCursorPosition(pos+1);
    }
    else
        setCursorPosition(cursor.position());

    return true;
}

void BaseTextEditor::deleteRegion(const Position &from, const Position &to)
{
    fetchSelectionAndDelete(from, to, true);
}

void BaseTextEditor::gotoDocumentStart()
{
    gotoLine(1,0);
}

void BaseTextEditor::gotoDocumentEnd()
{
    gotoLine(lineCount());
    gotoLineEnd();
}

int BaseTextEditor::lineCount()
{
    if (textEditorWidget())
        return textEditorWidget()->document()->blockCount();
    return 0;
}

QString BaseTextEditor::fetchSelectionAndDelete(const Position &from, const Position &to, bool del)
{
    QPointer<Mark> start = createMark();
    gotoPosition(from);
    int fromPos = nativePosition();
    gotoPosition(to);
    int toPos = nativePosition();
    QTextCursor cursor( textEditorWidget()->document());
    cursor.setPosition(fromPos);
    cursor.setPosition(toPos, QTextCursor::KeepAnchor);
    QString text = cursor.selectedText();
    if (del)
        cursor.removeSelectedText();
    gotoMark(start);
    return text;
}

void BaseTextEditor::indent()
{
    if (textEditorWidget())
        textEditorWidget()->format();
}

QTextDocument::FindFlags BaseTextEditor::flags(bool backward, bool caseSensitively, bool wholeWords) const
{
    QTextDocument::FindFlags result;
    if (backward)
        result |= QTextDocument::FindBackward;
    if (caseSensitively)
        result |= QTextDocument::FindCaseSensitively;
    if (wholeWords)
        result |= QTextDocument::FindWholeWords;

    return result;
}

::TextEditor::BaseTextEditorWidget * BaseTextEditor::textEditorWidget()
{
    ::TextEditor::BaseTextEditor *textEditor =
            qobject_cast< ::TextEditor::BaseTextEditor* >(editor());
    if (textEditor)
        return textEditor->editorWidget();
    return 0;
}


QString Scripting::Internal::BaseTextEditor::text(const Scripting::Internal::Position &from, const Scripting::Internal::Position &to)
{
    return fetchSelectionAndDelete(from, to, false);
}
