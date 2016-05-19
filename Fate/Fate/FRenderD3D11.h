#pragma once

#include "FRenderDevice.h"
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

#include "FTriCorn.h"

class FRenderD3D11 : public IRenderDevice
{
public:
	virtual bool Initialize(HWND hWindow);
	virtual void RenderFrame();
	virtual void Finalize();
private:
	void InitGraphics(void);    // creates the shape to render
	void InitPipeline(void);    // loads and prepares the shaders
private:
	IDXGISwapChain *m_pSwapchain;             // the pointer to the swap chain interface
	ID3D11Device *m_pDevice;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext *m_pDeviceContext;           // the pointer to our Direct3D device context

	ID3D11RenderTargetView *m_pBackbuffer;    // global declaration

	ID3D11InputLayout *m_pLayout;            // the pointer to the input layout
	ID3D11VertexShader *m_pVertexShader;               // the pointer to the vertex shader
	ID3D11PixelShader *m_pPixelShader;                // the pointer to the pixel shader
	ID3D11Buffer *m_pVertexBuffer;                // the pointer to the vertex buffer
	ID3D11Buffer *m_pIndexBuffer;				// ÀÎµ¦½º¹öÆÛ ¤»

	FTriCorn TriCorn;
};

struct VERTEX{ FLOAT X, Y, Z; D3DXCOLOR Color; FMatrix LocWorldProjMatrix; };
