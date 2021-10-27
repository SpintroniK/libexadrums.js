
#include "libexadrums.js.h"

using namespace Napi;


Function LibexadrumsJs::GetClass(Napi::Env env) 
{
    return DefineClass(env, "LibexadrumsJs", 
    {
        LibexadrumsJs::InstanceMethod("start", &LibexadrumsJs::Start),
        LibexadrumsJs::InstanceMethod("stop", &LibexadrumsJs::Stop),
        LibexadrumsJs::InstanceMethod("isStarted", &LibexadrumsJs::IsStarted),
        LibexadrumsJs::InstanceMethod("getDataLocation", &LibexadrumsJs::GetDataLocation),
        LibexadrumsJs::InstanceMethod("getVersion", &LibexadrumsJs::GetVersion),
        LibexadrumsJs::InstanceMethod("enableMetronome", &LibexadrumsJs::EnableMetronome),
        LibexadrumsJs::InstanceMethod("restartMetronome", &LibexadrumsJs::RestartMetronome),
        LibexadrumsJs::InstanceMethod("changeTempo", &LibexadrumsJs::ChangeTempo),
        LibexadrumsJs::InstanceMethod("changeClickVolume", &LibexadrumsJs::ChangeClickVolume),
        LibexadrumsJs::InstanceMethod("getTempo", &LibexadrumsJs::GetTempo),
        LibexadrumsJs::InstanceMethod("saveMetronomeConfig", &LibexadrumsJs::SaveMetronomeConfig),
        LibexadrumsJs::InstanceMethod("getClickPosition", &LibexadrumsJs::GetClickPosition),
        LibexadrumsJs::InstanceMethod("getLastClickTime", &LibexadrumsJs::GetLastClickTime),
        LibexadrumsJs::InstanceMethod("getClicksTypes", &LibexadrumsJs::GetClicksTypes),
        LibexadrumsJs::InstanceMethod("setClickType", &LibexadrumsJs::SetClickType),
        LibexadrumsJs::InstanceMethod("getClickTypeId", &LibexadrumsJs::GetClickTypeId),
        LibexadrumsJs::InstanceMethod("getRhythms", &LibexadrumsJs::GetRhythms),
        LibexadrumsJs::InstanceMethod("getRhythm", &LibexadrumsJs::GetRhythm),
        LibexadrumsJs::InstanceMethod("setRhythm", &LibexadrumsJs::SetRhythm),
        LibexadrumsJs::InstanceMethod("getBpms", &LibexadrumsJs::GetBpms),
        LibexadrumsJs::InstanceMethod("getBpmeas", &LibexadrumsJs::GetBpmeas),
        LibexadrumsJs::InstanceMethod("setBpmeas", &LibexadrumsJs::SetBpmeas),
        LibexadrumsJs::InstanceMethod("enableRecording", &LibexadrumsJs::EnableRecording),
        LibexadrumsJs::InstanceMethod("recorderExport", &LibexadrumsJs::RecorderExport),
        LibexadrumsJs::InstanceMethod("recorderExportPCM", &LibexadrumsJs::RecorderExportPCM),
        LibexadrumsJs::InstanceMethod("recorderPurgeTempFile", &LibexadrumsJs::RecorderPurgeTempFile),
        LibexadrumsJs::InstanceMethod("getSensorsResolution", &LibexadrumsJs::GetSensorsResolution),
        LibexadrumsJs::InstanceMethod("isSensorVirtual", &LibexadrumsJs::IsSensorVirtual),
        LibexadrumsJs::InstanceMethod("isSensorSpi", &LibexadrumsJs::IsSensorSpi),
        LibexadrumsJs::InstanceMethod("getAudioDeviceName", &LibexadrumsJs::GetAudioDeviceName),
        LibexadrumsJs::InstanceMethod("getKitsNames", &LibexadrumsJs::GetKitsNames),
        LibexadrumsJs::InstanceMethod("selectKit", &LibexadrumsJs::SelectKit),
        LibexadrumsJs::InstanceMethod("saveKitConfig", &LibexadrumsJs::SaveKitConfig),
        LibexadrumsJs::InstanceMethod("deleteKit", &LibexadrumsJs::DeleteKit),
        LibexadrumsJs::InstanceMethod("getNumKits", &LibexadrumsJs::GetNumKits),
        LibexadrumsJs::InstanceMethod("reloadKits", &LibexadrumsJs::ReloadKits),
        LibexadrumsJs::InstanceMethod("getKitDataFileName", &LibexadrumsJs::GetKitDataFileName),
        LibexadrumsJs::InstanceMethod("setInstrumentVolume", &LibexadrumsJs::SetInstrumentVolume),
        LibexadrumsJs::InstanceMethod("getInstrumentVolume", &LibexadrumsJs::GetInstrumentVolume),
        LibexadrumsJs::InstanceMethod("getInstrumentsNames", &LibexadrumsJs::GetInstrumentsNames),
        LibexadrumsJs::InstanceMethod("getInstrumentTriggersIds", &LibexadrumsJs::GetInstrumentTriggersIds),
        LibexadrumsJs::InstanceMethod("getLastTrigTime", &LibexadrumsJs::GetLastTrigTime),
        LibexadrumsJs::InstanceMethod("getLastTrigValue", &LibexadrumsJs::GetLastTrigValue),
        LibexadrumsJs::InstanceMethod("setTriggerSensorValue", &LibexadrumsJs::SetTriggerSensorValue),
        // CONFIG
        LibexadrumsJs::InstanceMethod("refreshSensorsConfig", &LibexadrumsJs::RefreshSensorsConfig),
        LibexadrumsJs::InstanceMethod("saveSensorsConfig", &LibexadrumsJs::SaveSensorsConfig),
        LibexadrumsJs::InstanceMethod("saveTriggersConfig", &LibexadrumsJs::SaveTriggersConfig),
        LibexadrumsJs::InstanceMethod("loadTriggersConfig", &LibexadrumsJs::LoadTriggersConfig),
        LibexadrumsJs::InstanceMethod("getSensorsTypes", &LibexadrumsJs::GetSensorsTypes),
        LibexadrumsJs::InstanceMethod("getTriggersTypes", &LibexadrumsJs::GetTriggersTypes),
        LibexadrumsJs::InstanceMethod("getTriggersResponses", &LibexadrumsJs::GetTriggersResponses),
        LibexadrumsJs::InstanceMethod("getAudioDevicesNames", &LibexadrumsJs::GetAudioDevicesNames),
        LibexadrumsJs::InstanceMethod("getTriggersParameters", &LibexadrumsJs::GetTriggersParameters),
        LibexadrumsJs::InstanceMethod("getAudioDeviceParams", &LibexadrumsJs::GetAudioDeviceParams),
        LibexadrumsJs::InstanceMethod("saveCurrentAudioDeviceConfig", &LibexadrumsJs::SaveCurrentAudioDeviceConfig),
        LibexadrumsJs::InstanceMethod("saveAudioDeviceConfig", &LibexadrumsJs::SaveAudioDeviceConfig),
        LibexadrumsJs::InstanceMethod("resetAudioDevice", &LibexadrumsJs::ResetAudioDevice),
        LibexadrumsJs::InstanceMethod("doExport", &LibexadrumsJs::ExportConfig),
        LibexadrumsJs::InstanceMethod("doImport", &LibexadrumsJs::ImportConfig),

    });
}

Object Init(Env env, Object exports) 
{
    String name = String::New(env, "LibexadrumsJs");
    exports.Set(name, LibexadrumsJs::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
