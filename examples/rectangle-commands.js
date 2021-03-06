var editor = editors.current()

var anchorPos = editor.position(PositionOperation.Anchor)
var anchorColumn = anchorPos.column
var anchorLine = anchorPos.line

var pointPos = editor.position(PositionOperation.Current)
var pointColumn = pointPos.column
var pointLine = pointPos.line

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


function replaceTextInRectangle(text) {
    if ( startLine != -1 || startColumn != -1) {
        var line = startLine
        while ( line <= endLine ) {
            editor.gotoLine(line,startColumn)
            editor.replace(endColumn-startColumn, text)
            line = line +1
        }
    }
}

function spaces(count) {
    var result = ""
    for (var i=0; i < count; i++) {
        result = result + " "
    }
    return result
}

function openRectangle() {
    if ( startLine != -1 || startColumn != -1) {
        var line = startLine
        while ( line <= endLine ) {
            editor.gotoLine(line,startColumn)
            editor.replace(0, spaces(endColumn-startColumn))
            line = line +1
        }

    }
}
