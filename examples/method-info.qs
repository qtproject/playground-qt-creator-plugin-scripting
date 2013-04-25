var fun = editors.current().currentFunction()
console.log("Name: " + fun.name)
console.log("Return Type: " + fun.returnType)
console.log("Arguments: " + fun.arguments.length)
for ( var i = 0; i <  + fun.arguments.length; i++ ) {
    var arg = fun.arguments[i]
    console.log("  Argument: name:" + arg.name + " type:" + arg.type + " initializer: " + arg.initializer)
}
console.log("isVirtual=" + fun.isVirtual + " isOverride=" + fun.isOverride
+ " isFinal=" + fun.isFinal + " isVariadic=" + fun.isVariadic + " isConst="
+ fun.isConst + " isVolatile=" + fun.isVolatile + " isPureVirtual=" +
fun.isPureVirtual)
