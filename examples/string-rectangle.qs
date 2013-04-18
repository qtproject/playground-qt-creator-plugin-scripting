// This script is similar to emacs' string-rectangle.
// As an example, select three lines of "var" below, run the script,
// and type "Variable", and see how the "var"'s are replaced with "Variable"

var text = dialogs.getText("Rectangular Insert", "String to insert")
var editor = editors.current()

var anchorPos = editor.position(PositionOperation.Anchor)
var anchorColumn = editor.convertPosition(anchorPos).x
var anchorLine = editor.convertPosition(anchorPos).y

var pointPos = editor.position(PositionOperation.Current)
var pointColumn = editor.convertPosition(pointPos).x
var pointLine = editor.convertPosition(pointPos).y

var startColumn, endColumn, startLine, endLine
if ( anchorLine < pointLine || (anchorLine == pointLine && anchorColumn < pointColumn)) {
    startColumn = anchorColumn
    endColumn = pointColumn
    startLine = anchorLine
    endLine = pointLine
}
else {
    startColumn = pointColumn
    endColumn = anchorColumn
    startLine = pointLine
    endLine = anchorLine
}

if ( startLine != -1 || startColumn != -1) {
    var line = startLine
    while ( line <= endLine ) {
        editor.gotoLine(line,startColumn)
        editor.replace(endColumn-startColumn, text)
        line = line +1
    }
}
