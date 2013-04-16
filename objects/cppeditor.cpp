#include "cppeditor.h"
#include <cppeditor/cppeditor.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <cppeditor/cppeditorconstants.h>
#include "signalwaiter.h"

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


/**
 \brief Wait for the editor to signal that it has been initialized after opening a file

  When opening a C++ file, the editor will asyncronicly parse the file. Until that has completed switchDeclarationDefinition() will not work.
*/
void CppEditor::waitForInitialized()
{
    SignalWaiter waiter;
    const bool received = waiter.wait(CPlusPlus::CppModelManagerInterface::instance(), SIGNAL(sourceFilesRefreshed(QStringList)), 1000);
    if ( !received )
        qWarning("editor did not complete initialization in time");
}

} // namespace Internal
} // namespace Scripting


