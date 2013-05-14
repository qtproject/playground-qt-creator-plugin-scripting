include("../test.js")

var editor = editors.openFile("test.cpp")

editor.gotoLine(1,0)
verifyPosition(1,0, "beginning of file")

editor.gotoLineEnd()
verifyPosition(1,11, "end of line")

editor.gotoLineStart()
verifyPosition(1,0, "start of line")

editor.gotoLineEnd()
editor.gotoBlockEnd()
verifyPosition(5,1, "end of block")

editor.close()
