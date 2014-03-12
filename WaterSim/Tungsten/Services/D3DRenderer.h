#pragma once
#include "pch.h"
#include "DirectXTK\WICTextureLoader.h"

#include "..\PlatformTools.h"
#include "..\DataContainers.h"

#include "..\ServiceLocator.h"
#ifdef _DESKTOPAPP
#include <d3d11.h>
#endif
#ifdef _WINRTAPP
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d11_1.h>
#include <windows.ui.xaml.media.dxinterop.h>
#endif


namespace Tungsten
{

class D3DRenderer: public IGraphicsService
{
private:
#if defined _WINRTAPP
	
	ISwapChainBackgroundPanelNative*	g_SwapChainBackgroundPanelNative;
	IDXGISwapChain1*					dxgiSwapChain;
#endif
	
#if defined _DESKTOPAPP
	IDXGISwapChain*						dxgiSwapChain;
#endif


	//ID3D11Debug*						debug;
	Vector<2>							resolutionImpl;
	float								g_dpi;
	

	ID3D11Device*						device;
	ID3D11DeviceContext*				context;

	//Active state
	ID3D11BlendState*					blendState;

	


	ID3D11RenderTargetView*				renderTargetView;
	ID3D11DepthStencilView*				depthStencilView;
	IDXGISurface*						dxgiBuffer;							

	float ConvertDpisToPixels(float dips);
public:

#if defined _WINRTAPP
	
	D3DRenderer(Windows::UI::Core::CoreWindow^								m_coreWindow,
				Windows::UI::Xaml::Controls::SwapChainBackgroundPanel^		m_swapChain);
	D3DRenderer(Windows::UI::Core::CoreWindow^								m_coreWindow);
#endif
#if defined _DESKTOPAPP
	D3DRenderer::D3DRenderer(HWND	h_window);
#endif
	
	
	//IGraphicsService interface
	//void		LoadStates(WCHAR*);


	void		Refresh() ;
	
	Texture		LoadTexture(WCHAR* filepath);
	void		Present();
	

	Vector<2>	GetResolution();
	
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetContext();

	
	/*void		SetBuffers(MemoryBlock vertexData,MemoryBlock indexData, MemoryBlock constantData=MemoryBlock());
	void		DrawIndexed(UINT IndexCount,UINT StartIndexLocation,INT BaseVertexLocation);
	void		PSSetShaderResource(void* shaderView,int index);
	void		VSSetShaderResource(void* shaderView,int index);
	void		SetConstantBufferVS(MemoryBlock buffer,int index);
	void		SetConstantBufferPS(MemoryBlock buffer,int index);
	void		DrawInstanced(MemoryBlock vertexData,MemoryBlock indexData,MemoryBlock instanceData);*/
	void		ClearContext();

	void Clear(float clearcolor[4]);
	
	~D3DRenderer(void);
 
	
	
};
	
}
	
	