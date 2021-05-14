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

    Napi::Value GetKitsNames(const Napi::CallbackInfo& info)
    {
        Napi::Env env = info.Env();
        const auto kitsNames = drumKit->GetKitsNames();
        auto kitsNamesArray = Napi::Array::New(env, kitsNames.size());
        for(size_t i = 0; i < kitsNames.size(); ++i)
        {
            kitsNamesArray[i] = Napi::String::From(env, kitsNames[i]);
        }

        return kitsNamesArray;
    }


    static Napi::Function GetClass(Napi::Env);

private:

    std::unique_ptr<eXaDrumsApi::eXaDrums> drumKit;
};
