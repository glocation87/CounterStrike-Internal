#include <iostream>
#include "hooks.h"
#include "../util/memory.h"
#include "../cheats/esp.h"

void Hooks::Initialize() noexcept
{
	MH_Initialize();

	// AllocKeyValuesMemory hook
	MH_CreateHook(
		Memory::Get(Interface::keyValuesSystem, 1),
		&Hooks::Hooked::AllocKeyValuesMemory,
		reinterpret_cast<void**>(&AllocKeyValuesMemoryOriginal)
	);

	// PaintTraverse hook
	MH_CreateHook(
		Memory::Get(Interface::panel, 41),
		&Hooks::Hooked::PaintTraverse,
		reinterpret_cast<void**>(&PaintTraverseOriginal)
	);
/*
	
	MH_CreateHook(
		Memory::Get(Interface::client, 24),
		&Hooks::Hooked::CreateMove,
		reinterpret_cast<void**>(&CreateMoveOriginal)
	);
	*/
	MH_EnableHook(MH_ALL_HOOKS);
}

void Hooks::Clean() noexcept
{

	// restore hooks
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);

	// uninit minhook
	MH_Uninitialize();
}

void* __stdcall Hooks::Hooked::AllocKeyValuesMemory(const std::int32_t size) noexcept
{
	// if function is returning to speficied addresses, return nullptr to "bypass"
	if (const std::uint32_t address = reinterpret_cast<std::uint32_t>(_ReturnAddress());
		address == reinterpret_cast<std::uint32_t>(Memory::allocKeyValuesEngine) ||
		address == reinterpret_cast<std::uint32_t>(Memory::allocKeyValuesClient))
		return nullptr; 

	return AllocKeyValuesMemoryOriginal(Interface::keyValuesSystem, size);
}

void __stdcall Hooks::Hooked::PaintTraverse(std::uintptr_t panel, bool forceRepaint, bool allowForce) noexcept
{
	//Call our original traverse func
	PaintTraverseOriginal(Interface::panel, panel, forceRepaint, allowForce);
	//get reference to panel and surface interface

	IVPanel* pPanel = Interface::panel;
	ISurface* pSurface = Interface::isurface;

	if (pPanel != nullptr && pSurface != nullptr)
		ESP::DrawUpdate(pPanel, pSurface, &panel);
}

bool __stdcall Hooks::Hooked::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	if (!cmd->commandNumber)
		return CreateMoveOriginal(Interface::clientMode, frameTime, cmd);

	if (CreateMoveOriginal(Interface::clientMode, frameTime, cmd))
		Interface::engine->SetViewAngles(cmd->viewAngles);

	return false;
}