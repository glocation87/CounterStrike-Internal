#include "../util/memory.h"

class CKeyValues {
public:
	static CKeyValues* FromString(const char* name, const char* value) noexcept
	{
		static std::uintptr_t functionAddress = Memory::ToAbsolute(reinterpret_cast<std::uintptr_t>(Memory::keyValuesFromString));

		CKeyValues* kv;

		__asm
		{
			push 0
			mov edx, value			// second param goes in edx
			mov ecx, name			// first param in ecx
			call functionAddress	// call the func with ecx, edx
			add esp, 4
			mov kv, eax				// value is stored in eax, move it into kv
		}

		return kv;
	}
};
