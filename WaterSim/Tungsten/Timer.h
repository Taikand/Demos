#pragma once
class Timer
{
private:
	__int64 zeroTime;
	__int64 previousTime;
	__int64 delta;
	__int64 totalTime;
	__int64 countsPerSec;
	__int64 pausedTime;
	bool pause;
public:
	Timer(void);
	~Timer(void);
	void Tick();			//Recalculates delta
	float GetDelta();		//Difference between two ticks , in seconds
	__int64 GetTotal();		//Total time in seconds,as integer
	float GetTotalFloat();
	void Pause();
	void Start();
	float GetDynamicDelta();	//Time since last Tick, update every time
};

//
//	switch (state)
//	{
//		case SpriteRender : 
//			vertexBufferDesc.BindFlags=				D3D11_BIND_VERTEX_BUFFER;
//			vertexBufferDesc.CPUAccessFlags=		NULL;
//			vertexBufferDesc.MiscFlags=				NULL;
//			vertexBufferDesc.StructureByteStride=	NULL;
//			vertexBufferDesc.Usage=					D3D11_USAGE_DEFAULT;
//
//			vertexStride=sizeof(SpriteVertex);
//
//			indexDesc.BindFlags=D3D11_BIND_INDEX_BUFFER;
//			indexDesc.CPUAccessFlags=NULL;
//			indexDesc.MiscFlags=NULL;
//			indexDesc.StructureByteStride=NULL;
//			indexDesc.Usage=D3D11_USAGE_DEFAULT;
//
//			
//
//			context->PSSetShader(effects[0].PS,NULL,NULL);
//			context->VSSetShader(effects[0].VS,NULL,NULL);
//			context->IASetInputLayout(effects[0].IA);
//
//			D3D11_SAMPLER_DESC samplerDesc;
//			samplerDesc.AddressU=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc.AddressV=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc.ComparisonFunc=D3D11_COMPARISON_NEVER;
//			samplerDesc.BorderColor[0]=1.0f;
//			samplerDesc.BorderColor[1]=1.0f;
//			samplerDesc.BorderColor[2]=1.0f;
//			samplerDesc.BorderColor[3]=1.0f;
//			samplerDesc.Filter=D3D11_FILTER_ANISOTROPIC;
//			samplerDesc.MaxAnisotropy=1;
//			samplerDesc.MaxLOD=FLT_MAX;
//			samplerDesc.MinLOD=-FLT_MAX;
//			samplerDesc.MipLODBias=0;
//			ID3D11SamplerState* samplerState;
//			device->CreateSamplerState(&samplerDesc,&samplerState);
//			context->PSSetSamplers(0,1,&samplerState);
//			samplerState->Release();
//
//			D3D11_BLEND_DESC blendDesc;
//			blendDesc.AlphaToCoverageEnable=false;
//			blendDesc.IndependentBlendEnable=false;
//			blendDesc.RenderTarget[0].BlendEnable=true;
//			blendDesc.RenderTarget[0].BlendOp=D3D11_BLEND_OP_ADD;
//			blendDesc.RenderTarget[0].BlendOpAlpha=D3D11_BLEND_OP_ADD;
//			blendDesc.RenderTarget[0].DestBlend=D3D11_BLEND_INV_SRC_ALPHA;
//			blendDesc.RenderTarget[0].DestBlendAlpha=D3D11_BLEND_ONE;
//			blendDesc.RenderTarget[0].SrcBlend=D3D11_BLEND_SRC_ALPHA;
//			blendDesc.RenderTarget[0].SrcBlendAlpha=D3D11_BLEND_SRC_ALPHA;
//			blendDesc.RenderTarget[0].RenderTargetWriteMask=D3D11_COLOR_WRITE_ENABLE_ALL;
//			
//			device->CreateBlendState(&blendDesc,&blendState);
//			context->OMSetBlendState(blendState,NULL,0xffffffff);
//						
//			break;
//		case SimpleModel :
//			D3D11_SAMPLER_DESC samplerDesc1;
//			samplerDesc1.AddressU=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc1.AddressV=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc1.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc1.ComparisonFunc=D3D11_COMPARISON_NEVER;
//			samplerDesc1.BorderColor[0]=1.0f;
//			samplerDesc1.BorderColor[1]=1.0f;
//			samplerDesc1.BorderColor[2]=1.0f;
//			samplerDesc1.BorderColor[3]=1.0f;
//			samplerDesc1.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//			samplerDesc1.MaxAnisotropy=1;
//			samplerDesc1.MaxLOD=FLT_MAX;
//			samplerDesc1.MinLOD=-FLT_MAX;
//			samplerDesc1.MipLODBias=0;
//			ID3D11SamplerState* samplerState1;
//			device->CreateSamplerState(&samplerDesc1,&samplerState1);
//			context->PSSetSamplers(0,1,&samplerState1);
//			samplerState1->Release();
//			vertexBufferDesc.BindFlags=				D3D11_BIND_VERTEX_BUFFER;
//			vertexBufferDesc.CPUAccessFlags=		NULL;
//			vertexBufferDesc.MiscFlags=				NULL;
//			vertexBufferDesc.StructureByteStride=	NULL;
//			vertexBufferDesc.Usage=					D3D11_USAGE_DEFAULT;
//
//			vertexStride=sizeof(float)*9;
//
//			indexDesc.BindFlags=D3D11_BIND_INDEX_BUFFER;
//			indexDesc.CPUAccessFlags=NULL;
//			indexDesc.MiscFlags=NULL;
//			indexDesc.StructureByteStride=NULL;
//			indexDesc.Usage=D3D11_USAGE_DEFAULT;
//
//			
//
//			context->PSSetShader(effects[1].PS,NULL,NULL);
//			context->VSSetShader(effects[1].VS,NULL,NULL);
//			context->IASetInputLayout(effects[1].IA);
//			break;
//		case SkyBox :
//			D3D11_SAMPLER_DESC samplerDesc2;
//			samplerDesc2.AddressU=D3D11_TEXTURE_ADDRESS_BORDER;
//			samplerDesc2.AddressV=D3D11_TEXTURE_ADDRESS_BORDER;
//			samplerDesc2.AddressW=D3D11_TEXTURE_ADDRESS_BORDER;
//			samplerDesc2.ComparisonFunc=D3D11_COMPARISON_NEVER;
//			samplerDesc2.BorderColor[0]=1.0f;
//			samplerDesc2.BorderColor[1]=1.0f;
//			samplerDesc2.BorderColor[2]=1.0f;
//			samplerDesc2.BorderColor[3]=1.0f;
//			samplerDesc2.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//			samplerDesc2.MaxAnisotropy=1;
//			samplerDesc2.MaxLOD=FLT_MAX;
//			samplerDesc2.MinLOD=-FLT_MAX;
//			samplerDesc2.MipLODBias=0;
//			ID3D11SamplerState* samplerState2;
//			device->CreateSamplerState(&samplerDesc2,&samplerState2);
//			context->PSSetSamplers(0,1,&samplerState2);
//			samplerState2->Release();
//			vertexBufferDesc.BindFlags=				D3D11_BIND_VERTEX_BUFFER;
//			vertexBufferDesc.CPUAccessFlags=		NULL;
//			vertexBufferDesc.MiscFlags=				NULL;
//			vertexBufferDesc.StructureByteStride=	NULL;
//			vertexBufferDesc.Usage=					D3D11_USAGE_DEFAULT;
//
//			vertexStride=sizeof(float)*9;
//
//			indexDesc.BindFlags=D3D11_BIND_INDEX_BUFFER;
//			indexDesc.CPUAccessFlags=NULL;
//			indexDesc.MiscFlags=NULL;
//			indexDesc.StructureByteStride=NULL;
//			indexDesc.Usage=D3D11_USAGE_DEFAULT;
//
//			
//
//			context->PSSetShader(effects[2].PS,NULL,NULL);
//			context->VSSetShader(effects[2].VS,NULL,NULL);
//			context->IASetInputLayout(effects[2].IA);
//			break;
//		case Grass:
//			D3D11_SAMPLER_DESC samplerDesc3;
//			samplerDesc3.AddressU=D3D11_TEXTURE_ADDRESS_BORDER;
//			samplerDesc3.AddressV=D3D11_TEXTURE_ADDRESS_BORDER;
//			samplerDesc3.AddressW=D3D11_TEXTURE_ADDRESS_BORDER;
//			samplerDesc3.ComparisonFunc=D3D11_COMPARISON_NEVER;
//			samplerDesc3.BorderColor[0]=1.0f;
//			samplerDesc3.BorderColor[1]=1.0f;
//			samplerDesc3.BorderColor[2]=1.0f;
//			samplerDesc3.BorderColor[3]=1.0f;
//			samplerDesc3.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//			samplerDesc3.MaxAnisotropy=1;
//			samplerDesc3.MaxLOD=FLT_MAX;
//			samplerDesc3.MinLOD=-FLT_MAX;
//			samplerDesc3.MipLODBias=0;
//			ID3D11SamplerState* samplerState3;
//			device->CreateSamplerState(&samplerDesc3,&samplerState3);
//			context->PSSetSamplers(0,1,&samplerState3);
//			samplerState3->Release();
//			vertexBufferDesc.BindFlags=				D3D11_BIND_VERTEX_BUFFER;
//			vertexBufferDesc.CPUAccessFlags=		NULL;
//			vertexBufferDesc.MiscFlags=				NULL;
//			vertexBufferDesc.StructureByteStride=	NULL;
//			vertexBufferDesc.Usage=					D3D11_USAGE_DEFAULT;
//
//			vertexStride=sizeof(float)*9;
//
//			indexDesc.BindFlags=D3D11_BIND_INDEX_BUFFER;
//			indexDesc.CPUAccessFlags=NULL;
//			indexDesc.MiscFlags=NULL;
//			indexDesc.StructureByteStride=NULL;
//			indexDesc.Usage=D3D11_USAGE_DEFAULT;
//
//			
//
//			context->PSSetShader(effects[3].PS,NULL,NULL);
//			context->VSSetShader(effects[3].VS,NULL,NULL);
//			context->IASetInputLayout(effects[3].IA);
//			break;
//		case HeightMap:
//			//context->ClearState();
//			//context->RSSetViewports(1,&viewport);
//			D3D11_DEPTH_STENCIL_DESC dsDesc4;
//			//Depth test
//			dsDesc4.DepthEnable = true;
//			dsDesc4.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//			dsDesc4.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
//			dsDesc4.StencilEnable = false;
//			ID3D11DepthStencilState* state4;
//			device->CreateDepthStencilState(&dsDesc4,&state4);
//			context->OMSetDepthStencilState(state4,1);
//
//			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//			D3D11_SAMPLER_DESC samplerDesc4;
//			samplerDesc4.AddressU=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc4.AddressV=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc4.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc4.ComparisonFunc=D3D11_COMPARISON_NEVER;
//			samplerDesc4.BorderColor[0]=1.0f;
//			samplerDesc4.BorderColor[1]=1.0f;
//			samplerDesc4.BorderColor[2]=1.0f;
//			samplerDesc4.BorderColor[3]=1.0f;
//			samplerDesc4.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//			samplerDesc4.MaxAnisotropy=1;
//			samplerDesc4.MaxLOD=FLT_MAX;
//			samplerDesc4.MinLOD=-FLT_MAX;
//			samplerDesc4.MipLODBias=0;
//			ID3D11SamplerState* samplerState4;
//			device->CreateSamplerState(&samplerDesc4,&samplerState4);
//			context->PSSetSamplers(0,1,&samplerState4);
//			samplerState4->Release();
//			vertexBufferDesc.BindFlags=				D3D11_BIND_VERTEX_BUFFER;
//			vertexBufferDesc.CPUAccessFlags=		NULL;
//			vertexBufferDesc.MiscFlags=				NULL;
//			vertexBufferDesc.StructureByteStride=	NULL;
//			vertexBufferDesc.Usage=					D3D11_USAGE_DEFAULT;
//
//			vertexStride=sizeof(int)*2+sizeof(float)*4;
//
//			indexDesc.BindFlags=D3D11_BIND_INDEX_BUFFER;
//			indexDesc.CPUAccessFlags=NULL;
//			indexDesc.MiscFlags=NULL;
//			indexDesc.StructureByteStride=NULL;
//			indexDesc.Usage=D3D11_USAGE_DEFAULT;
//
//			
//
//			context->PSSetShader(effects[4].PS,NULL,NULL);
//			context->VSSetShader(effects[4].VS,NULL,NULL);
//			context->IASetInputLayout(effects[4].IA);
//			break;
//		case SpriteHeightMap:
//			//context->ClearState();
//			//context->RSSetViewports(1,&viewport);
//			
//
//			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//			D3D11_DEPTH_STENCIL_DESC dsDesc5;
//			//Depth test
//			dsDesc5.DepthEnable = true;
//			dsDesc5.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//			dsDesc5.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
//			dsDesc5.StencilEnable = false;
//			
//
//
//			ID3D11DepthStencilState* state5;
//			device->CreateDepthStencilState(&dsDesc5,&state5);
//			context->OMSetDepthStencilState(state5,1);
//
//			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//			D3D11_SAMPLER_DESC samplerDesc5;
//			samplerDesc5.AddressU=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc5.AddressV=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc5.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc5.ComparisonFunc=D3D11_COMPARISON_NEVER;
//			samplerDesc5.BorderColor[0]=1.0f;
//			samplerDesc5.BorderColor[1]=1.0f;
//			samplerDesc5.BorderColor[2]=1.0f;
//			samplerDesc5.BorderColor[3]=1.0f;
//			samplerDesc5.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//			samplerDesc5.MaxAnisotropy=1;
//			samplerDesc5.MaxLOD=FLT_MAX;
//			samplerDesc5.MinLOD=-FLT_MAX;
//			samplerDesc5.MipLODBias=0;
//			ID3D11SamplerState* samplerState5;
//			device->CreateSamplerState(&samplerDesc5,&samplerState5);
//			context->PSSetSamplers(0,1,&samplerState5);
//			samplerState5->Release();
//			vertexBufferDesc.BindFlags=				D3D11_BIND_VERTEX_BUFFER;
//			vertexBufferDesc.CPUAccessFlags=		NULL;
//			vertexBufferDesc.MiscFlags=				NULL;
//			vertexBufferDesc.StructureByteStride=	NULL;
//			vertexBufferDesc.Usage=					D3D11_USAGE_DEFAULT;
//
//			vertexStride=sizeof(float)*4;
//
//			indexDesc.BindFlags=D3D11_BIND_INDEX_BUFFER;
//			indexDesc.CPUAccessFlags=NULL;
//			indexDesc.MiscFlags=NULL;
//			indexDesc.StructureByteStride=NULL;
//			indexDesc.Usage=D3D11_USAGE_DEFAULT;
//
//			blendDesc.AlphaToCoverageEnable=false;
//			blendDesc.IndependentBlendEnable=false;
//			blendDesc.RenderTarget[0].BlendEnable=true;
//			blendDesc.RenderTarget[0].BlendOp=D3D11_BLEND_OP_ADD;
//			blendDesc.RenderTarget[0].BlendOpAlpha=D3D11_BLEND_OP_ADD;
//			blendDesc.RenderTarget[0].DestBlend=D3D11_BLEND_INV_SRC_ALPHA;
//			blendDesc.RenderTarget[0].DestBlendAlpha=D3D11_BLEND_ONE;
//			blendDesc.RenderTarget[0].SrcBlend=D3D11_BLEND_SRC_ALPHA;
//			blendDesc.RenderTarget[0].SrcBlendAlpha=D3D11_BLEND_SRC_ALPHA;
//			blendDesc.RenderTarget[0].RenderTargetWriteMask=D3D11_COLOR_WRITE_ENABLE_ALL;
//			
//			device->CreateBlendState(&blendDesc,&blendState);
//			context->OMSetBlendState(blendState,NULL,0xffffffff);
//
//
//
//			context->PSSetShader(effects[5].PS,NULL,NULL);
//			context->VSSetShader(effects[5].VS,NULL,NULL);
//			context->IASetInputLayout(effects[5].IA);
//			break;
//		case SpriteWrite : 
//			vertexBufferDesc.BindFlags=				D3D11_BIND_VERTEX_BUFFER;
//			vertexBufferDesc.CPUAccessFlags=		NULL;
//			vertexBufferDesc.MiscFlags=				NULL;
//			vertexBufferDesc.StructureByteStride=	NULL;
//			vertexBufferDesc.Usage=					D3D11_USAGE_DEFAULT;
//
//			vertexStride=sizeof(SpriteVertex);
//
//			indexDesc.BindFlags=D3D11_BIND_INDEX_BUFFER;
//			indexDesc.CPUAccessFlags=NULL;
//			indexDesc.MiscFlags=NULL;
//			indexDesc.StructureByteStride=NULL;
//			indexDesc.Usage=D3D11_USAGE_DEFAULT;
//
//			
//
//			context->PSSetShader(effects[6].PS,NULL,NULL);
//			context->VSSetShader(effects[6].VS,NULL,NULL);
//			context->IASetInputLayout(effects[6].IA);
//
//			D3D11_SAMPLER_DESC samplerDesc6;
//			samplerDesc6.AddressU=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc6.AddressV=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc6.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
//			samplerDesc6.ComparisonFunc=D3D11_COMPARISON_NEVER;
//			samplerDesc6.BorderColor[0]=1.0f;
//			samplerDesc6.BorderColor[1]=1.0f;
//			samplerDesc6.BorderColor[2]=1.0f;
//			samplerDesc6.BorderColor[3]=1.0f;
//			samplerDesc6.Filter=D3D11_FILTER_ANISOTROPIC;
//			samplerDesc6.MaxAnisotropy=1;
//			samplerDesc6.MaxLOD=FLT_MAX;
//			samplerDesc6.MinLOD=-FLT_MAX;
//			samplerDesc6.MipLODBias=0;
//			ID3D11SamplerState* samplerState6;
//			device->CreateSamplerState(&samplerDesc6,&samplerState6);
//			context->PSSetSamplers(0,1,&samplerState6);
//			samplerState6->Release();
//
//			
//			blendDesc.AlphaToCoverageEnable=false;
//			blendDesc.IndependentBlendEnable=false;
//			blendDesc.RenderTarget[0].BlendEnable=true;
//			blendDesc.RenderTarget[0].BlendOp=D3D11_BLEND_OP_ADD;
//			blendDesc.RenderTarget[0].BlendOpAlpha=D3D11_BLEND_OP_ADD;
//			blendDesc.RenderTarget[0].DestBlend=D3D11_BLEND_INV_SRC_ALPHA;
//			blendDesc.RenderTarget[0].DestBlendAlpha=D3D11_BLEND_ONE;
//			blendDesc.RenderTarget[0].SrcBlend=D3D11_BLEND_SRC_ALPHA;
//			blendDesc.RenderTarget[0].SrcBlendAlpha=D3D11_BLEND_SRC_ALPHA;
//			blendDesc.RenderTarget[0].RenderTargetWriteMask=D3D11_COLOR_WRITE_ENABLE_ALL;
//			
//			device->CreateBlendState(&blendDesc,&blendState);
//			context->OMSetBlendState(blendState,NULL,0xffffffff);
//						
//			break;
//		default:
//			break;
//	}
//
//void D3DRenderer::DrawInstanced(MemoryBlock vertexData,MemoryBlock indexData,MemoryBlock instanceData)
//{
//	//VertexBuffer
//	vertexBufferDesc.ByteWidth=vertexData.width;
//
//	D3D11_SUBRESOURCE_DATA vertex_data;
//	vertex_data.pSysMem=vertexData.ptr;
//	vertex_data.SysMemPitch=0;
//	vertex_data.SysMemSlicePitch=0;
//	ID3D11Buffer* buffers[2];
//	device->CreateBuffer(&vertexBufferDesc,&vertex_data,&buffers[0]);
//	
//	//IndexBuffer
//	indexDesc.ByteWidth=indexData.width;
//	
//	D3D11_SUBRESOURCE_DATA index_data;
//	index_data.SysMemPitch=0;
//	index_data.SysMemSlicePitch=0;
//	index_data.pSysMem=indexData.ptr;
//	ID3D11Buffer* p_indexBuffer;
//	device->CreateBuffer(&indexDesc,&index_data,&p_indexBuffer);
//
//	UINT offset=0;
//
//	D3D11_BUFFER_DESC instanceBuffer;
//	instanceBuffer.BindFlags=D3D11_BIND_VERTEX_BUFFER;
//	instanceBuffer.ByteWidth=instanceData.width;
//	instanceBuffer.CPUAccessFlags=NULL;
//	instanceBuffer.MiscFlags=NULL;
//	instanceBuffer.StructureByteStride=NULL;
//	instanceBuffer.Usage=D3D11_USAGE_DEFAULT;
//
//	D3D11_SUBRESOURCE_DATA instance_data;
//	instance_data.SysMemPitch=0;
//	instance_data.SysMemSlicePitch=0;
//	instance_data.pSysMem=instanceData.ptr;
//
//	device->CreateBuffer(&instanceBuffer,&instance_data,&buffers[1]);
//
//	UINT strides[2];
//	strides[0]=vertexStride;
//	strides[1]=sizeof(float)*2;
//	
//	UINT offsets[2];
//	offsets[0]=0;
//	offsets[1]=0;
//
//	context->IASetVertexBuffers(0,2,buffers,strides,offsets);
//	context->IASetIndexBuffer(p_indexBuffer,DXGI_FORMAT_R32_UINT,offset);
//
//	context->DrawIndexedInstanced(6,20,0,0,0);
//	buffers[0]->Release();
//	buffers[1]->Release();
//	p_indexBuffer->Release();
//}
//
//
//void D3DRenderer::LoadStates(WCHAR* folder)
//{
//	using namespace std;
//	std::wstring path=folder;
//	
//	//SpriteRender State
//	MemoryBlock bytes;
//	PlatformTools::CreateByteCodeFromFile( (WCHAR*)( path+L"Shaders\\PSSpriteRender.cso").c_str(),&bytes);
//	device->CreatePixelShader(bytes.ptr,bytes.width ,NULL,&effects[0].PS);
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\VSSpriteRender.cso").c_str(),&bytes);
//	device->CreateVertexShader(bytes.ptr,bytes.width ,NULL,&effects[0].VS);
//	D3D11_INPUT_ELEMENT_DESC IA_desc[]=
//	{
//		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"TEXTURE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"TINT",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL}
//	};
//	PlatformTools::CheckFatalError( device->CreateInputLayout(IA_desc,3,bytes.ptr,bytes.width ,&effects[0].IA) );
//
//	//SimpleModel State
//
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\PSSimpleModel.cso").c_str(),&bytes );
//	device->CreatePixelShader(bytes.ptr,bytes.width ,NULL,&effects[1].PS);
//
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\VSSimpleModel.cso").c_str(),&bytes);
//	device->CreateVertexShader(bytes.ptr,bytes.width ,NULL,&effects[1].VS);
//
//	D3D11_INPUT_ELEMENT_DESC IA_desc2[]=
//	{
//		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"TEXTURE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL}
//	};
//	PlatformTools::CheckFatalError( device->CreateInputLayout(IA_desc2,3,bytes.ptr,bytes.width ,&effects[1].IA) );
//
//	//SkyMap State
//
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\PSSkyBox.cso").c_str(),&bytes );
//	device->CreatePixelShader(bytes.ptr,bytes.width ,NULL,&effects[2].PS);
//
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\VSSkyBox.cso").c_str(),&bytes);
//	device->CreateVertexShader(bytes.ptr,bytes.width ,NULL,&effects[2].VS);
//
//	D3D11_INPUT_ELEMENT_DESC IA_desc3[]=
//	{
//		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"TEXTURE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL}
//	};
//	PlatformTools::CheckFatalError( device->CreateInputLayout(IA_desc2,3,bytes.ptr,bytes.width ,&effects[2].IA) );
//
//	//Grass State
//
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\PSInstancedGrass.cso").c_str(),&bytes );
//	device->CreatePixelShader(bytes.ptr,bytes.width ,NULL,&effects[3].PS);
//
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\VSInstancedGrass.cso").c_str(),&bytes);
//	device->CreateVertexShader(bytes.ptr,bytes.width ,NULL,&effects[3].VS);
//
//	D3D11_INPUT_ELEMENT_DESC IA_desc4[]=
//	{
//		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"TEXTURE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"IPOSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,1,0,D3D11_INPUT_PER_INSTANCE_DATA,1}
//	};
//	PlatformTools::CheckFatalError( device->CreateInputLayout(IA_desc4,4,bytes.ptr,bytes.width ,&effects[3].IA) );
//
//	//HeightMap State
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\PSHeightMap.cso").c_str(),&bytes );
//	device->CreatePixelShader(bytes.ptr,bytes.width ,NULL,&effects[4].PS);
//
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\VSHeightMap.cso").c_str(),&bytes);
//	device->CreateVertexShader(bytes.ptr,bytes.width ,NULL,&effects[4].VS);
//
//	D3D11_INPUT_ELEMENT_DESC IA_desc5[]=
//	{
//		{"HEIGHT",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"TEXTURE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		
//	};
//	PlatformTools::CheckFatalError( device->CreateInputLayout(IA_desc5,3,bytes.ptr,bytes.width ,&effects[4].IA) );
//
//	//SpriteHeightMap State
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\PSSpriteHeightMap.cso").c_str(),&bytes );
//	device->CreatePixelShader(bytes.ptr,bytes.width ,NULL,&effects[5].PS);
//
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\VSSpriteHeightMap.cso").c_str(),&bytes);
//	device->CreateVertexShader(bytes.ptr,bytes.width ,NULL,&effects[5].VS);
//
//	D3D11_INPUT_ELEMENT_DESC IA_desc6[]=
//	{
//		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		/*{"ORIENTATION",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},*/
//		{"TEXTURE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"IPOSITION",0,DXGI_FORMAT_R32G32_FLOAT,1,0,D3D11_INPUT_PER_INSTANCE_DATA,1}
//	};
//	PlatformTools::CheckFatalError( device->CreateInputLayout(IA_desc6,  3,bytes.ptr,bytes.width ,&effects[5].IA) );
//
//	//SpriteFont State
//	
//	PlatformTools::CreateByteCodeFromFile( (WCHAR*)( path+L"Shaders\\PSSpriteFont.cso").c_str(),&bytes);
//	device->CreatePixelShader(bytes.ptr,bytes.width ,NULL,&effects[6].PS);
//	PlatformTools::CreateByteCodeFromFile((WCHAR*)( path+L"Shaders\\VSSpriteRender.cso").c_str(),&bytes);
//	device->CreateVertexShader(bytes.ptr,bytes.width ,NULL,&effects[6].VS);
//	D3D11_INPUT_ELEMENT_DESC IA_desc7[]=
//	{
//		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"TEXTURE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL},
//		{"TINT",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,NULL}
//	};
//	PlatformTools::CheckFatalError( device->CreateInputLayout(IA_desc7,3,bytes.ptr,bytes.width ,&effects[6].IA) );
//}