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

#include "signalwaiter.h"

#include <QElapsedTimer>
#include <QCoreApplication>

namespace Scripting {
namespace Internal {

SignalWaiter::SignalWaiter(QObject *parent) :
    QObject(parent), m_received(false)
{
}

bool SignalWaiter::wait(QObject *object, const char *signal, int msecs)
{
    connect( object, signal, this, SLOT(slotReceived()));
    QElapsedTimer timer;
    timer.start();
    while ( !m_received && timer.elapsed() < msecs ) {
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents, 100);
    }
    return m_received;
}

void SignalWaiter::slotReceived()
{
    m_received = true;
}

} // namespace Internal
} // namespace Scripting
