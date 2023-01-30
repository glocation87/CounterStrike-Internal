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
		return Read<prototype*, void*>(vtable)[index](vtable, args);
	}

	

	void Initialize() noexcept;
	//func signatures

}
