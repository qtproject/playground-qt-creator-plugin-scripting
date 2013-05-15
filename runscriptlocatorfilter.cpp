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

#include "runscriptlocatorfilter.h"
#include "scriptmanager.h"

using namespace Scripting;
using namespace Scripting::Internal;


RunScriptLocatorFilter::RunScriptLocatorFilter(QObject *parent) :
    Locator::ILocatorFilter(parent)
{
    setId("Run Script");
    setDisplayName(tr("Run Script"));
    setShortcutString(QLatin1String("rs"));
}

QList<Locator::FilterEntry> RunScriptLocatorFilter::matchesFor(QFutureInterface<Locator::FilterEntry> &future, const QString &entry)
{
    Q_UNUSED(future)
    QList<Locator::FilterEntry> result;

    const ScriptManager::ScriptList &scripts = ScriptManager::instance()->scriptList();

    foreach(const ScriptManager::Script &script, scripts) {
        if (script.name.contains(entry)) {
            QVariant id;
            Locator::FilterEntry entry(this, script.name, script.fileName);
            if (!script.projectName.isEmpty())
                entry.extraInfo = script.projectName + QLatin1String(" - ");
            entry.extraInfo += script.fileName;
            result.append(entry);
        }
    }

    return result;
}

void RunScriptLocatorFilter::accept(Locator::FilterEntry selection) const
{
    ScriptManager::instance()->runFile(selection.internalData.toString());
}

void RunScriptLocatorFilter::refresh(QFutureInterface<void> &future)
{
    Q_UNUSED(future)
}
