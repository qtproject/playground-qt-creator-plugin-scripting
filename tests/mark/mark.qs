include("../test.js")

markMove()
markStays()
markMoveOnPrevChar()
markStaysOnNextChar()

function findYay(editor) {
    editor.gotoLine(1,0)
    editor.find("yay")
}

function markMove() {
    var editor = editors.openFile("test.cpp")
    findYay(editor)
    var mark = editor.createMark()
    editor.gotoLine(1,0)
    editor.insert("Hello World\n")
    findYay(editor)
    comparePositions(editor.position(),mark, "ensure mark moves on new lines")
    editor.close()
}

function markStays() {
    var editor = editors.openFile("test.cpp")
    findYay(editor)
    var mark = editor.createMark()
    editor.gotoLineEnd()
    editor.insert("Hello world")
    findYay(editor)
    comparePositions(editor.position(),mark, "ensure mark stays when inserting after the mark")
    editor.close()
}

function markMoveOnPrevChar() {
    var editor = editors.openFile("test.cpp")
    findYay(editor)
    var mark = editor.createMark()
    var pos = editor.position()
    editor.gotoPreviousCharacter(3)
    editor.insert("WOW")
    findYay(editor)
    comparePositions(editor.position(),mark, "ensure mark moves on insert at prev character")
    compare(mark.line,pos.line)
    compare(mark.column, pos.column+3)
    editor.close()
}

function markStaysOnNextChar() {
    var editor = editors.openFile("test.cpp")
    findYay(editor)
    var mark = editor.createMark()
    var pos = editor.position()
    editor.insert("WOW")
    findYay(editor)
    comparePositions(editor.position(),mark, "ensure mark stays the same when inserting after point")
    compare(mark.line,pos.line)
    compare(mark.column, pos.column)
    editor.close()

}
