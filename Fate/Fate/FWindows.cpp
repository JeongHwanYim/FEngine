#include "FateEngineDefine.h"

#include "FWindows.h"
#include "FRenderDevice.h"
#include "FRenderD3D11.h"

#include "FDirectInputContext.h"

namespace FTL
{
	HINSTANCE gMainInstance = 0;

#if WITH_D3D11
	IRenderDevice* gRenderDevice = new FRenderD3D11();
#else
#endif
	IInputContext* gInputContext = new FDirectInputContext();
}

namespace FTL
{
	void CreateMainWindow()
	{
		// the handle for the window, filled by a function
		HWND hWnd;
		// this struct holds information for the window class
		WNDCLASSEX wc;

		// clear out the window class for use
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		// fill in the struct with the needed information
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowMainProc;
		wc.hInstance = gMainInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = TEXT("WindowClass1");

		// register the window class
		RegisterClassEx(&wc);

		// create the window and use the result as the handle
		hWnd = CreateWindowEx(NULL,
			TEXT("WindowClass1"),    // name of the window class
			TEXT("Our First Windowed Program"),   // title of the window
			WS_OVERLAPPEDWINDOW,    // window style
			300,    // x-position of the window
			300,    // y-position of the window
			WINDOW_DEFAULT_ROW_SIZE,    // width of the window
			WINDOW_DEFAULT_COL_SIZE,    // height of the window
			NULL,    // we have no parent window, NULL
			NULL,    // we aren't using menus, NULL
			gMainInstance,    // application handle
			NULL);    // used with multiple windows, NULL

		// display the window on the screen
		ShowWindow(hWnd, 1);

		// set up and initialize Direct3D
		gRenderDevice->Initialize(hWnd);
		gInputContext->Initialize(hWnd);

		// enter the main loop:

		// this struct holds Windows event messages
		MSG msg;

		// wait for the next message in the queue, store the result in 'msg'
		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// translate keystroke messages into the right format
				TranslateMessage(&msg);

				// send the message to the WindowProc function
				DispatchMessage(&msg);

				// check to see if it's time to quit
				if (msg.message == WM_QUIT)
					break;

				gInputContext->Process();
				gRenderDevice->RenderFrame();
			}
			else
			{
				// Run game code here
				// ...
				// ...
			}
		}

		gRenderDevice->Finalize();
	}

	LRESULT CALLBACK WindowMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		unsigned int x = 0;
		unsigned int y = 0;

		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_MOUSEMOVE:
//			MessageBox(hWnd, TEXT("OnMouseMove"), NULL, NULL);
			x = static_cast<unsigned int>(LOWORD(lParam));
			y = static_cast<unsigned int>(HIWORD(lParam));
//			FMouseContext::OnMouseMove(x, y);
			break;
		case WM_MOUSEWHEEL:
//			FMouseContext::OnMouseWheel();
			return 0;
		case WM_LBUTTONUP:
//			FMouseContext::OnMouseLButtonUp();
			return 0;
		case WM_LBUTTONDOWN:
//			FMouseContext::OnMouseLButtonDown();
			return 0;
		case WM_RBUTTONUP:
//			FMouseContext::OnMouseRButtonUp();
			return 0;
		case WM_RBUTTONDOWN:
//			FMouseContext::OnMouseRButtonDown();
			return 0;
		}
		return(DefWindowProc(hWnd, message, wParam, lParam));
	}
}