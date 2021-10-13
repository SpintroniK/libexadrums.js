#pragma once

#include "helpers.h"

#include <libexadrums/Api/eXaDrums.hpp>
#include <libexadrums/Api/Config/Config_api.hpp>
#include <napi.h>
#include <memory>

class LibexadrumsJs : public Napi::ObjectWrap<LibexadrumsJs>
{

public:

    LibexadrumsJs(const Napi::CallbackInfo& info) : ObjectWrap(info)
    {
        std::string dataLocation{};
        getArgs(info, dataLocation);

        this->drumKit = std::make_unique<eXaDrumsApi::eXaDrums>(dataLocation.data());
        this->config = std::make_unique<eXaDrumsApi::Config>(*this->drumKit.get());
    }


    // MODULE

    void Start(const Napi::CallbackInfo& info) 
    {
        drumKit->Start();
    }

    void Stop(const Napi::CallbackInfo& info) 
    {
        drumKit->Stop();
    }

    Napi::Value IsStarted(const Napi::CallbackInfo& info)
    {
        bool isStarted = drumKit->IsStarted();
        return Napi::Value::From(info.Env(), isStarted);
    }

    Napi::Value GetDataLocation(const Napi::CallbackInfo& info)
    {
        return Napi::String::From(info.Env(), drumKit->GetDataLocation());
    }
    
    Napi::Value GetVersion(const Napi::CallbackInfo& info)
    {
        return Napi::String::From(info.Env(), eXaDrumsApi::eXaDrums::GetVersion());
    }

    void EnableRecording(const Napi::CallbackInfo& info)
    {
        bool enable{};
        getArgs(info, enable);
        drumKit->EnableRecording(enable);
    }

    void RecorderExport(const Napi::CallbackInfo& info)
    {
        std::string fileName{};
        getArgs(info, fileName);
        drumKit->RecorderExport(fileName);
    }

    void RecorderExportPCM(const Napi::CallbackInfo& info)
    {
        std::string fileName{};
        getArgs(info, fileName);
        drumKit->RecorderExportPCM(fileName);
    }

    void RecorderPurgeTempFile(const Napi::CallbackInfo& info)
    {
        drumKit->RecorderPurgeTempFile();
    }


    // METRONOME

    void EnableMetronome(const Napi::CallbackInfo& info)
    {
        bool enabled{};
        getArgs(info, enabled);
        drumKit->EnableMetronome(enabled);
    }

    void RestartMetronome(const Napi::CallbackInfo& info)
    {
        drumKit->RestartMetronome();
    }

    void ChangeTempo(const Napi::CallbackInfo& info)
    {
        uint32_t tempo{};
        getArgs(info, tempo);
        drumKit->ChangeTempo(tempo);
    }

    void ChangeClickVolume(const Napi::CallbackInfo& info)
    {
        uint32_t volume{};
        getArgs(info, volume);
        
        drumKit->ChangeClickVolume(volume);
    }

    Napi::Value GetTempo(const Napi::CallbackInfo& info)
    {
        uint32_t tempo = drumKit->GetTempo();
        return Napi::Number::From(info.Env(), tempo);
    }

    void SaveMetronomeConfig(const Napi::CallbackInfo& info)
    {
        drumKit->SaveMetronomeConfig();
    }
    
    Napi::Value GetClickPosition(const Napi::CallbackInfo& info)
    {
        double clickPos = drumKit->GetClickPosition();
        return Napi::Number::From(info.Env(), clickPos);
    }

    Napi::Value GetLastClickTime(const Napi::CallbackInfo& info)
    {
        int64_t lastClickTime = drumKit->GetLastClickTime();
        return Napi::Number::From(info.Env(), lastClickTime);
    }

