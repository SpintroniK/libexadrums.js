const addon = require('../build/Release/exadrums.js-native.node')

class LibexadrumsJs 
{
    constructor(dataLocation) 
    {
        this._addonInstance = new addon.LibexadrumsJs(dataLocation)
        this.version = '0.1.0'
    }

    // Module
    start()                     { this._addonInstance.start() }
    stop()                      { this._addonInstance.stop()  }
    isStarted()                 { return this._addonInstance.isStarted() }
    getDataLocation()           { return this._addonInstance.getDataLocation() }
    getVersion()                { return this._addonInstance.getVersion() }
    enableRecording(enable)     { this._addonInstance.enableRecording(enable) }
    recorderExport(fineName)    { this._addonInstance.recorderExport(fineName) }
    recorderExportPCM(fineName) { this._addonInstance.recorderExportPCM(fineName) }
    recorderPurgeTempFile()     { this._addonInstance.recorderPurgeTempFile() }

    // Metronome
    enableMetronome(isEnable)   { this._addonInstance.enableMetronome(isEnable) }
    restartMetronome()          { this._addonInstance.restartMetronome() }
    changeTempo(tempo)          { this._addonInstance.changeTempo(tempo) }
    changeClickVolume(volume)   { this._addonInstance.changeClickVolume(volume) }
    getTempo()                  { return this._addonInstance.getTempo() }
    saveMetronomeConfig()       { this._addonInstance.saveMetronomeConfig() }
    getClickPosition()          { return this._addonInstance.getClickPosition() }
    getLastClickTime()          { return this._addonInstance.getLastClickTime() }
    getClicksTypes()            { return this._addonInstance.getClicksTypes() }
    setClickType(index)         { this._addonInstance.setClickType(index) }
    getClickTypeId()            { return this._addonInstance.getClickTypeId() }
    getRhythms()                { return this._addonInstance.getRhythms() }
    getRhythm()                 { return this._addonInstance.getRhythm() }
    setRhythm(rhythm)           { this._addonInstance.setRhythm(rhythm) }
    getBpms()                   { return this._addonInstance.getBpms() }
    getBpmeas()                 { return this._addonInstance.getBpmeas() }
    setBpmeas(bpmeas)           { this._addonInstance.setBpmeas(bpmeas) }

    // Kits
    getkitsnames()  { return this._addonInstance.getKitsNames() }
}

module.exports = LibexadrumsJs
