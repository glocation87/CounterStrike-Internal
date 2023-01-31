#pragma once
#include <intrin.h>
#include "../../externals/minhook/include/MinHook.h"
#include "../valve/iclientmode.h"
#include "../valve/ivpanel.h"
#include "../valve/isurface.h"

namespace Hooks
{
	//initialize and clean up hooks
	void Initialize() noexcept;
	void Clean() noexcept;

	//store original function pointers and create prototype signatures
	using AllocKeyValuesPrototype = void*(__thiscall*)(void*, const std::int32_t) noexcept;
	inline AllocKeyValuesPrototype AllocKeyValuesMemoryOriginal;

	using PaintTraversePrototype = void(__thiscall*)(IVPanel*, std::uintptr_t, bool, bool) noexcept;
	inline PaintTraversePrototype PaintTraverseOriginal;

	using CreateMovePrototype = bool(__thiscall*)(IClientModeShared*, float, CUserCmd*) noexcept;
	inline CreateMovePrototype CreateMoveOriginal = nullptr;
	
	namespace Hooked
	{
		void* __stdcall AllocKeyValuesMemory(const std::int32_t size) noexcept;
		void __stdcall PaintTraverse(std::uintptr_t panel, bool forceRepaint, bool allowForce) noexcept;
		bool __stdcall CreateMove(float frameTime, CUserCmd* cmd) noexcept;
	}
	
}