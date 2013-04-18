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
