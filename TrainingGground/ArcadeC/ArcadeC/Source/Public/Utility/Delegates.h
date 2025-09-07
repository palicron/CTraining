#pragma once


#include <functional>
#include <optional>
#include <utility>
#include <type_traits>

template<typename Signature>
struct Delegates;

//Single Bind Delegate
template <typename R, typename... Args>
struct Delegates<R(Args...)>
{
    //Bind
  /*  void Bind(std::function<R(Args...)> func)
    {
        bind_func = func;
    }

    void Unbind()
    {
        bind_func.reset();
    }

    R Execute(Args... args) const
    {
        if (!bind_func)
        {
            throw std::bad_function_call();
        }
        return (*bind_func)(std::forward<Args>(args)...);
    }

    //@TODO check whi i cannot use std::optinal
    //bool IsBound() const { return BindFunc.has_value(); }

    std::optional<std::function<R(Args...)>> bind_func ;
   // std::function<R(Args...)> BindFunc;*/

   std::optional<float> cosa = 0.f;
};

