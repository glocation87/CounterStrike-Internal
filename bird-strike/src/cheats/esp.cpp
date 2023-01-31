/*
	* References
	pSurface->DrawSetColor(0, 255, 0, 255);
	pSurface->DrawLine(10, 10, 60, 10);
	pSurface->DrawFilledRect(10, 20, 60, 70);
	pSurface->DrawOutlinedRect(10, 80, 60, 130);
*/

#include "esp.h"

void ESP::DrawUpdate(IVPanel* pPanel, ISurface* pSurface, std::uintptr_t* panel_t) noexcept
{
	//check if current panel is MatSystemTopPanel, this is what we will draw over/on
	if (lstrcmpA(pPanel->GetName(*panel_t), "MatSystemTopPanel") == 0)
	{
		//create reference to local player
		CEntity* localPlayer = Interface::entityList->GetEntityFromIndex(Interface::engine->GetLocalPlayerIndex());

		int ScrW, ScrH;
		Interface::engine->GetScreenSize(ScrW, ScrH);

		//ensure font is initialized
		if (!ESP::Font)
		{
			ESP::Font = pSurface->FontCreate();
			pSurface->SetFontGlyphSet(ESP::Font, "Calibri", 14, 150, 0, 0, ISurface::EFontFlag::FONT_FLAG_OUTLINE);
		}

		//Loop entity list
		for (int32_t i = 0; i < 64; i++)
		{
			//check if local player
			if (i == localPlayer->GetIndex())
				continue;

			CEntity* pEntity = Interface::entityList->GetEntityFromIndex(i);
			CVector* pEntityPosition = new CVector;
			
			if (pEntity != nullptr)
			{
				//team check
				//if (entity->GetTeam() == localPlayer->GetTeam())
					//continue;
				//CVector bonePos = GetBonePosition(pEntity, 0);
				//CVector* pBonePos = &bonePos;

				const CVector entityWorldPosition = pEntity->GetAbsOrigin();
				WorldToScreen(entityWorldPosition, pEntityPosition);
				//WorldToScreen(bonePos, pBonePos);

				//set draw color
				pSurface->DrawSetColor(0, 255, 25, 255);

				//draw from screen center to ent position
				pSurface->DrawLine((ScrW/2), (ScrH/2), pEntityPosition->x, pEntityPosition->y);
				
				
				delete pEntityPosition;
			}
		}
	}
}

//source: https://www.unknowncheats.me/forum/counterstrike-global-offensive/285042-w2s-function-world-screen.html
void ESP::WorldToScreen(const CVector originVector, CVector* outputVector) noexcept
{
	const CMatrix4x4* quaternion = &(Interface::engine->WorldToScreenMatrix());

	int ScrW, ScrH;
	Interface::engine->GetScreenSize(ScrW, ScrH);

	float w = quaternion->data[3][0] * originVector.x + quaternion->data[3][1] * originVector.y + quaternion->data[3][2] * originVector.z + quaternion->data[3][3];

	if (w > 0.01)
	{
		float inverseWidth = 1 / w;
		outputVector->x = (ScrW / 2) + (0.5 * ((quaternion->data[0][0] * originVector.x + quaternion->data[0][1] * originVector.y + quaternion->data[0][2] * originVector.z + quaternion->data[0][3]) * inverseWidth) * ScrW + 0.5);
		outputVector->y = (ScrH / 2) - (0.5 * ((quaternion->data[1][1] * originVector.x + quaternion->data[1][1] * originVector.y + quaternion->data[1][2] * originVector.z + quaternion->data[1][3]) * inverseWidth) * ScrH + 0.5);
		outputVector->z = (ScrH / 2) - (0.5 * ((quaternion->data[2][1] * originVector.x + quaternion->data[2][1] * originVector.y + quaternion->data[2][2] * originVector.z + quaternion->data[2][3]) * inverseWidth) * ScrH + 0.5);
	}
}

CMatrix3x4* ESP::GetBoneMatrix(CEntity* entity) noexcept
{
	return Memory::Read<CMatrix3x4*, DWORD*>(Memory::Read<DWORD*, DWORD>(*reinterpret_cast<DWORD*>(entity) + static_cast<DWORD>(0x26A8)));
}

CVector ESP::GetBonePosition(CEntity* entity, int boneIdx) noexcept
{
	CVector bonePosition;
	CMatrix3x4 boneMatrix = Memory::Read<CMatrix3x4, DWORD>(*reinterpret_cast<DWORD*>(GetBoneMatrix(entity)) + static_cast<DWORD>(0x30 * boneIdx));
	bonePosition.x = boneMatrix.data[0][3];
	bonePosition.y = boneMatrix.data[1][3];
	bonePosition.z = boneMatrix.data[2][3];
	return bonePosition;
}