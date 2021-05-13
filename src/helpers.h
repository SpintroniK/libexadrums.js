#pragma once

#include <napi.h>
#include <string>
#include <type_traits>


template<class T>
void checkArgType(const Napi::CallbackInfo& info, size_t index, T& arg)
{
    const auto& currentArg = info[index];
    index++;

    using ArgType = std::remove_reference_t<decltype(arg)>;

    if constexpr(std::is_same_v<ArgType, std::string>)
    {
        if(currentArg.IsString())
        {
            arg = currentArg.As<Napi::String>().Utf8Value();
            return;
        }
    }

    if constexpr(std::is_same_v<ArgType, bool>)
    {
        if(currentArg.IsBoolean())
        {
            arg = currentArg.As<Napi::Boolean>().Value();
            return;
        }
    }

    if constexpr(std::is_same_v<ArgType, uint32_t> || std::is_same_v<ArgType, int>)
    {
        if(currentArg.IsNumber())
        {
            arg = static_cast<ArgType>(currentArg.As<Napi::Number>());
            return;
        }
    }

    Napi::TypeError::New(info.Env(), "Wrong argument type").ThrowAsJavaScriptException();
}


template<class ...T>
void getArgs(const Napi::CallbackInfo& info, T&... args)
{
    constexpr std::size_t n = sizeof...(T);

    if(info.Length() < n)
    {
        Napi::TypeError::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
       
    size_t index = 0;
    (checkArgType(info, index, args), ...);
}