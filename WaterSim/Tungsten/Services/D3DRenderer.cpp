#include "pch.h"
#include "D3DRenderer.h"
#include "DirectXTK\DDSTextureLoader.h"



using namespace DirectX;
using namespace Tungsten;
using namespace Tungsten::PlatformTools;
#pragma comment(lib,"d3d11.lib")

#if defined _WINRTAPP
#include <windows.ui.xaml.interop.h>

D3DRenderer::D3DRenderer(	Windows::UI::Core::CoreWindow^								m_coreWindow,
					Windows::UI::Xaml::Controls::SwapChainBackgroundPanel^		m_swapChain)
					:IGraphicsService(resolutionImpl)
{
	ISwapChainBackgroundPanelNative* p_SwapChainBP;
	reinterpret_cast<IUnknown*>(m_swapChain)->QueryInterface(__uuidof(ISwapChainBackgroundPanelNative),(void**)&p_SwapChainBP);
	float dpi = Windows::Graphics::Display::DisplayInformation::GetForCurrentView()->LogicalDpi;
	
	float width=m_coreWindow->Bounds.Width;
	float height=m_coreWindow->Bounds.Height;
	
	
	//Create Device
	UINT creationflags;
	creationflags=D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	creationflags|=D3D11_CREATE_DEVICE_DEBUG;
	
	D3D_FEATURE_LEVEL farray[]=
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	
	D3D11CreateDevice(
		nullptr,
		
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationflags,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&device,
		nullptr,
		&context);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	IDXGIDevice1* dxgidev;
	reinterpret_cast<IUnknown*>(device)->QueryInterface(__uuidof(IDXGIDevice1),(void**)&dxgidev);
	IDXGIAdapter* dxgiAdapt;
	dxgidev->GetAdapter(&dxgiAdapt);
	IDXGIFactory2* dxgifact;
	dxgiAdapt->GetParent(__uuidof(IDXGIFactory2),(void**)&dxgifact);

	//Create SwapChain
	DXGI_SWAP_CHAIN_DESC1 sc_desc;

	sc_desc.Width=(UINT) width;
	sc_desc.Height=(UINT) height;

	sc_desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;

	sc_desc.Stereo=false;
	//Multisampling
	sc_desc.SampleDesc.Count=1;
	sc_desc.SampleDesc.Quality=0;
	sc_desc.BufferUsage=DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sc_desc.BufferCount=2;
	sc_desc.Scaling= DXGI_SCALING_STRETCH;
	sc_desc.SwapEffect=DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	sc_desc.AlphaMode=DXGI_ALPHA_MODE_IGNORE;
	sc_desc.Flags=0;
	dxgifact->CreateSwapChainForComposition(device,
		&sc_desc,
		nullptr,
		&g_pdxgiSwapChain);

	//Set up the depth stencil
	ID3D11Texture2D* pDepthStencil = NULL;
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = (int)width;
	descDepth.Height = (int)height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	device ->CreateTexture2D( &descDepth, NULL, &pDepthStencil ) ;
	
	D3D11_DEPTH_STENCIL_DESC dsDesc;

	//Depth test
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;


	dsDesc.StencilEnable = false;


	
	ID3D11DepthStencilState * pDSState;

	device->CreateDepthStencilState(&dsDesc, &pDSState);
	
	//
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags=0;

	
	device->CreateDepthStencilView( pDepthStencil,
		&descDSV, 
		&depthStencilView );  

	
	context->OMSetDepthStencilState(pDSState, 1);
	
	//Render Target
	CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc(
		D3D11_RTV_DIMENSION_TEXTURE2DARRAY,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		0,
		0,
		1
	);
	ID3D11Texture2D* backbuffer;
		g_pdxgiSwapChain->GetBuffer(0,IID_PPV_ARGS(&backbuffer));
	
	CD3D11_VIEWPORT viewport(
		0.0f,
		0.0f,
		width,
		height
		);
	context->RSSetViewports(1,&viewport);
	
	device->CreateRenderTargetView(backbuffer,&renderTargetViewDesc,&renderTargetView);

	context->OMSetRenderTargets( 1,          
		&renderTargetView,      
		depthStencilView );     
	//#!
	HRESULT hr=
	p_SwapChainBP->SetSwapChain(g_pdxgiSwapChain);

	
	
	//Shader Loading

	float color[4]={0.0f,0.0f,1.0f,1.0f};
	this->Clear(color);
	g_pdxgiSwapChain->Present(0,0);
}

