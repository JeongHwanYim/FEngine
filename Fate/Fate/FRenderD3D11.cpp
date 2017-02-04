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
	camera.CommitListener();
	ProcessInCPU();

	float colorRGBA[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	// clear the back buffer to a deep blue
	m_pDeviceContext->ClearRenderTargetView(m_pBackbuffer, colorRGBA);

	UpdateVertexBuffer();
	UpdateIndexBuffer();
	UpdateConstantBuffer();

	// select which vertex buffer to display
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	m_pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pCBuffer);

	// select which primtive type we are using
	m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	desc.CullMode = D3D11_CULL_BACK;
	desc.FillMode = D3D11_FILL_WIREFRAME;
	desc.FrontCounterClockwise = false;
	desc.DepthClipEnable = true;

	ID3D11RasterizerState* pRasterizerState = NULL;
	m_pDevice->CreateRasterizerState(&desc, &pRasterizerState);

	m_pDeviceContext->RSSetState(pRasterizerState);

	// draw the vertex buffer to the back buffer
	m_pDeviceContext->DrawIndexed(renderedTriCorn.indices.size(), 0, 0);

	// switch the back buffer and the front buffer
	m_pSwapchain->Present(0, 0);
}

void FRenderD3D11::Finalize()
{
	m_pSwapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode
	
	// close and release all existing COM objects
	if (m_pLayout ) m_pLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pCBuffer) m_pCBuffer->Release();
	if (m_pSwapchain) m_pSwapchain->Release();
	if (m_pBackbuffer) m_pBackbuffer->Release();
	if (m_pDevice) m_pDevice->Release();
	if (m_pDeviceContext) m_pDeviceContext->Release();
}


// this is the function that creates the shape to render
void FRenderD3D11::InitGraphics()
{
	SetConstantBuffer();
	SetVertexBuffer();
	SetIndexBuffer();
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

	m_pDevice->CreateInputLayout(ied, _countof(ied), VertexShader->GetBufferPointer(), VertexShader->GetBufferSize(), &m_pLayout);
	m_pDeviceContext->IASetInputLayout(m_pLayout);
}

void FRenderD3D11::SetVertexBuffer(void)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	vertexBufferDesc.ByteWidth = sizeof(VERTEX)* triCorn.vertex.size();             // size is the VERTEX struct * VERTEX_COUNT
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	HRESULT hr;
	hr = m_pDevice->CreateBuffer(&vertexBufferDesc, NULL, &m_pVertexBuffer);       // create vertex buffer
	m_pVertexBuffer->SetPrivateData(WKPDID_D3DDebugObjectName, strlen("VertexBuffer") + 1, "VertexBuffer");
	if (FAILED(hr))
	{
		DebugBreak();
	}
}

void FRenderD3D11::SetIndexBuffer(void)
{
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	// 정적 인덱스 버퍼의 description을 작성합니다.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD)* triCorn.indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexSubresource;
	ZeroMemory(&indexSubresource, sizeof(indexSubresource));
	indexSubresource.pSysMem = triCorn.indices.data();

	HRESULT hr;
	hr = m_pDevice->CreateBuffer(&indexBufferDesc, &indexSubresource, &m_pIndexBuffer);       // create index buffer
	m_pIndexBuffer->SetPrivateData(WKPDID_D3DDebugObjectName, strlen("IndexBuffer") + 1, "IndexBuffer");
	if (FAILED(hr))
	{
		DebugBreak();
	}
}

void FRenderD3D11::SetConstantBuffer(void)
{
	D3D11_BUFFER_DESC cBufferDesc;
	ZeroMemory(&cBufferDesc, sizeof(cBufferDesc));

	// 정적 인덱스 버퍼의 description을 작성합니다.
	cBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cBufferDesc.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = 0;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	HRESULT hr;
	hr = m_pDevice->CreateBuffer(&cBufferDesc, NULL, &m_pCBuffer);       // create index buffer
	m_pCBuffer->SetPrivateData(WKPDID_D3DDebugObjectName, strlen("ConstantBuffer") + 1, "ConstantBuffer");
	if (FAILED(hr))
	{
		DebugBreak();
	}
}

