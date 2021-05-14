const addon = require('../build/Release/exadrums.js-native.node')

class LibexadrumsJs 
{
    constructor(dataLocation) 
    {
        this._addonInstance = new addon.LibexadrumsJs(dataLocation)
    }

    start()                     { this._addonInstance.start() }
    stop()                      { this._addonInstance.stop()  }
    isStarted()                 { return this._addonInstance.isStarted() }
    getDataLocation()           { return this._addonInstance.getDataLocation() }
    getVersion()                { return this._addonInstance.getVersion() }
    enableMetronome(isEnable)   { this._addonInstance.enableMetronome(isEnable) }
    restartMetronome()          { this._addonInstance.restartMetronome() }
    changeTempo(tempo)          { this._addonInstance.changeTempo(tempo) }
    changeClickVolume(volume)   { this._addonInstance.changeClickVolume(volume) }
    getTempo()                  { return this._addonInstance.getTempo() }
    saveMetronomeConfig()       { this._addonInstance.saveMetronomeConfig() }
    getClickPosition()          { return this._addonInstance.getClickPosition() }
    getLastClickTime()          { return this._addonInstance.getLastClickTime() }

    getkitsnames()  { return this._addonInstance.getKitsNames() }
}

module.exports = LibexadrumsJs