D3DRenderer::D3DRenderer(Windows::UI::Core::CoreWindow^	m_coreWindow)
:IGraphicsService(resolutionImpl)
{
	
	float width=m_coreWindow->Bounds.Width;
	float height=m_coreWindow->Bounds.Height;
	resolutionImpl.x=width;
	resolutionImpl.y=height;

	//Create Device
	UINT creationflags;
	creationflags=D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	creationflags|=D3D11_CREATE_DEVICE_DEBUG;
	
	D3D_FEATURE_LEVEL farray[]=
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	D3D11CreateDevice(
		nullptr,
		
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationflags,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&device,
		nullptr,
		&context);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	IDXGIDevice1* dxgidev;
	reinterpret_cast<IUnknown*>(device)->QueryInterface(__uuidof(IDXGIDevice1),(void**)&dxgidev);
	IDXGIAdapter* dxgiAdapt;
	dxgidev->GetAdapter(&dxgiAdapt);
	IDXGIFactory2* dxgifact;
	dxgiAdapt->GetParent(__uuidof(IDXGIFactory2),(void**)&dxgifact);

	//Create SwapChain
	DXGI_SWAP_CHAIN_DESC1 sc_desc;

	sc_desc.Width=(UINT) width;
	sc_desc.Height=(UINT) height;

	sc_desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;

	sc_desc.Stereo=false;
	//Multisampling
	sc_desc.SampleDesc.Count=1;
	sc_desc.SampleDesc.Quality=0;
	sc_desc.BufferUsage=DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sc_desc.BufferCount=2;
	sc_desc.Scaling= DXGI_SCALING_STRETCH;
	sc_desc.SwapEffect=DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	sc_desc.AlphaMode=DXGI_ALPHA_MODE_IGNORE;
	sc_desc.Flags=0;
	dxgifact->CreateSwapChainForCoreWindow(device,
		reinterpret_cast<IUnknown*>(m_coreWindow),
		&sc_desc,
		nullptr,
		&g_pdxgiSwapChain);

	//Set up the depth stencil
	ID3D11Texture2D* pDepthStencil = NULL;
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = (int)width;
	descDepth.Height = (int)height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	device ->CreateTexture2D( &descDepth, NULL, &pDepthStencil ) ;
	
	D3D11_DEPTH_STENCIL_DESC dsDesc;

	//Depth test
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;


	dsDesc.StencilEnable = false;


	
	ID3D11DepthStencilState * pDSState;

	device->CreateDepthStencilState(&dsDesc, &pDSState);
	
	//
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags=0;

	
	device->CreateDepthStencilView( pDepthStencil,
		&descDSV, 
		&depthStencilView );  

	
	context->OMSetDepthStencilState(pDSState, 1);
	
	//Render Target
	CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc(
		D3D11_RTV_DIMENSION_TEXTURE2DARRAY,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		0,
		0,
		1
	);
	ID3D11Texture2D* backbuffer;
		g_pdxgiSwapChain->GetBuffer(0,IID_PPV_ARGS(&backbuffer));
	
	CD3D11_VIEWPORT viewport(
		0.0f,
		0.0f,
		width,
		height
		);
	context->RSSetViewports(1,&viewport);
	
	device->CreateRenderTargetView(backbuffer,&renderTargetViewDesc,&renderTargetView);

	context->OMSetRenderTargets( 1,          
		&renderTargetView,      
		depthStencilView );     
	

	float color[4]={0.0f,0.0f,1.0f,1.0f};
	this->Clear(color);
	g_pdxgiSwapChain->Present(0,0);

}

float D3DRenderer::ConvertDpisToPixels(float dips)
{
	static const float dipsPerInch = 96.0f;
	return floor(dips * g_dpi / dipsPerInch + 0.5f); // Round to nearest integer.
}

#endif

