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

    function compare(act, exp, message) {
        if ( verbose ) {
            if ( message != undefined )
                console.log("comparing(" + message + ") " + act + " with " + exp)
            else
                console.log("comparing " + act + " with " + exp)
        }
        if (act != exp) {
            if ( message != undefined )
                error("Compare failed (" + message +"): actual=" + act + " expected=" + exp)
            else
                error("Compare failed: actual=" + act + " expected=" + exp)
        }
    }

    function comparePositions(act, exp, message) {
        compare(act.line, exp.line, message)
        compare(act.column, exp.column, message)
    }

    function verifyPosition(line,column, message) {
        compare(editor.currentLine(), line, message)
        compare(editor.currentColumn(), column, message)
    }

}
