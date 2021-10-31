const addon = require('../build/Release/exadrums.js-native.node')

class Exadrums 
{

    version = '0.1.0'

    constructor(dataLocation = '') 
    {
        if(dataLocation === '')
        {
            throw new Error('Default constructor does not exist.')
        }
        this._addonInstance = new addon.LibexadrumsJs(dataLocation)
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
    getkitsnames()              { return this._addonInstance.getKitsNames() }
    selectKit(index)            { this._addonInstance.selectKit(index) }
    saveKitConfig(index)        { this._addonInstance.saveKitConfig(index) }
    deleteKit(index)            { this._addonInstance.deleteKit(index) }
    getNumKits()                { return this._addonInstance.getNumKits() }
    reloadKits()                { this._addonInstance.reloadKits() }
    getKitDataFileName()        { return this._addonInstance.getKitDataFileName() }
    setInstrumentVolume(id, vol){ this._addonInstance.setInstrumentVolume(id, vol) }
    getInstrumentVolume(id)     { return this._addonInstance.getInstrumentVolume(id) }
    getInstrumentsNames()       { return this._addonInstance.getInstrumentsNames() }
    getInstrumentTriggersIds(id){ return this._addonInstance.getInstrumentTriggersIds(id) }

    // Triggers
    getLastTrigTime()           { return this._addonInstance.getLastTrigTime() }
    getLastTrigValue()          { return this._addonInstance.getLastTrigValue() }
    setTriggerSensorValue(id, channel, value) { this._addonInstance.setTriggerSensorValue(id, channel, value) }

    // Sensors
    getSensorsResolution()      { return this._addonInstance.getSensorsResolution() }
    isSensorVirtual()           { return this._addonInstance.isSensorVirtual() }
    isSensorSpi()               { return this._addonInstance.isSensorSpi() }

    // Audio
    getAudioDeviceName()        { return this._addonInstance.getAudioDeviceName() }

    config = 
    {
        refreshSensorsConfig: _ =>          { return this._addonInstance.refreshSensorsConfig() },
        saveSensorsConfig: _ =>             { return this._addonInstance.saveSensorsConfig() },
        saveTriggersConfig: _ =>            { return this._addonInstance.saveTriggersConfig() },
        loadTriggersConfig: _ =>            { return this._addonInstance.loadTriggersConfig() },
        getSensorsTypes: _=>                { return this._addonInstance.getSensorsTypes() },
        getTriggersTypes: _=>               { return this._addonInstance.getTriggersTypes() },
        getTriggersResponses: _=>           { return this._addonInstance.getTriggersResponses() },
        getAudioDevicesNames: _ =>          { return this._addonInstance.getAudioDevicesNames() },
        getAudioDevicesNames: _ =>          { return this._addonInstance.getAudioDevicesNames() },
        saveCurrentAudioDeviceConfig: _ =>  { return this._addonInstance.saveCurrentAudioDeviceConfig() },
        getAudioDeviceParams: _ =>          { return this._addonInstance.getAudioDeviceParams() },
        saveAudioDeviceConfig: params =>    { return this._addonInstance.saveAudioDeviceConfig(params) },
        resetAudioConfig: _ =>              { return this._addonInstance.resetAudioConfig() },
        doExport: (configDir, 
                   outputFile) =>           { return this._addonInstance.doExport(configDir, outputFile) },
        doImport: (configFile, 
                   outputConfigDir, 
                   replace) =>              { return this._addonInstance.doImport(configFile, outputConfigDir, replace) },
        getTriggersParameters: _ => 
        { 
            const triggersParams = this._addonInstance.getTriggersParameters()
            return [...triggersParams].map(t => new TriggersParameters(t))
        },
        addTrigger: triggerParams =>        { return this._addonInstance.addTrigger(triggerParams) },
        deleteTrigger: sensorId =>          { return this._addonInstance.deleteTrigger(sensorId) },
        getNbTriggers: _ =>                 { return this._addonInstance.getNbTriggers() },
        setSensorsSamplingRate: rate =>     { return this._addonInstance.setSensorsSamplingRate(rate) },
        setSensorsResolution: res =>        { return this._addonInstance.setSensorsResolution(res) },
        setSensorsDataFolder: folder =>        { return this._addonInstance.setSensorsDataFolder(folder) },
    }
}

class TriggersParameters
{
    constructor(input)
    {
        this.id = input.sensorId
        this.scanTime = input.scanTime
        this.threshold = input.threshold
        this.maskTime = input.maskTime
        this.gain = input.gain

        this.type = input.type
        this.response = input.response
    }
}

class AlsaParameters
{
    constructor(input)
    {
        this.capture = input.capture
        this.sampleRate = input.sampleRate
        this.nChannels = input.nChannels
        this.bufferTime = input.bufferTime
        this.periodTime = input.periodTime
        
        this.device = input.device
    }
}

module.exports = { Exadrums, TriggersParameters }
