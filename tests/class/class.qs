include("../test.js")

var editor = editors.openFile("test.h")

noBase()
oneBaseClass()
twoBaseClasses()
struct()
union()
editor.close()

function find(str) {
    editor.gotoLine(1,0)
    editor.find(str)
}

function noBase() {
    find("// 1")
    var cls = editor.currentClass()
    compare(cls.name,"A")
    compare(cls.isClass, true)
    compare(cls.isStruct, false)
    compare(cls.isUnion, false)
    compareArrays(cls.baseClasses, [])
}

function oneBaseClass() {
    find("// 2")
    var cls = editor.currentClass()
    compare(cls.name,"B")
    compareArrays(cls.baseClasses, ["A"])
}

function twoBaseClasses() {
    find("// 3")
    var cls = editor.currentClass()
    compare(cls.name,"D")
    compareArrays(cls.baseClasses, ["X", "Y"])
}

function struct() {
    find("// 4")
    var cls = editor.currentClass()
    compare(cls.name,"E")
    compare(cls.isClass, false)
    compare(cls.isStruct, true)
    compare(cls.isUnion, false)
    compareArrays(cls.baseClasses, [])

}

function union() {
    find("// 5")
    var cls = editor.currentClass()
    compare(cls.name,"F")
    compare(cls.isClass, false)
    compare(cls.isStruct, false)
    compare(cls.isUnion, true)
    compareArrays(cls.baseClasses, [])

}
