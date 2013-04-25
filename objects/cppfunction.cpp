#include "cppfunction.h"
#include <cplusplus/Symbol.h>
#include <cpptools/ModelManagerInterface.h>
#include <cplusplus/Overview.h>
#include "cppargument.h"

namespace Scripting {
namespace Internal {

CppFunction::CppFunction()
{
}

CppFunction *CppFunction::create(int line, int column, const QString &fileName)
{
    const CPlusPlus::Function* fun = function(line, column, fileName );
    if (!fun)
        return 0;

    // The fun object might be destructed at any time, so we need to collect all the information.
    CppFunction* result = new CppFunction; // QtScript takes ownership
    result->m_name = extractName(fun);
    result->m_returnType = extractReturnType(fun);
    result->m_arguments = extractArguments(fun);
    result->m_isVirtual = fun->isVirtual();
    result->m_isOverride = fun->isOverride();
    result->m_isFinal = fun->isFinal();
    result->m_isVariadic = fun->isVariadic();
    result->m_isConst = fun->isConst();
    result->m_isVolatile = fun->isVolatile();
    result->m_isPureVirtual = fun->isPureVirtual();

    return result;
}

CPlusPlus::Function *CppFunction::function(int line, int column, const QString &fileName)
{
    const CPlusPlus::Snapshot snapshot = CPlusPlus::CppModelManagerInterface::instance()->snapshot();
    const CPlusPlus::Document::Ptr document = snapshot.document(fileName);
    if (!document)
        return 0;

    CPlusPlus::Symbol *symbol = document->lastVisibleSymbolAt(line, column);
    if (!symbol)
        return 0;

    // Find the enclosing function scope (which might be several levels up, or we might be standing on it)
    CPlusPlus::Scope *scope;
    if (symbol->isScope())
        scope = symbol->asScope();
    else
        scope = symbol->enclosingScope();

    while (scope && !scope->isFunction() )
        scope = scope->enclosingScope();

    if (!scope)
        return 0;

    return scope->asFunction();
}

QString CppFunction::extractName(const CPlusPlus::Function *function)
{
    const CPlusPlus::Overview o;
    QString result = o(function->name());

    // Prepend namespace "Foo::Foo::foo()" up to empty root namespace
    for (const CPlusPlus::Symbol *owner = function->enclosingNamespace();
         owner; owner = owner->enclosingNamespace()) {
        const QString name = o(owner->name());
        if (name.isEmpty()) {
            break;
        } else {
            result.prepend(QLatin1String("::"));
            result.prepend(name);
        }
    }

    return result;
}

QString CppFunction::extractReturnType(const CPlusPlus::Function *function)
{
    return CPlusPlus::Overview()(function->returnType());
}

QList<CppArgument*> CppFunction::extractArguments(const CPlusPlus::Function *function)
{
    QList<CppArgument*> result;
    for (unsigned int i=0; i <function->argumentCount(); ++i ) {
        result.append(CppArgument::create(function->argumentAt(i)->asArgument()));
    }
    return result;
}

QString CppFunction::name() const
{
    return m_name;
}

QString CppFunction::returnType() const
{
    return m_returnType;
}

QList<CppArgument *> CppFunction::arguments() const
{
    return m_arguments;
}

bool CppFunction::isVirtual() const
{
    return m_isVirtual;
}

bool CppFunction::isOverride() const
{
    return m_isOverride;
}

bool CppFunction::isFinal() const
{
    return m_isFinal;
}

bool CppFunction::isVariadic() const
{
    return m_isVariadic;
}

bool CppFunction::isConst() const
{
    return m_isConst;
}

bool CppFunction::isVolatile() const
{
    return m_isVolatile;
}

bool CppFunction::isPureVirtual() const
{
    return m_isPureVirtual;
}


} // namespace Internal
} // namespace Scripting
