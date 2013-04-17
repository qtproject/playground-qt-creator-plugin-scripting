#ifndef SCRIPTING_INTERNAL_TEXTEDITOR_H
#define SCRIPTING_INTERNAL_TEXTEDITOR_H

#include "editor.h"
#include <texteditor/itexteditor.h>
#include "enums.h"

namespace Scripting {
namespace Internal {

class TextEditor : public Editor
{
    Q_OBJECT
public:

    explicit TextEditor(QObject *parent = 0);

public slots:
    int find(const QString &string) const;
    int position(Enums::PositionOperation posOp = Enums::Current, int at = -1) const;
    QPoint convertPosition(int pos) const;
    QRect cursorRect(int pos = -1) const;
    int columnCount() const;
    int rowCount() const;


    void remove(int length);
    void insert(const QString &string);
    void replace(int length, const QString &string);
    void setCursorPosition(int pos);
    void select(int toPos);

protected:
    ::TextEditor::ITextEditor * editor() const;
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTING_INTERNAL_TEXTEDITOR_H
