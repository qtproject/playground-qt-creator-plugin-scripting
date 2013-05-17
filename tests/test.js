var TEST_JS_LOADED // Purposfully left undefined - this is to avoid the global variables being loaded more than once
if (TEST_JS_LOADED == undefined) {
    TEST_JS_LOADED = true

    // Set to true to print out every single comparison
    var verbose = false

    // Set to true to "break" on the first error
    var haltOnError = false

    var errorCount = 0

    function error(message) {
        console.log("+++ " + message)
        printBackTrace()
        errorCount++
        if ( haltOnError )
            throw "error"
    }

    function printBackTrace() {
        var bt = utils.backtrace()
        // We start at 3, so we don't show backtrakce(), printBackTrace() and error()
        for ( var i=3;i<bt.length;i++) {
            console.log("\t" + bt[i])
        }
    }

    function logCompare(act,exp,message) {
        if ( verbose ) {
            if ( message != undefined )
                console.log("comparing(" + message + ") " + act + " with " + exp)
            else
                console.log("comparing " + act + " with " + exp)
        }
    }

    function failCompare(act,exp,message) {
        if ( message != undefined )
            error("Compare failed (" + message +"): actual=" + act + " expected=" + exp)
        else
            error("Compare failed: actual=" + act + " expected=" + exp)
    }

    function compareArrays(act, exp, message) {
        logCompare(act,exp,message)
        if (act.length != exp.length)
            failCompare(act,exp,message)
        else {
            for (var i=0; i<act.length; ++i) {
                if (act[i] != exp[i]) {
                    failCompare(act,exp,message)
                    break
                }
            }
        }
    }

    function compare(act, exp, message) {
        logCompare(act,exp,message)
        if (act != exp)
            failCompare(act,exp,message)
    }

    function comparePositions(act, exp, message) {
        compare(act.line, exp.line, message)
        compare(act.column, exp.column, message)
    }

    function verifyPosition(line,column, message) {
        compare(editor.currentLine, line, message)
        compare(editor.currentColumn, column, message)
    }

    function assert(cond, message) {
        if ( verbose ) {
            if ( message != undefined )
                console.log("assert(" + message + "): " + cond)
            else
                console.log("assert: " + cond)
        }
        if ( !cond ) {
            if ( message != undefined )
                error("Assertion failed: " + message)
            else
                error("Assertion failed")
        }
    }
}
