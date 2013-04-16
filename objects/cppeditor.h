#ifndef SCRIPTING_INTERNAL_CPPEDITOR_H
#define SCRIPTING_INTERNAL_CPPEDITOR_H

#include "basetexteditor.h"
#include <cppeditor/cppeditor.h>

//namespace CppEditor {
//    namespace Internal {
//      class CppEditorWidget;
//    }
//};

namespace Scripting {
namespace Internal {

class CppEditor : public BaseTextEditor
{
    Q_OBJECT
public:
    explicit CppEditor(QObject *parent = 0);

public slots:
    void switchDeclarationDefinition();

protected:
    void waitForInitialized();
};

} // namespace Internal
} // namespace Scripting

#endif // SCRIPTING_INTERNAL_CPPEDITOR_H
