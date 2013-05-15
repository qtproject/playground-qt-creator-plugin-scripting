#include "cppeditor.h"
#include <cppeditor/cppeditor.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <cppeditor/cppeditorconstants.h>
#include "utils/signalwaiter.h"
#include "cppfunction.h"
#include <cpptools/cppmodelmanagerinterface.h>
#include "cppclass.h"

namespace Scripting {
namespace Internal {

CppEditor::CppEditor(QObject *parent) :
    BaseTextEditor(parent)
{
}

void CppEditor::switchDeclarationDefinition()
{
    Core::ActionManager::command(::CppEditor::Constants::SWITCH_DECLARATION_DEFINITION)->action()->trigger();
}

CppFunction *CppEditor::currentFunction() const
{
    return functionAt(editor()->currentLine(), editor()->currentColumn());
}

CppClass *CppEditor::classAt(int line, int column) const
{
    return CppClass::create(line, column, editor()->document()->fileName());
}

CppClass* CppEditor::currentClass() const
{
    return classAt(editor()->currentLine(), editor()->currentColumn());
}

CppFunction* CppEditor::functionAt(int line, int column) const
{
    return CppFunction::create(line, column, editor()->document()->fileName());
}

/**
 \brief Wait for the editor to signal that it has been initialized after opening a file

  When opening a C++ file, the editor will asyncronicly parse the file. Until that has completed switchDeclarationDefinition() will not work.
*/
void CppEditor::waitForInitialized()
{
    CPlusPlus::Snapshot snapshot = CppTools::CppModelManagerInterface::instance()->snapshot();
    if (!snapshot.isEmpty())
        return;

    SignalWaiter waiter;
    const bool received = waiter.wait(CppTools::CppModelManagerInterface::instance(), SIGNAL(sourceFilesRefreshed(QStringList)), 1000);
    if ( !received )
        qWarning("editor did not complete initialization in time");
}

} // namespace Internal
} // namespace Scripting


