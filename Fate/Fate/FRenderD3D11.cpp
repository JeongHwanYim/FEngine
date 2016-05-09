#include "FateEngineDefine.h"
#include "FRenderD3D11.h"
#include "FMemFunc.h"

bool FRenderD3D11::Initialize(HWND hWindow)
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferDesc.Width = FTL::WINDOW_DEFAULT_ROW_SIZE;                    // set the back buffer width
	scd.BufferDesc.Height = FTL::WINDOW_DEFAULT_COL_SIZE;                  // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWindow;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_pSwapchain,
		&m_pDevice,
		NULL,
		&m_pDeviceContext);


	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	m_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pBackbuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackbuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = FTL::WINDOW_DEFAULT_ROW_SIZE;
	viewport.Height = FTL::WINDOW_DEFAULT_COL_SIZE;

	m_pDeviceContext->RSSetViewports(1, &viewport);

	InitPipeline();
	InitGraphics();

	return true;
}

void FRenderD3D11::RenderFrame()
{
	float colorRGBA[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	// clear the back buffer to a deep blue
	m_pDeviceContext->ClearRenderTargetView(m_pBackbuffer, colorRGBA);


	// select which vertex buffer to display
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	m_pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// select which primtive type we are using
	m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the vertex buffer to the back buffer
	m_pDeviceContext->DrawIndexed(FTriCorn::INDEX_COUNT, 0, 0);

	// switch the back buffer and the front buffer
	m_pSwapchain->Present(0, 0);

}

void FRenderD3D11::Finalize()
{
	m_pSwapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode
	
	// close and release all existing COM objects
	m_pLayout->Release();
	m_pVertexShader->Release();
	m_pPixelShader->Release();
	m_pVertexBuffer->Release();
	m_pSwapchain->Release();
	m_pBackbuffer->Release();
	m_pDevice->Release();
	m_pDeviceContext->Release();
}


// this is the function that creates the shape to render
void FRenderD3D11::InitGraphics()
{
	// create a triangle using the VERTEX struct
//	VERTEX OurVertices[] =
//	{
//		{ 0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
//		{ 0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
//		{ -0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) }
//	};

	VERTEX OurVertices[FTriCorn::VERTEX_COUNT];
	for (int i = 0; i < FTriCorn::VERTEX_COUNT; ++i)
	{
		OurVertices[i].X = TriCorn.vertex[i].pos.V[0];
		OurVertices[i].Y = TriCorn.vertex[i].pos.V[1];
		OurVertices[i].Z = TriCorn.vertex[i].pos.V[2];

		OurVertices[i].Color.r = TriCorn.vertex[i].color.V[0];
		OurVertices[i].Color.g = TriCorn.vertex[i].color.V[1];
		OurVertices[i].Color.b = TriCorn.vertex[i].color.V[2];
		OurVertices[i].Color.a = TriCorn.vertex[i].color.V[3];
	}


	// create the vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	TCHAR buff[256];
	swprintf_s(buff, TEXT("size : %d"), sizeof(OurVertices));
	OutputDebugString(buff);

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	vertexBufferDesc.ByteWidth = sizeof(VERTEX)* FTriCorn::VERTEX_COUNT;             // size is the VERTEX struct * VERTEX_COUNT
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	// 정적 인덱스 버퍼의 description을 작성합니다.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(WORD)* FTriCorn::INDEX_COUNT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexSubsourceData;
	indexSubsourceData.pSysMem = TriCorn.indices.data();
	indexSubsourceData.SysMemPitch = 0;
	indexSubsourceData.SysMemSlicePitch = 0;

	m_pDevice->CreateBuffer(&vertexBufferDesc, NULL, &m_pVertexBuffer);       // create vertex buffer
	m_pDevice->CreateBuffer(&indexBufferDesc, &indexSubsourceData, &m_pIndexBuffer);       // create index buffer

	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	m_pDeviceContext->Map(m_pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
	m_pDeviceContext->Unmap(m_pVertexBuffer, NULL);                                      // unmap the buffer

	m_pDeviceContext->Map(m_pIndexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, NULL);    // map the buffer
	m_pDeviceContext->Unmap(m_pIndexBuffer, NULL);
}


// this function loads and prepares the shaders
void FRenderD3D11::InitPipeline()
{
	// load and compile the two shaders
	ID3D10Blob *VertexShader, *PixelShader;
	D3DX11CompileFromFile(TEXT("..\\..\\Resource\\Shader\\shader.shader"), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VertexShader, 0, 0);
	D3DX11CompileFromFile(TEXT("..\\..\\Resource\\Shader\\shader.shader"), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PixelShader, 0, 0);

	// encapsulate both shaders into shader objects
	m_pDevice->CreateVertexShader(VertexShader->GetBufferPointer(), VertexShader->GetBufferSize(), NULL, &m_pVertexShader);
	m_pDevice->CreatePixelShader(PixelShader->GetBufferPointer(), PixelShader->GetBufferSize(), NULL, &m_pPixelShader);

	// set the shader objects
	m_pDeviceContext->VSSetShader(m_pVertexShader, 0, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	m_pDevice->CreateInputLayout(ied, 2, VertexShader->GetBufferPointer(), VertexShader->GetBufferSize(), &m_pLayout);
	m_pDeviceContext->IASetInputLayout(m_pLayout);
}