include("../test.js")

var absolute = new QFileInfo(utils.currentScripRoot + "/test.cpp")
var relative = new QFileInfo("relative")

compare(absolute.exists, true)
compare(relative.exists, false)

compare(relative.filePath, "relative")
assert(endsWith(absolute.filePath, "test.cpp"), "filePath for absolute files")

assert(startsWith(relative.absoluteFilePath,"/"))
compare(absolute.fileName, "test.cpp")

compare(absolute.isRelative, false)
compare(relative.isRelative, true)
compare(absolute.size, 61)

assert(absolute.created.getFullYear() > 2012)

var gotIt = false
try {
    new QFileInfo()
}
catch(message) {
    gotIt = true
}
assert(gotIt, "We should throw an error when constructing a QFileInfo without a file")

function endsWith(str,pattern) {
    return str.substr(str.length-pattern.length,pattern.length) == pattern
}

function startsWith(str,pattern) {
    return str.substr(0,pattern.length) == pattern
}
