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
    const dataLocation = resolveHome('~/.eXaDrums/Data')
    const instance = new LibexadrumsJs(dataLocation)

    // Make sure all required methods exist
    assert(instance.start, "The expected method is not defined.")
    assert(instance.stop, "The expected method is not defined.")
    assert(instance.isStarted, "The expected method is not defined.")
    assert(instance.getDataLocation, "The expected method is not defined.")
    assert(instance.getVersion, "The expected method is not defined.")
    assert(instance.enableMetronome, "The expected method is not defined.")
    assert(instance.changeClickVolume, "The expected method is not defined.")
    
    // console.log(`libexadrums version = ${instance.getVersion()}`)

    assert.strictEqual(instance.getDataLocation(), `${dataLocation}/`, "Data Location is wrong.")

    assert.strictEqual(instance.isStarted(), false, "isStarted should return false.")
    assert.doesNotThrow(_ => instance.start(), undefined, "Error: Start function should not throw.")
    assert.strictEqual(instance.isStarted(), true, "isStarted should return true.")

    assert.doesNotThrow(_ => instance.enableMetronome(true), undefined, "enableMetronome should not throw.")
    assert.doesNotThrow(_ => instance.changeClickVolume(15), undefined, "changeClickVolume should not throw.")
    
    await sleep(1000) // Let the module run for a short while
    assert.doesNotThrow(_ => instance.enableMetronome(false), undefined, "enableMetronome should not throw.")
    await sleep(3000) // Let the module run for a short while

    assert.doesNotThrow(_ => instance.stop(), undefined, "Error: Stop function should not throw.")
    assert.strictEqual(instance.isStarted(), false, "isStarted should return false.")

}

function testInvalidParams()
{
    const instance = new LibexadrumsJs()
}

(async _=>
{
    await assert.doesNotReject(testBasic, undefined, "testBasic threw an expection")
    assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw")

    console.log("Tests passed - everything looks OK!")
})()
