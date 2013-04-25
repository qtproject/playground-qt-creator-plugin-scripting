#ifndef SCRIPTING_INTERNAL_CPPARGUMENT_H
#define SCRIPTING_INTERNAL_CPPARGUMENT_H

#include <QObject>
#include <QMetaType>

namespace CPlusPlus {
    class Argument;
}

namespace Scripting {
namespace Internal {

class CppArgument : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString initializer READ initializer)

public:
    static CppArgument* create( CPlusPlus::Argument* );

    QString name() const;
    QString type() const;
    QString initializer() const;

private:
    CppArgument();

    QString m_name;
    QString m_type;
    QString m_initializer;
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(Scripting::Internal::CppArgument*)

#endif // SCRIPTING_INTERNAL_CPPARGUMENT_H
