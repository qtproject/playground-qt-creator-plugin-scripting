include("../test.js")
testBasic()
testDirOp()
testFilter()
testCd()
testStaticFunctions()

function testBasic() {
    var usrbin = new QDir("/usr/bin")
    compare(usrbin.path,"/usr/bin")
    compare(usrbin.absolutePath,"/usr/bin")
    compare(usrbin.dirName,"bin")

    var scriptDir = new QDir(utils.currentScripRoot)
    compare(scriptDir.count, 4)
    compare(scriptDir.at(0), ".")
    compare(scriptDir.at(1), "..")
    compare(scriptDir.at(2), "qdir.qs")
    compare(scriptDir.at(3), "testcase")

    compare(usrbin.isReadable, true)
    compare(usrbin.exists(), true)

    var bogus = new QDir("/bogus")
    compare(bogus.exists(), false)

    var root = new QDir("/")
    compare(usrbin.isRoot, false)
    compare(root.isRoot, true)

    var relative = new QDir("foo")
    compare(relative.isRelative, true)
    compare(usrbin.isRelative, false)
}

function testDirOp() {
    var scriptDir = new QDir(utils.currentScripRoot)

    compare(scriptDir.exists("NEWDIR"),false)
    var ok = scriptDir.mkdir("NEWDIR")
    assert(ok)

    compare(scriptDir.exists("NEWDIR"),true)

    ok = scriptDir.rename("NEWDIR", "NEWDIR2")
    assert(ok)

    compare(scriptDir.exists("NEWDIR"),false)
    compare(scriptDir.exists("NEWDIR2"),true)

    ok = scriptDir.rmdir("NEWDIR2")
    assert(ok)

    compare(scriptDir.exists("NEWDIR2"),false)
}

function testFilter() {
    var testcase = new QDir(utils.currentScripRoot + "/testcase" )
    var files = testcase.entryList()
    compare(files.length, 5)

    var files = testcase.entryList([], Filter.Files, SortFlag.Name )
    compareArrays(files,["a","b","c"])

    files = testcase.entryList([], Filter.Dirs, SortFlag.Name )
    compareArrays(files,[".","..","x","y"])

    files = testcase.entryList([], Filter.Dirs | Filter.NoDotAndDotDot, SortFlag.Name )
    compareArrays(files,["x","y"])

    files = testcase.entryList([], Filter.Files | Filter.NoDotAndDotDot, SortFlag.Size)
    compareArrays(files, ["c","b","a"])

    files = testcase.entryList([], Filter.Files | Filter.NoDotAndDotDot, SortFlag.Size | SortFlag.Reversed)
    compareArrays(files, ["a","b","c"])

    testcase = new QDir(utils.currentScripRoot + "/testcase/x" )
    files = testcase.entryList(["*.txt"], Filter.NoFilter, SortFlag.Name )
    compareArrays(files,["abc.txt","def.txt"])

    files = testcase.entryList(["*.txt", "*.data"], Filter.NoFilter, SortFlag.Name )
    compareArrays(files,["abc.txt","def.txt","hij.data","klm.data"])
}


function testCd() {
    var dir = new QDir(utils.currentScripRoot )
    var filesHere = dir.entryList()

    dir = dir.cd("testcase")
    var files = dir.entryList([], Filter.Files, SortFlag.Name )
    compareArrays(files,["a","b","c"])

    dir = dir.cdUp()
    compareArrays(filesHere, dir.entryList())
}

function testStaticFunctions() {
    var str = QDir().toNativeSeparators("/usr/bin");
    compare(str, "/usr/bin")

    QDir().setCurrent(utils.currentScripRoot)
    compare(QDir().currentPath(), utils.currentScripRoot);
    assert(QDir().current().exists("qdir.qs"));

    compare(QDir().cleanPath("//usr/./../tmp/./bah"),"/tmp/bah")
}
