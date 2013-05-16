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

#include "enums.h"

QDir::Filters Enums::convertFilters(int filters)
{
    QDir::Filters result;
    if ( filters & Dirs )
        result |= QDir::Dirs;

    if ( filters & Files )
        result |= QDir::Files;

    if ( filters & Drives )
        result |= QDir::Drives;

    if ( filters & NoSymLinks )
        result |= QDir::NoSymLinks;

    if ( filters & Readable )
        result |= QDir::Readable;

    if ( filters & Writable )
        result |= QDir::Writable;

    if ( filters & Executable )
        result |= QDir::Executable;

    if ( filters & Modified )
        result |= QDir::Modified;

    if ( filters & Hidden )
        result |= QDir::Hidden;

    if ( filters & System )
        result |= QDir::System;

    if ( filters & AllDirs )
        result |= QDir::AllDirs;

    if ( filters & CaseSensitive )
        result |= QDir::CaseSensitive;

    if ( filters & NoDotAndDotDot )
        result |= QDir::NoDotAndDotDot;

    if ( filters & NoDot )
        result |= QDir::NoDot;

    if ( filters & NoDotDot )
        result |= QDir::NoDotDot;

    return result;
}

QDir::SortFlags Enums::convertSortFlag(int sort)
{
    QDir::SortFlags result;
    if ( sort & Name )
        result |= QDir::Name;

    if ( sort & Time )
        result |= QDir::Time;

    if ( sort & Size )
        result |= QDir::Size;

    if ( sort & DirsFirst )
        result |= QDir::DirsFirst;

    if ( sort & Reversed )
        result |= QDir::Reversed;

    if ( sort & IgnoreCase )
        result |= QDir::IgnoreCase;

    if ( sort & DirsLast )
        result |= QDir::DirsLast;

    if ( sort & LocaleAware )
        result |= QDir::LocaleAware;

    if ( sort & Type )
        result |= QDir::Type;

    return result;

}
