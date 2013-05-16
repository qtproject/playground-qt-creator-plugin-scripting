include("test.js")
//-------------------- Main --------------------

var dir = new QDir(utils.currentScripRoot);
var tests = dir.entryList([], Filter.Dirs | Filter.NoDotAndDotDot);

for (var i = 0; i < tests.length; i++) {
    runTest(tests[i])
}

if ( errorCount == 0)
    console.log("There were no errors")
else
    console.log("+++++++++ There were " + errorCount + " error(s) ++++++++++")


function runTest(name) {
    console.log("Running test " + name)
    include(name+"/" + name + ".qs")
}

