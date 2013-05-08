#include "position.h"

namespace Scripting {
namespace Internal {

Position::Position(int line, int column)
    : m_line(line), m_column(column)
{
}

int Position::line() const
{
    return m_line;
}

void Position::setLine(int line)
{
    m_line = line;
}

int Position::column() const
{
    return m_column;
}

void Position::setColumn(int column)
{
    m_column = column;
}


} // namespace Internal
} // namespace Scripting
