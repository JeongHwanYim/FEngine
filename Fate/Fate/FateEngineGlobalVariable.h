// 반드시 FEngineLoop 안에서만 include해야 된다.

#include "FMemAllocator.h"
#include "FRenderD3D11.h"
#include "FDirectInputContext.h"
#include "FInputManager.h"

FTL::IMemAllocator* gAllocator = new FTL::StdAllocator();
HINSTANCE gMainInstance = 0;

#if WITH_D3D11
IRenderDevice* gRenderDevice = new FRenderD3D11();
#else
#endif


FInputManager* gInputManager = new FInputManager();