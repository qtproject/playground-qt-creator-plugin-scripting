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
    Mark(BaseTextEditor* editor, int line, int column);
    int convertPosition(int line,int column);

    int m_pos;
    QPointer<BaseTextEditor> m_editor;
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(Scripting::Internal::Mark*)

#endif // SCRIPTING_INTERNAL_MARK_H
