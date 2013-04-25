#include "cppargument.h"

#include <cplusplus/Symbol.h>
#include <cplusplus/Symbols.h>
#include <cplusplus/Overview.h>
#include <cplusplus/Literals.h>

namespace Scripting {
namespace Internal {


CppArgument *CppArgument::create(CPlusPlus::Argument* argument)
{
    // Instance owned by QtScript
    CppArgument* result = new CppArgument;

    CPlusPlus::Overview o;
    result->m_name = o(argument->name());
    result->m_type = o(argument->type());
    result->m_initializer = argument->initializer() ? QString::fromUtf8(argument->initializer()->chars()) : QString();
    return result;
}

QString CppArgument::name() const
{
    return m_name;
}

QString CppArgument::type() const
{
    return m_type;
}

QString CppArgument::initializer() const
{
    return m_initializer;
}

CppArgument::CppArgument()
{
}

} // namespace Internal
} // namespace Scripting
