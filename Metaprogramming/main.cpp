
#include <iostream>

struct FDefaultDelegateUserPolicy{}; 

template<typename DelegateSignature, typename UserPolicy = FDefaultDelegateUserPolicy>
struct TDelegate{};


template<typename InReturnValType, typename... ParamTypes>
struct TDelegate<InReturnValType(ParamTypes...)>
{
  using RetValType                = InReturnValType;
  using FuncType                  = InReturnValType(ParamTypes...);
};

