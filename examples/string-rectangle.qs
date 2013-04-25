// This script is similar to emacs' string-rectangle.

include("rectangle-commands.js")
var text = dialogs.getText("Rectangular Insert", "String to insert")

replaceTextInRectangle(text)
