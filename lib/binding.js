const addon = require('../build/Release/exadrums.js-native.node')

class LibexadrumsJs 
{
    constructor(dataLocation) 
    {
        this._addonInstance = new addon.LibexadrumsJs(dataLocation)
    }

    start() { this._addonInstance.start() }
    stop()  { this._addonInstance.stop()  }
}

module.exports = LibexadrumsJs