    Napi::Value GetClicksTypes(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, drumKit->GetClicksTypes());
    }

    void SetClickType(const Napi::CallbackInfo& info)
    {
        uint32_t clickTypeIndex{};
        getArgs(info, clickTypeIndex);
        drumKit->SetClickType(clickTypeIndex); 
    }

    Napi::Value GetClickTypeId(const Napi::CallbackInfo& info)
    {
        uint32_t clickTypeIndex = drumKit->GetClickTypeId();
        return Napi::Number::From(info.Env(), clickTypeIndex);
    }

    Napi::Value GetRhythms(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, drumKit->GetRhythms());
    }

    Napi::Value GetRhythm(const Napi::CallbackInfo& info)
    {
        uint32_t currentRythm = drumKit->GetRhythm();
        return Napi::Number::From(info.Env(), currentRythm);
    }

    void SetRhythm(const Napi::CallbackInfo& info)
    {
        uint32_t rythmIndex{};
        getArgs(info, rythmIndex);
        drumKit->SetRhythm(rythmIndex);
    }

    Napi::Value GetBpms(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, drumKit->GetBpms());
    }

    Napi::Value GetBpmeas(const Napi::CallbackInfo& info)
    {
        return Napi::Number::From(info.Env(), drumKit->GetBpmeas());
    }

    void SetBpmeas(const Napi::CallbackInfo& info)
    {
        uint32_t bpmeas{};
        getArgs(info, bpmeas);
        drumKit->SetBpmeas(bpmeas);
    }


    // KIT

    Napi::Value GetKitsNames(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, drumKit->GetKitsNames());
    }

    void SelectKit(const Napi::CallbackInfo& info)
    {
        uint32_t index{};
        getArgs(info, index);
        drumKit->SelectKit(index);
    }

    void SaveKitConfig(const Napi::CallbackInfo& info)
    {
        uint32_t index{};
        getArgs(info, index);
        drumKit->SaveKitConfig(index);
    }

    void DeleteKit(const Napi::CallbackInfo& info)
    {
        uint32_t index{};
        getArgs(info, index);
        drumKit->DeleteKit(index);
    }

    void ReloadKits(const Napi::CallbackInfo& info)
    {
        drumKit->ReloadKits();
    }

    Napi::Value GetNumKits(const Napi::CallbackInfo& info)
    {
        return Napi::Number::From(info.Env(), drumKit->GetNumKits());
    }

    Napi::Value GetKitDataFileName(const Napi::CallbackInfo& info)
    {
        return native2Value(info, drumKit->GetKitDataFileName());
    }

    void SetInstrumentVolume(const Napi::CallbackInfo& info)
    {
        uint32_t id{};
        uint32_t volume{};
        getArgs(info, id, volume);

        drumKit->SetInstrumentVolume(id, volume);
    }

    Napi::Value GetInstrumentVolume(const Napi::CallbackInfo& info)
    {
        uint32_t id{};
        getArgs(info, id);
        return native2Value(info, drumKit->GetInstrumentVolume(id));
    }

    Napi::Value GetInstrumentsNames(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, drumKit->GetInstrumentsNames());
    }

    Napi::Value GetInstrumentTriggersIds(const Napi::CallbackInfo& info)
    {
        uint32_t instrumentId{};
        getArgs(info, instrumentId);

        return vector2Array(info, drumKit->GetInstrumentTriggersIds(instrumentId));
    }

    void SetTriggerSensorValue(const Napi::CallbackInfo& info)
    {
        uint32_t id{};
        uint32_t channel{};
        int32_t data{};
        getArgs(info, id, channel, data);
        drumKit->SetTriggerSensorValue(id, channel, data); 
    }

    // TRIGGERS

    Napi::Value GetLastTrigTime(const Napi::CallbackInfo& info)
    {
        return native2Value(info, drumKit->GetLastTrigTime());
    }

    Napi::Value GetLastTrigValue(const Napi::CallbackInfo& info)
    {
        return native2Value(info, drumKit->GetLastTrigValue());
    }

    // SENSORS

    Napi::Value GetSensorsResolution(const Napi::CallbackInfo& info)
    {
        return Napi::Number::From(info.Env(), drumKit->GetSensorsResolution());
    }

    Napi::Value IsSensorVirtual(const Napi::CallbackInfo& info)
    {
        return Napi::Boolean::From(info.Env(), drumKit->IsSensorVirtual());
    }

    Napi::Value IsSensorSpi(const Napi::CallbackInfo& info)
    {
        return Napi::Boolean::From(info.Env(), drumKit->IsSensorSpi());
    }

    // AUDIO

    Napi::Value GetAudioDeviceName(const Napi::CallbackInfo& info)
    {
        return Napi::String::From(info.Env(), drumKit->GetAudioDeviceName());
    }

    // CONFIG

    // SENSORS

    void RefreshSensorsConfig(const Napi::CallbackInfo& info)
    {
        return config->RefreshSensorsConfig();
    }

    void SaveSensorsConfig(const Napi::CallbackInfo& info)
    {
        return config->SaveSensorsConfig();
    }

    Napi::Value GetSensorsTypes(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, config->GetSensorsTypes());
    }

    Napi::Value GetTriggersTypes(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, config->GetTriggersTypes());
    }

    Napi::Value GetTriggersResponses(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, config->GetTriggersResponses());
    }

    Napi::Value GetAudioDevicesNames(const Napi::CallbackInfo& info)
    {
        return vector2Array(info, config->GetAudioDevicesNames());
    }

    // TRIGGERS

    Napi::Value GetTriggersParameters(const Napi::CallbackInfo& info)
    {
        const auto triggersParameters = config->GetTriggersParameters();
        auto out = Napi::Array::New(info.Env(), triggersParameters.size());

        for(size_t i = 0; i < triggersParameters.size(); ++i)
        {
            auto obj = Napi::Object::New(info.Env());

            obj["sensorId"] = triggersParameters[i].sensorId;
            obj["scanTime"] = triggersParameters[i].scanTime;
            obj["threshold"] = triggersParameters[i].threshold;
            obj["maskTime"] = triggersParameters[i].maskTime;
            obj["gain"] = triggersParameters[i].gain;
            obj["type"] = Napi::String::From(info.Env(), triggersParameters[i].type);
            obj["response"] = Napi::String::From(info.Env(), triggersParameters[i].response);

            out[i] = obj;
        }

        return out;
    }

    // AUDIO
    
    Napi::Value GetAudioDeviceParams(const Napi::CallbackInfo& info)
    {
        const auto alsaParameters = config->GetAudioDeviceParams();
        auto obj = Napi::Object::New(info.Env());

        obj["capture"] = alsaParameters.capture;
        obj["sampleRate"] = alsaParameters.sampleRate;
        obj["nChannels"] = alsaParameters.nChannels;
        obj["bufferTime"] = alsaParameters.bufferTime;
        obj["periodTime"] = alsaParameters.periodTime;

        obj["device"] = alsaParameters.device;

        return obj;
    }


    static Napi::Function GetClass(Napi::Env);

private:

    std::unique_ptr<eXaDrumsApi::eXaDrums> drumKit;
    std::unique_ptr<eXaDrumsApi::Config> config;
};
