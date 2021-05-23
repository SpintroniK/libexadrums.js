#pragma once

#include "helpers.h"

#include <libexadrums/Api/eXaDrums.hpp>
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


    static Napi::Function GetClass(Napi::Env);

private:

    std::unique_ptr<eXaDrumsApi::eXaDrums> drumKit;
};
