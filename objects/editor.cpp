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

#include "editor.h"

#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/ifile.h>

using namespace Scripting;
using namespace Scripting::Internal;


Editor::Editor(QObject *parent):
    QObject(parent),
    m_editor(0)
{
}

void Editor::setEditor(Core::IEditor *editor)
{
    m_editor = editor;
}

bool Editor::exists()
{
    return m_editor->widget()!=0;
}

bool Editor::save()
{
    QString errorString;
    return m_editor->file()->save(&errorString);
}

int Editor::currentLine()
{
    return m_editor->currentLine();
}

int Editor::currentColumn()
{
    return m_editor->currentColumn();
}

void Editor::gotoLine(int line, int column)
{
    m_editor->gotoLine(line, column);
}

QString Editor::fileName()
{
    if (m_editor->file())
        return m_editor->file()->fileName();
    return QString();
}

Core::IEditor * Editor::editor()
{
    return m_editor;
}
