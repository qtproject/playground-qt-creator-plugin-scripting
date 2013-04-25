#ifndef SCRIPTING_INTERNAL_CPPFUNCTION_H
#define SCRIPTING_INTERNAL_CPPFUNCTION_H

#include <QObject>
#include <QMetaType>
#include <QList>

namespace CPlusPlus {
    class Function;
}

namespace Scripting {
namespace Internal {

class CppArgument;

class CppFunction : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString name READ name )
    Q_PROPERTY( QString returnType READ returnType )
    Q_PROPERTY( QList<CppArgument*> arguments READ arguments )
    Q_PROPERTY( bool isVirtual READ isVirtual )
    Q_PROPERTY( bool isOverride READ isOverride )
    Q_PROPERTY( bool isFinal READ isFinal )
    Q_PROPERTY( bool isVariadic READ isVariadic )
    Q_PROPERTY( bool isConst READ isConst )
    Q_PROPERTY( bool isVolatile READ isVolatile )
    Q_PROPERTY( bool isPureVirtual READ isPureVirtual )

public:
    static CppFunction* create(int line, int column, const QString& fileName);
    QString name() const;
    QString returnType() const;
    QList<CppArgument*> arguments() const;
    bool isVirtual() const;
    bool isOverride() const;
    bool isFinal() const;
    bool isVariadic() const;
    bool isConst() const;
    bool isVolatile() const;
    bool isPureVirtual() const;

private:
    CppFunction();
    static CPlusPlus::Function* function(int line,int column, const QString& fileName);
    static QString extractName(const CPlusPlus::Function* function);
    static QString extractReturnType(const CPlusPlus::Function* function);
    static QList<CppArgument *> extractArguments(const CPlusPlus::Function* function);

    QString m_name;
    QString m_returnType;
    QList<CppArgument*> m_arguments;
    bool m_isVirtual;
    bool m_isOverride;
    bool m_isFinal;
    bool m_isVariadic;
    bool m_isConst;
    bool m_isVolatile;
    bool m_isPureVirtual;
};

} // namespace Internal
} // namespace Scripting

Q_DECLARE_METATYPE(Scripting::Internal::CppFunction*)

#endif // SCRIPTING_INTERNAL_CPPFUNCTION_H
