const LibexadrumsJs = require("../lib/binding.js")
const assert = require("assert")
const path = require('path')
const axios = require('axios')
const anzip = require('anzip')
const fs = require('fs').promises
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


const gitRepo = 'https://github.com/SpintroniK/exadrums-data/archive/refs/heads/master.zip'
const dataLocation = resolveHome('./Data')

async function testInit()
{

    const instance = new LibexadrumsJs(dataLocation)

    assert(instance.start, "The expected method is not defined.")
    assert(instance.stop, "The expected method is not defined.")
    assert(instance.isStarted, "The expected method is not defined.")
    assert(instance.getDataLocation, "The expected method is not defined.")
    assert(instance.getVersion, "The expected method is not defined.")

    console.log(`libexadrums version = ${instance.getVersion()}`)

    assert.strictEqual(instance.getDataLocation(), `${dataLocation}/`, "Data Location is wrong.")
}

async function testModule()
{
    const instance = new LibexadrumsJs(dataLocation)

    assert.strictEqual(instance.isStarted(), false, "isStarted should return false.")
    assert.doesNotThrow(_ => instance.start(), undefined, "Error: Start function should not throw.")
    assert.strictEqual(instance.isStarted(), true, "isStarted should return true.")
    assert.doesNotThrow(_ => instance.enableRecording(true), undefined, "enableRecording should not throw.")

    await sleep(3000)

    assert.doesNotThrow(_ => instance.enableRecording(false), undefined, "enableRecording should not throw.")
    assert.doesNotThrow(_ => instance.recorderExport('./test.xml', undefined, "recorderExport should not throw."))
    assert.doesNotThrow(_ => instance.recorderExportPCM('./test.wav', undefined, "recorderExportPCM should not throw."))
    assert.doesNotThrow(_ => instance.recorderPurgeTempFile(), undefined, "recorderPurgeTempFile should not throw.")
    assert.doesNotThrow(_ => instance.stop(), undefined, "Error: Start function should not throw.")
}

async function testMetronome()
{

    const instance = new LibexadrumsJs(dataLocation)

    assert(instance.enableMetronome, "The expected method is not defined.")
    assert(instance.changeClickVolume, "The expected method is not defined.")

    assert.doesNotThrow(_ => instance.setClickType(1), undefined, "setClickType should not throw.")
    assert.strictEqual(instance.getClickTypeId(), 1, "Click type index is wrong.")
    assert.doesNotThrow(_ => instance.start(), undefined, "Error: Start function should not throw.")
    assert.doesNotThrow(_ => instance.changeTempo(60), undefined, "changeTempo should not throw.")

    assert.strictEqual(instance.getClicksTypes().includes('Sine'), true, "Sine should be returned by getClicksTypes.")
    assert.strictEqual(4 in instance.getBpms(), true, "getBpms should contain the value 4.")
    assert.doesNotThrow(_ => instance.setBpmeas(3), undefined, "setBpmeas should not throw.")
    assert.strictEqual(instance.getBpmeas(), 3, "getBpmeas should return 3.")

    assert.doesNotThrow(_ => instance.enableMetronome(true), undefined, "enableMetronome should not throw.")
    assert.doesNotThrow(_ => instance.changeClickVolume(15), undefined, "changeClickVolume should not throw.")

    const lastClickTime = instance.getLastClickTime()
    
    await sleep(2000) // Let the module run for a short while

    assert.strictEqual(instance.getClickPosition() >= 0., true, "Click position is wrong.")
    assert.strictEqual(instance.getLastClickTime() > lastClickTime, true, "Last click time value is wrong.")
    assert.doesNotThrow(_ => instance.enableMetronome(false), undefined, "enableMetronome should not throw.")
    assert.doesNotThrow(_ => instance.changeTempo(120), undefined, "changeTempo should not throw.")
    assert.strictEqual(instance.getTempo(), 120, "getTempo() should return 120.")
    assert.doesNotThrow(_ => instance.getRhythms(), undefined, "getRhythms should not throw.")
    assert.strictEqual(instance.getRhythms().length > 0, true, "getRhythms did not return a correct value.")

    assert.doesNotThrow(_ => instance.setRhythm(1), undefined, "setRhythm should not throw.")
    assert.strictEqual(instance.getRhythm(), 1, "getRhythm should return 1.")

    assert.doesNotThrow(_ => instance.saveMetronomeConfig(), undefined, "saveMetronomeConfig should not thow.")

    assert.doesNotThrow(_ => instance.restartMetronome(), undefined, "restartMetronome should not throw.")
    await sleep(2000) // Let the module run for a short while

    assert.doesNotThrow(_ => instance.stop(), undefined, "Error: Stop function should not throw.")
    assert.strictEqual(instance.isStarted(), false, "isStarted should return false.")

}

function testInvalidParams()
{
    const instance = new LibexadrumsJs()
}

(async _=>
{
    let dataFolderExists = false
    try
    {
        dataFolderExists = (await fs.stat(dataLocation)).isDirectory()
    }
    catch(_)
    {
        //
    }

    if(!dataFolderExists)
    {
        console.log('Data folder not found. Downloading from Github repo...')
        const res = await axios.get(gitRepo, { responseType: 'arraybuffer' })
        await fs.writeFile('data.zip', res.data)

        console.log('Extracting data folder...')
        await anzip('data.zip', { outputPath: './', outputContent: false });
        await fs.rename('exadrums-data-master', dataLocation)
    }

    console.log('Launching tests...')

    assert.doesNotThrow(testInit, undefined, "Initialization failed.")
    await assert.doesNotReject(testModule, undefined, "Module test failed.")
    await assert.doesNotReject(testMetronome, undefined, "Metronome test failed.")
    assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw.")

    console.log("Tests passed - everything looks OK!")
})()
