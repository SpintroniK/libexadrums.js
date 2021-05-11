const addon = require('../build/Release/exadrums.js-native.node')

class LibexadrumsJs 
{
    constructor(dataLocation) 
    {
        this._addonInstance = new addon.LibexadrumsJs(dataLocation)
    }

    start()             { this._addonInstance.start() }
    stop()              { this._addonInstance.stop()  }
    isStarted()         { return this._addonInstance.isStarted() }
    getDataLocation()   { return this._addonInstance.getDataLocation() }

    getkitsnames()  { return this._addonInstance.getKitsNames() }
}

module.exports = LibexadrumsJs
