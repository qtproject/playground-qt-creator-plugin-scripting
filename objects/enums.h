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

#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include <QMetaType>
#include <QDir>

/** This class exports enums needed on the scripting side

  This is a placeholder for those enums that are in QtCreator (hence outside our control),
  and which we do not have Q_ENUMS registered fo them.
*/
class Enums :public QObject {
    Q_OBJECT
public:
    /** copied from ::TextEditor::ITextEditor::PositionOperation */
    enum PositionOperation {
        Current = 1,
        EndOfLine = 2,
        StartOfLine = 3,
        Anchor = 4,
        EndOfDoc = 5
    };
    Q_ENUMS(PositionOperation)

    enum Filter {
        Dirs = QDir::Dirs,
        Files = QDir::Files,
        Drives = QDir::Drives,
        NoSymLinks = QDir::NoSymLinks,
        AllEntries = QDir::AllEntries,
        TypeMask = QDir::TypeMask,
        Readable = QDir::Readable,
        Writable = QDir::Writable,
        Executable = QDir::Executable,
        PermissionMask = QDir::PermissionMask,
        Modified = QDir::Modified,
        Hidden = QDir::Hidden,
        System = QDir::System,
        AccessMask = QDir::AccessMask,
        AllDirs = QDir::AllDirs,
        CaseSensitive = QDir::CaseSensitive,
        NoDotAndDotDot = QDir::NoDotAndDotDot,
        NoDot = QDir::NoDot,
        NoDotDot = QDir::NoDotDot,
        NoFilter = QDir::NoFilter,
    };
    Q_ENUMS(Filter)

    enum SortFlag {
        Name = QDir::Name,
        Time = QDir::Time,
        Size = QDir::Size,
        Unsorted = QDir::Unsorted,
        SortByMask = QDir::SortByMask,

        DirsFirst = QDir::DirsFirst,
        Reversed = QDir::Reversed,
        IgnoreCase = QDir::IgnoreCase,
        DirsLast = QDir::DirsLast,
        LocaleAware = QDir::LocaleAware,
        Type = QDir::Type,
        NoSort = QDir::NoSort
    };
    Q_ENUMS(SortFlag)

    static QDir::Filters convertFilters(int filters);
    static QDir::SortFlags convertSortFlag(int sort);
};

Q_DECLARE_METATYPE(Enums::PositionOperation)
Q_DECLARE_METATYPE(Enums::Filter)
Q_DECLARE_METATYPE(Enums::SortFlag)
#endif // ENUMS_H
