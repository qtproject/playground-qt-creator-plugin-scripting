// This simple example shows how to use mark to remember positions
// and currentFunction to retrieve information about the function.

var editor = editors.current()
var start = editor.createMark()

editor.gotoPosition(editor.currentFunction.start)

editor.find("{")
var startOfFunction = editor.position()
editor.gotoBlockEnd()
editor.gotoLineStart();
editor.insert("*/\n")
editor.gotoPosition(startOfFunction)
editor.insert("\n/*")

editor.gotoPosition(start)
