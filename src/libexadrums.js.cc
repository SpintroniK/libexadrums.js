#include "libexadrums.js.h"
#include <string>

using namespace Napi;

LibexadrumsJs::LibexadrumsJs(const Napi::CallbackInfo& info) : ObjectWrap(info)
{
    Napi::Env env = info.Env();

    if(info.Length() < 1) 
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }

    if(!info[0].IsString()) 
    {
        Napi::TypeError::New(env, "You need to name yourself").ThrowAsJavaScriptException();
        return;
    }

    const std::string dataLocation = info[0].As<Napi::String>().Utf8Value();
    this->drumKit = std::make_unique<eXaDrumsApi::eXaDrums>(dataLocation.data());
}

void LibexadrumsJs::Start(const Napi::CallbackInfo& info) 
{
    drumKit->Start();
}

void LibexadrumsJs::Stop(const Napi::CallbackInfo& info) 
{
    drumKit->Stop();
}

Napi::Function LibexadrumsJs::GetClass(Napi::Env env) 
{
    return DefineClass(env, "LibexadrumsJs", 
    {
        LibexadrumsJs::InstanceMethod("start", &LibexadrumsJs::Start),
        LibexadrumsJs::InstanceMethod("stop", &LibexadrumsJs::Stop),
    });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) 
{
    Napi::String name = Napi::String::New(env, "LibexadrumsJs");
    exports.Set(name, LibexadrumsJs::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
