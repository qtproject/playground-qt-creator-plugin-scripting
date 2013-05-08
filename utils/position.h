#ifndef SCRIPTING_INTERNAL_POSITION_H
#define SCRIPTING_INTERNAL_POSITION_H

#include <QMetaType>

namespace Scripting {
namespace Internal {

class Position
{
public:
    explicit Position(int line=1, int column=1);
    int line() const;
    void setLine(int line);
    int column() const;
    void setColumn(int column);

private:
    int m_line;
    int m_column;
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(Scripting::Internal::Position)

#endif // SCRIPTING_INTERNAL_POSITION_H
