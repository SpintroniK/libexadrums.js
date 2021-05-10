const LibexadrumsJs = require("../lib/binding.js")
const assert = require("assert")
const path = require('path')
const os = require('os')

assert(LibexadrumsJs, "The expected module is undefined")

const sleep = ms =>new Promise(resolve => setTimeout(resolve, ms))
function resolveHome(filepath) 
{
    if (filepath[0] === '~') 
    {
        return path.join(os.homedir(), filepath.slice(1));
    }
    return filepath;
}


async function testBasic()
{
    const instance = new LibexadrumsJs(resolveHome('~/.eXaDrums/Data/'))

    assert(instance.start, "The expected method is not defined")
    instance.start()
    await sleep(4000)
    instance.stop()

}

function testInvalidParams()
{
    const instance = new LibexadrumsJs()
}

(async _=>
{
    await assert.doesNotReject(testBasic, undefined, "testBasic threw an expection")
    assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw")

    console.log("Tests passed- everything looks OK!")
})()
