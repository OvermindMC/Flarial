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

template<typename T>
class Vec2 {
public:
	T x, y;
public:
	Vec2(T x = 0, T y = 0) {
		this->x = x;
		this->y = y;
	};
};

template<typename T>
class Vec3 : public Vec2<T> {
public:
	T z;
public:
	Vec3(T x = 0, T y = 0, T z = 0) : Vec2<T>(x, y) {
		this->z = z;
	};
};