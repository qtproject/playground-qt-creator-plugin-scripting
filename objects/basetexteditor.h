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

#ifndef TEXTEDITORWRAPPER_H
#define TEXTEDITORWRAPPER_H

#include "texteditor.h"
#include <QTextDocument>

namespace TextEditor {
    class BaseTextEditor;
    class BaseTextEditorWidget;
}

namespace Scripting {
namespace Internal {

class Mark;

class BaseTextEditor : public TextEditor
{
    Q_OBJECT
public:
    explicit BaseTextEditor(QObject *parent=0);
    ::TextEditor::BaseTextEditorWidget *textEditorWidget();

public slots:
    void copy();
    void paste();
    void cut();
    void cutLine();
    void copyLine();

    void deleteSelection();
    void deleteLine(int count=1);
    void deleteEndOfWord(int count=1);
    void deleteEndOfWordCamelCase(int count=1);
    void deleteStartOfWord(int count=1);
    void deleteStartOfWordCamelCase(int count=1);

    void gotoBlockStart(int count=1);
    void gotoBlockEnd(int count=1);
    void gotoLineStart(int count=1);
    void gotoLineEnd(int count=1);
    void gotoNextLine(int count=1);
    void gotoPreviousLine(int count=1);
    void gotoPreviousCharacter(int count=1);
    void gotoNextCharacter(int count=1);
    void gotoPreviousWord(int count=1);
    void gotoNextWord(int count=1);
    void gotoPreviousWordCamelCase(int count=1);
    void gotoNextWordCamelCase(int count=1);

    void clearSelection();
    bool hasSelection();
    void selectAll();

    void selectBlockStart(int count=1);
    void selectBlockEnd(int count=1);
    void selectLineStart(int count=1);
    void selectLineEnd(int count=1);
    void selectNextLine(int count=1);
    void selectPreviousLine(int count=1);
    void selectPreviousCharacter(int count=1);
    void selectNextCharacter(int count=1);
    void selectPreviousWord(int count=1);
    void selectNextWord(int count=1);
    void selectPreviousWordCamelCase(int count=1);
    void selectNextWordCamelCase(int count=1);
    void selectBlockUp(int count=1);
    void selectBlockDown(int count=1);

    void moveLineUp(int count=1);
    void moveLineDown(int count=1);
    void copyLineUp(int count=1);
    void copyLineDown(int count=1);
    void joinLines(int count=1);

    void insertLineAbove(int count=1);
    void insertLineBelow(int count=1);

    void uppercaseSelection();
    void lowercaseSelection();

    void cleanWhitespace();

    void insertText(const QString &text);
    QString selectedText();
    QString text();

    // Own implementation - ie. not in the interface of ::TextEditor::BaseTextEditorWidget
    Mark* createMark(int line=-1, int column=-1);
    void gotoMark(Mark*);

    bool find(const QString& text, bool backward = false, bool caseSensitively = false, bool wholeWords = false);
    bool findRegexp(const QString& regexp, bool backward = false, bool caseSensitively = false, bool wholeWords = false);

private:
    QTextDocument::FindFlags flags(bool backward, bool caseSensitively, bool wholeWords) const;
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(Scripting::Internal::BaseTextEditor*)

#endif // TEXTEDITORWRAPPER_H
