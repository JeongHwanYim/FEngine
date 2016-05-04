#include "FateEngineDefine.h"
#include "FateEngineGlobalVariable.h"

#include <tchar.h>
#include <string.h>
#include <vector>
#include <string>

#include "FMemAllocator.h"
#include "FArray.h"
#include "FTestHelper.h"
#include "FWindows.h"

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#pragma region IncludeLibrary
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma endregion

size_t ParseCommandLine(FArray<TCHAR*>& CmdList, const LPTSTR CommandLine)
{
	LPTSTR pNextToken = NULL;
	LPTSTR pToken = _tcstok_s(CommandLine, TEXT(" "), &pNextToken);

	while (pToken != NULL)
	{
		CmdList.push_back(pToken);
		pToken = _tcstok_s(NULL, TEXT(" "), &pNextToken);
	}

	return CmdList.Size();
}

int APIENTRY _tWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPTSTR		lpCmdLine,
	int			nCmdShow)
{
	RegistMainInstance(hInstance);

	FArray<TCHAR*> CmdList;
	size_t nSize = ParseCommandLine(CmdList, GetCommandLine());

	// 모든 테스트가 검증되는지 확인.
	bool RunTestAllPassed = FTestExecutor::RunTest();

	CreateMainWindow();

	return 0;
}