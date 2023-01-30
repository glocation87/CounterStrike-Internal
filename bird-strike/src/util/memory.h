#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>
#include <cstdint>
#include <functional>

namespace Memory
{
	template<typename T, typename R> inline T Read(R address) noexcept {
		return *(reinterpret_cast<T*>(address));
	}

	template<typename T, typename R> inline T Write(R address, T value) noexcept {
		T* pointer;
		pointer = reinterpret_cast<T*>(address);
		*pointer = value;
		return *pointer;

	 }
	
	template<typename T, typename ... T_args> constexpr T CallVirtual(void* vtable, const std::uint32_t index, T_args ... args) noexcept
	{
		using prototype = T(__thiscall*)(void*, decltype(args)...);
		return (Read<prototype*, void*>(vtable))[index](vtable, args...);
	}

	inline std::uintptr_t ToAbsolute(std::uintptr_t relAddr) noexcept {
		return static_cast<std::uintptr_t>(relAddr + 4 + *reinterpret_cast<std::int32_t*>(relAddr));
	}

	inline std::uint8_t* keyValuesFromString = nullptr;
}
