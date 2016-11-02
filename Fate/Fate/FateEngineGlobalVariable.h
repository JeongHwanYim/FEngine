// 반드시 FEngineLoop 안에서만 include해야 된다.

#include "FMemAllocator.h"
#include "FRenderD3D11.h"
#include "FDirectInputContext.h"
#include "FInputManager.h"

extern FTL::IMemAllocator* gAllocator;
extern HINSTANCE gMainInstance;

#if WITH_D3D11
extern IRenderDevice* gRenderDevice;
#else
#endif


extern FInputManager* gInputManager;