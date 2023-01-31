#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>
#include <cstdint>
#include <functional>

namespace Memory
{
	void Initialize() noexcept;
	std::uint8_t* PatternScan(const char* moduleName, const char* pattern) noexcept;

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

	// get void pointer to virtual function @ given index
	constexpr void* Get(void* vmt, const std::uint32_t index) noexcept
	{
		return (*static_cast<void***>(vmt))[index];
	}

	// return addresses
	inline std::uint8_t* allocKeyValuesClient = nullptr;
	inline std::uint8_t* allocKeyValuesEngine = nullptr;
	inline std::uint8_t* insertIntoTree = nullptr;

	inline std::uint8_t* keyValuesFromString = nullptr;
}
