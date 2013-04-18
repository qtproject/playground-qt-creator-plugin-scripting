#include "dialogs.h"
#include <QInputDialog>

namespace Scripting {
namespace Internal {

Dialogs::Dialogs(QObject *parent) :
    QObject(parent)
{
}

QString Dialogs::getText(const QString &title, const QString& label, const QString &defaultValue)
{
    return QInputDialog::getText(0, title, label, QLineEdit::Normal, defaultValue);
}

} // namespace Internal
} // namespace Scripting
