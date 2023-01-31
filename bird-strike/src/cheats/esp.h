#pragma once
#include "../core/interfaces.h"

namespace ESP
{
	void DrawUpdate(IVPanel* pPanel, ISurface* pSurface, std::uintptr_t* panel_t) noexcept;
	void WorldToScreen(const CVector originVector, CVector* outputVector) noexcept;
	CMatrix3x4* GetBoneMatrix(CEntity* entity) noexcept;
	CVector GetBonePosition(CEntity* entity, int boneIdx) noexcept;
	inline DWORD Font;
}