#if defined _DESKTOPAPP
D3DRenderer::D3DRenderer(HWND	h_window)
:IGraphicsService(resolutionImpl)
{
	ConfigurationState config=Services.Config()->Get();
	UINT flags=0;
	flags|=D3D11_CREATE_DEVICE_SINGLETHREADED; //D3D calls will only come from one thread
	flags|=D3D11_CREATE_DEVICE_BGRA_SUPPORT;	//required for D2D interop
#if defined _DEBUG
	flags|=D3D11_CREATE_DEVICE_DEBUG;
#endif
	DXGI_SWAP_CHAIN_DESC scDescription;
	scDescription.BufferDesc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
	scDescription.BufferDesc.Height=config.resolution.height;
	scDescription.BufferDesc.Width=config.resolution.width;
	DXGI_RATIONAL refreshRate={0,0};	//Use active refresh rate
	scDescription.BufferDesc.RefreshRate=refreshRate;
	//Default values, black magic inside
	scDescription.BufferDesc.Scaling=DXGI_MODE_SCALING_UNSPECIFIED;
	scDescription.BufferDesc.ScanlineOrdering=DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	scDescription.BufferCount=2;
	scDescription.BufferUsage=DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDescription.Flags=0;
	scDescription.OutputWindow=h_window;
	scDescription.SampleDesc.Count=1;
	scDescription.SampleDesc.Quality=0;
	scDescription.SwapEffect=DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	scDescription.Windowed=true;
	if(config.windowed==config.no)
		scDescription.Windowed=false;

	D3D11CreateDeviceAndSwapChain(
		NULL,						//Use default adapter
		D3D_DRIVER_TYPE_HARDWARE,	//Use hardware renderer
		NULL,						//Sofware DLL, not used
		flags,
		NULL,						//Uses default feature level array D3D_FEATURE_LEVEL_11_0 to 9_1
		NULL,						//Number of feature levels, use default
		D3D11_SDK_VERSION,
		&scDescription,
		&dxgiSwapChain,
		&device,
		NULL,
		&context
		);
	UINT sampleLevels[10];
	device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,1,sampleLevels);
	//device->QueryInterface(IID_PPV_ARGS(&debug));
	//debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ID3D11Texture2D* depthTexture;
	D3D11_TEXTURE2D_DESC depthTextureDesc;
	depthTextureDesc.ArraySize=1;
	depthTextureDesc.BindFlags=D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.CPUAccessFlags=NULL;
	depthTextureDesc.Format=DXGI_FORMAT_D32_FLOAT;
	depthTextureDesc.Height=config.resolution.height;
	depthTextureDesc.MipLevels=1;
	depthTextureDesc.MiscFlags=0;
	depthTextureDesc.SampleDesc.Count=1;
	depthTextureDesc.SampleDesc.Quality=0;
	depthTextureDesc.Usage=D3D11_USAGE_DEFAULT;
	depthTextureDesc.Width=config.resolution.width;
	CheckFatalError(device->CreateTexture2D(&depthTextureDesc,NULL,&depthTexture));
	CheckFatalError( device->CreateDepthStencilView(depthTexture,NULL,&depthStencilView) );
	D3D11_DEPTH_STENCIL_DESC depthStateDesc;
	depthStateDesc.DepthEnable=true;
	depthStateDesc.DepthFunc=D3D11_COMPARISON_LESS_EQUAL;
	depthStateDesc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ALL;
	depthStateDesc.StencilEnable=false;
	ID3D11DepthStencilState* depthState;
	CheckFatalError( device->CreateDepthStencilState(&depthStateDesc,&depthState) );
	context->OMSetDepthStencilState(depthState,NULL);
	//TODO:Remove this
	ID3D11Texture2D* backbuffer;
	dxgiSwapChain->GetBuffer(0,IID_PPV_ARGS(&backbuffer));
	device->CreateRenderTargetView(backbuffer,NULL,&renderTargetView);
	/*D3D11_RASTERIZER_DESC rasteriser;
	rasteriser.FillMode=D3D11_FILL_SOLID;
	rasteriser.CullMode=D3D11_CULL_NONE;
	rasteriser.FrontCounterClockwise=false;
	rasteriser.DepthBias=0.0f;
	rasteriser.SlopeScaledDepthBias=0.0f;
	rasteriser.DepthBiasClamp=0.0f;
	rasteriser.DepthClipEnable=true;
	rasteriser.ScissorEnable=false;
	rasteriser.MultisampleEnable=false;
	rasteriser.AntialiasedLineEnable=false;
	ID3D11RasterizerState* rasteriserState;
	device->CreateRasterizerState(&rasteriser,&rasteriserState);
	context->RSSetState(rasteriserState);*/
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CD3D11_VIEWPORT viewport(
		0.0f,
		0.0f,
		(float)config.resolution.width,
		(float)config.resolution.height
		);
	resolutionImpl.x = config.resolution.width;
	resolutionImpl.y = config.resolution.height;
	context->RSSetViewports(1,&viewport);

	

	float color[4]={1.0f,0.0f,1.0f,1.0f};
	this->Clear(color);
	dxgiSwapChain->Present(0,0);
};

#endif


void D3DRenderer::Clear(float clearcolor[4])
{
	context->ClearRenderTargetView(renderTargetView,clearcolor);	
	context->ClearDepthStencilView(depthStencilView,D3D11_CLEAR_DEPTH,1.0f,(UINT8)0.0f);
}



D3DRenderer::~D3DRenderer(void)
{
	renderTargetView->Release();
	depthStencilView->Release();
	context->Release();
	device->Release();
}


#pragma region IGraphicsService
//IGraphicsService implementations
void D3DRenderer::Refresh()
{
	
	
	//context->OMSetRenderTargets(1,&renderTargetView,depthStencilView);
	float color[4];
	color[0]=0.0f;
	color[1]=0.0f;
	color[2] = 0.0f;
	color[3]=1.0f;
	
	Clear(color);
}




Texture D3DRenderer::LoadTexture(WCHAR* filepath)
{
	Texture ret;
	//CreateWICTextureFromFile(this->device,this->context,filepath,&ret.resource,&ret.shaderView);
	return ret;
}

void D3DRenderer::Present()
{
	
	//dxgiSwapChain->GetBuffer(0,IID_PPV_ARGS(&dxgiBuffer));
	//Do not mess these arguments,ever, AGAIN!!!!!!
	dxgiSwapChain->Present(1,0);
	//dxgiBuffer->Release();
	
}

Vector<2> D3DRenderer::GetResolution()
{
	return resolutionImpl;
}

ID3D11Device* D3DRenderer::GetDevice()
{
	return device;
}

ID3D11DeviceContext* D3DRenderer::GetContext()
{
	return context;
}

void D3DRenderer::ClearContext()
{
	context->ClearState();
	context->OMSetRenderTargets(1,&renderTargetView,depthStencilView);
	CD3D11_VIEWPORT viewport(
		0.0f,
		0.0f,
		resolution.x,
		resolution.y
		);	
	context->RSSetViewports(1,&viewport);
}

#pragma endregion