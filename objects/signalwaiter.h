#ifndef SCRIPTING_INTERNAL_SIGNALWAITER_H
#define SCRIPTING_INTERNAL_SIGNALWAITER_H

#include <QObject>

namespace Scripting {
namespace Internal {

/**
 * @brief Wait for a signal to emit
 *
 * The method wait will block until the provided signal is emitted or the time out is reached. While blocking it will run the event loop.
 */
class SignalWaiter : public QObject
{
    Q_OBJECT
public:
    explicit SignalWaiter(QObject *parent = 0);
    bool wait(QObject* object, const char* signal, int msecs);

private slots:
    void slotReceived();

private:
    bool m_received;
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTING_INTERNAL_SIGNALWAITER_H
