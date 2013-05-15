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

#ifndef SCRIPTING_INTERNAL_TEXTEDITOR_H
#define SCRIPTING_INTERNAL_TEXTEDITOR_H

#include "editor.h"
#include <texteditor/itexteditor.h>
#include "enums.h"
#include "utils/position.h"

namespace Scripting {
namespace Internal {

class TextEditor : public Editor
{
    Q_OBJECT
public:
    explicit TextEditor(QObject *parent = 0);
    int nativePosition(Enums::PositionOperation posOp = Enums::Current, int at = -1) const;
    Position convertPosition(int pos) const;

public slots:
    Position position(Enums::PositionOperation posOp = Enums::Current, int at = -1) const;
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
