#pragma once

#include <napi.h>
#include <libexadrums/Api/eXaDrums.hpp>
#include <memory>

class LibexadrumsJs : public Napi::ObjectWrap<LibexadrumsJs>
{
public:
    LibexadrumsJs(const Napi::CallbackInfo&);
    void Start(const Napi::CallbackInfo&);
    void Stop(const Napi::CallbackInfo&);

    static Napi::Function GetClass(Napi::Env);

private:
    std::unique_ptr<eXaDrumsApi::eXaDrums> drumKit;
};
