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

#ifndef SCRIPTING_INTERNAL_DIALOGS_H
#define SCRIPTING_INTERNAL_DIALOGS_H

#include <QObject>

namespace Scripting {
namespace Internal {

/**
 * @brief Asks user for various input
 */
class Dialogs : public QObject
{
    Q_OBJECT
public:
    explicit Dialogs(QObject *parent = 0);

public slots:
    QString getText(const QString& title, const QString &label, const QString& defaultValue = QString());
    bool yesNoQuestion(const QString& title, const QString &label, const QString &details = QString(), const QString &yesLabel = tr("Yes"), const QString &noLabel = tr("No"));
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTING_INTERNAL_DIALOGS_H
