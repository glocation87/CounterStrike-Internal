#include "../valve/headers.h"

namespace Interface
{
	// initialize interface pointers
	void Initialize() noexcept;

	// Returns the interface
	template <typename T>
	T* Get(LPCWSTR module, const char* _interface) noexcept;

	inline IBaseClientDLL* client = nullptr;
	inline IGlowManager* glowManager = nullptr;
	inline IGlobalVars* globals = nullptr;
	inline IClientEntityList* entityList = nullptr;
	inline IClientModeShared* clientMode = nullptr;
	inline IVModelInfo* modelInfo = nullptr;
	inline IVDebugOverlay* debugOverlay = nullptr;
	inline IVEngineClient* engine = nullptr;
	inline IVPanel* panel = nullptr;
	inline ISurface* isurface = nullptr;

	// other
	inline void* keyValuesSystem = nullptr;
}