#ifndef SCRIPTING_INTERNAL_MARK_H
#define SCRIPTING_INTERNAL_MARK_H

#include <QObject>
#include <QPointer>
#include <QMetaType>

namespace Scripting {
namespace Internal {

class BaseTextEditor;

/**
 * @brief Keep track of a possition in a file
 * This class helps you track a logical possition in a file. It's line and column properties will change as text are deleted or inserted before the mark.
 */
class Mark : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName)
    Q_PROPERTY(int line READ line)
    Q_PROPERTY(int column READ column)

public:
    static Mark *create(BaseTextEditor*, int line, int column );
    QString fileName() const;
    int line() const;
    int column() const;

private slots:
    void update(int from, int charsRemoved, int charsAdded);

private:
    Mark(BaseTextEditor* editor, int column, int line);
    int convertPosition(int line,int column);

    int m_pos;
    QPointer<BaseTextEditor> m_editor;
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(Scripting::Internal::Mark*)

#endif // SCRIPTING_INTERNAL_MARK_H