void FRenderD3D11::UpdateVertexBuffer(void)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	ZeroMemory(&mappedSubresource, sizeof(mappedSubresource));
	m_pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

	memcpy(mappedSubresource.pData, renderedTriCorn.vertex.data(), mappedSubresource.RowPitch);

	m_pDeviceContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &mappedSubresource, 0, 0);       // update vertex buffer
	m_pDeviceContext->Unmap(m_pVertexBuffer, 0);
}

void FRenderD3D11::UpdateIndexBuffer(void)
{
	/*
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	ZeroMemory(&mappedSubresource, sizeof(mappedSubresource));
	m_pDeviceContext->Map(m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);

	memcpy(mappedSubresource.pData, renderedTriCorn.indices.data(), renderedTriCorn.indices.size());

	m_pDeviceContext->UpdateSubresource(m_pIndexBuffer, 0, NULL, &mappedSubresource, 0, 0);       // update index buffer
	m_pDeviceContext->Unmap(m_pIndexBuffer, 0);
	*/
}

void FRenderD3D11::UpdateConstantBuffer(void)
{
	m_ConstantBuffer.WorldViewProjection = camera.GetViewMatrix();
	m_ConstantBuffer.Fov = camera.m_fFOV;
	m_ConstantBuffer.Far = camera.m_fFar;
	m_ConstantBuffer.ScreenRatio = camera.m_fScreenRatio;

	m_pDeviceContext->UpdateSubresource(m_pCBuffer, 0, NULL, &m_ConstantBuffer, 0, 0);       // update constant buffer
}

void FRenderD3D11::ProcessInCPU(void)
{
	// 일단 싹 지우자. triCorn의 연산 결과를 renderedTriCorn에 담는다.
	renderedTriCorn.vertex.clear();
	renderedTriCorn.indices.clear();

	FMatrix ViewMat = camera.GetViewMatrix();
	FMatrix ProjMat = camera.GetProjectionMatrix();
	FVector cameraPos = camera.GetLocation();
	FVector cameraTarget = camera.GetLocation() + FVector(3, camera.m_vLook.V[0], camera.m_vLook.V[1], camera.m_vLook.V[2]);
	FVector4 cameraUp = camera.m_vUp;
/*
	D3DXMATRIX d3dViewMat;

	D3DXVECTOR3 EyePos = D3DXVECTOR3(cameraPos.V[0], cameraPos.V[1], cameraPos.V[2]);
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(cameraTarget.V[0], cameraTarget.V[1], cameraTarget.V[2]);
	D3DXVECTOR3 UpVec = D3DXVECTOR3(cameraUp.V[0], cameraUp.V[1], cameraUp.V[2]);

	D3DXMatrixLookAtLH(&d3dViewMat, &EyePos, &TargetPos, &UpVec);

	D3DXMATRIX d3dProjMat;
	D3DXMatrixPerspectiveFovLH(&d3dProjMat, camera.m_fFOV * acos(-1) / 180, camera.m_fScreenRadio, camera.m_fNear, camera.m_fFar);
*/
	FMatrix mat = ViewMat * ProjMat;

	renderedTriCorn.indices = triCorn.indices;

	for (auto& vertex : triCorn.vertex)
	{
		FVertex& ver = vertex;
		FVector4 vec = FVector4::transVector4(ver.pos);
//		vec.V[3] = vec.V[2];
		
		FVector4 res = mat.multiply(vec);

		FLOAT zVal = res.V[3];

		res.V[0] /= zVal;
		res.V[1] /= zVal;
		res.V[2] /= zVal;
		res.V[3] /= zVal;

		renderedTriCorn.vertex.push_back({ FVector(3, res.V[0], res.V[1], res.V[2]), ver.color });

		TCHAR str[256];

		swprintf_s(str, TEXT("vertex = (%f, %f, %f, %f) color = {%f %f %f %f}\n"), res.V[0], res.V[1], res.V[2], res.V[3], ver.color.V[0], ver.color.V[1], ver.color.V[2], ver.color.V[3]);
		OutputDebugString(str);
	}
}