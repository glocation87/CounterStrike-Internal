#pragma once
#include "../util/memory.h"

#include "cvector.h"
#include "cmatrix.h"
#include "ispatialquery.h"

class IVEngineClient
{
public:
	constexpr void GetScreenSize(std::int32_t& width, std::int32_t& height) noexcept
	{
		Memory::CallVirtual<void>(this, 5, std::ref(width), std::ref(height));
	}

	// returns index of local player
	constexpr std::int32_t GetLocalPlayerIndex() noexcept
	{
		return Memory::CallVirtual<std::int32_t>(this, 12);
	}

	constexpr void SetViewAngles(const CVector& viewAngles) noexcept
	{
		Memory::CallVirtual<void, const CVector&>(this, 19, viewAngles);
	}

	// returns true if in-game
	constexpr bool IsInGame() noexcept
	{
		return Memory::CallVirtual<bool>(this, 26);
	}

	constexpr const CMatrix4x4& WorldToScreenMatrix() noexcept
	{
		return Memory::CallVirtual<const CMatrix4x4&>(this, 37);
	}

	constexpr ISpacialQuery* GetBSPTreeQuery() noexcept
	{
		return Memory::CallVirtual<ISpacialQuery*>(this, 43);
	}
};