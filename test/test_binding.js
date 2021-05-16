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

async function testInit()
{

    const dataLocation = resolveHome('~/.eXaDrums/Data')
    const instance = new LibexadrumsJs(dataLocation)

    assert(instance.start, "The expected method is not defined.")
    assert(instance.stop, "The expected method is not defined.")
    assert(instance.isStarted, "The expected method is not defined.")
    assert(instance.getDataLocation, "The expected method is not defined.")
    assert(instance.getVersion, "The expected method is not defined.")

    console.log(`libexadrums version = ${instance.getVersion()}`)

    assert.strictEqual(instance.getDataLocation(), `${dataLocation}/`, "Data Location is wrong.")

    assert.strictEqual(instance.isStarted(), false, "isStarted should return false.")
    assert.doesNotThrow(_ => instance.start(), undefined, "Error: Start function should not throw.")
    assert.strictEqual(instance.isStarted(), true, "isStarted should return true.")

    assert.doesNotThrow(_ => instance.stop(), undefined, "Error: Start function should not throw.")
}

async function testMetronome()
{

    const dataLocation = resolveHome('~/.eXaDrums/Data')
    const instance = new LibexadrumsJs(dataLocation)

    assert(instance.enableMetronome, "The expected method is not defined.")
    assert(instance.changeClickVolume, "The expected method is not defined.")

    assert.doesNotThrow(_ => instance.setClickType(1), undefined, "setClickType should not throw.")
    assert.strictEqual(instance.getClickTypeId(), 1, "Click type index is wrong.")
    assert.doesNotThrow(_ => instance.start(), undefined, "Error: Start function should not throw.")
    assert.doesNotThrow(_ => instance.changeTempo(60), undefined, "changeTempo should not throw.")

    assert.strictEqual(instance.getClicksTypes().includes('Sine'), true, "Sine should be returned by getClicksTypes.")

    assert.doesNotThrow(_ => instance.enableMetronome(true), undefined, "enableMetronome should not throw.")
    assert.doesNotThrow(_ => instance.changeClickVolume(15), undefined, "changeClickVolume should not throw.")

    const lastClickTime = instance.getLastClickTime()
    
    await sleep(1000) // Let the module run for a short while

    assert.strictEqual(instance.getClickPosition() >= 0., true, "Click position is wrong.")
    assert.strictEqual(instance.getLastClickTime() > lastClickTime + 100, true, "Last click time value is wrong.")
    assert.doesNotThrow(_ => instance.enableMetronome(false), undefined, "enableMetronome should not throw.")
    assert.doesNotThrow(_ => instance.changeTempo(120), undefined, "changeTempo should not throw.")
    assert.strictEqual(instance.getTempo(), 120, "getTempo() should return 120.")
    assert.doesNotThrow(_ => instance.getRhythms(), undefined, "getRhythms should not throw.")
    assert.strictEqual(instance.getRhythms().length > 0, true, "getRhythms did not return a correct value.")

    assert.doesNotThrow(_ => instance.setRhythm(1), undefined, "setRhythm should not throw.")
    assert.strictEqual(instance.getRhythm(), 1, "getRhythm should return 1.")

    assert.doesNotThrow(_ => instance.saveMetronomeConfig(), undefined, "saveMetronomeConfig should not thow.")

    assert.doesNotThrow(_ => instance.restartMetronome(), undefined, "restartMetronome should not throw.")
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
    assert.doesNotThrow(testInit, undefined, "Initialization failed.")
    await assert.doesNotReject(testMetronome, undefined, "Metronome test failed.")
    assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw.")

    console.log("Tests passed - everything looks OK!")
})()
