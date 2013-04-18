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
    static QString getText(const QString& title, const QString &label, const QString& defaultValue = QString());
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTING_INTERNAL_DIALOGS_H
