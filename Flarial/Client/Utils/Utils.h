#pragma once
#include <type_traits>
#include <functional>
#include <Windows.h>
#include <string>
#include <vector>
#include <map>

class Utils {
public:
	template <unsigned int IIdx, typename TRet, typename... TArgs>
	static inline auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
		using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
	};
};