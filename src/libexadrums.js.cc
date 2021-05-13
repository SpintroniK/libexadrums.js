
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
        LibexadrumsJs::InstanceMethod("getKitsNames", &LibexadrumsJs::GetKitsNames),
    });
}

Object Init(Env env, Object exports) 
{
    String name = String::New(env, "LibexadrumsJs");
    exports.Set(name, LibexadrumsJs::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
