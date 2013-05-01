// This example shows how to use a mark to remember a position in the text, while text changes around it.
var editor = editors.current()
var mark = editor.createMark();
editor.gotoLineStart();
editor.insertText("/*")
editor.gotoLineEnd();
editor.insertText("*/")
editor.gotoMark(mark);
