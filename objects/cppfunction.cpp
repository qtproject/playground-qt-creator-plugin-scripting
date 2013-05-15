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

#include "cppfunction.h"
#include <cplusplus/Symbol.h>
#include <cpptools/cppmodelmanagerinterface.h>
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
    result->m_start = Position(fun->line(),fun->column());

    return result;
}

CPlusPlus::Function *CppFunction::function(int line, int column, const QString &fileName)
{
    const CPlusPlus::Snapshot snapshot = CppTools::CppModelManagerInterface::instance()->snapshot();
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

Position CppFunction::start() const
{
    return m_start;
}


} // namespace Internal
} // namespace Scripting
