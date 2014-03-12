#pragma once
#include "Tungsten\States\D3D11CommonState.h"
#include "Tungsten\Camera.h"
#include "Tungsten\Timer.h"
namespace Tungsten
{
	class WaterPhysics : public D3D11CommonState
	{
	public:
		struct Wave
		{
			float2 direction = { 0.0f, 0.0f };
			float phase = 0.0f;
			float freq = 0.0f;
			float amplitude = 0.0f;
			float3 pad;

		};
		void SetWave(Wave& arg, int index);
		Camera* camera;
		void Draw();
		void Apply();
		void InitGrid(int width, int height, int cellsPerUnit = 1);
		WaterPhysics(WCHAR* pShader, WCHAR* vShader);
		~WaterPhysics();
	private:
		Timer animationTimer;
		Wave wavebuffer[4];
		ID3D11PixelShader*	ps;
		ID3D11VertexShader*	vs;
		ID3D11InputLayout*	ia;
		ID3D11SamplerState* ss;
		Texture waterTex;
		struct Vertex
		{
			float x;
			float y;
			//texture
			float u;
			float v;
		};
		struct
		{
			Vertex* vertex = NULL;
			UINT* index = NULL;
		}grid;
		struct
		{
			ID3D11Buffer* vertex;
			ID3D11Buffer* index;
		} buffers;
		struct perFrame
		{
			DirectX::XMMATRIX viewMatrix;
			float time;
			float3 _pad;
		};


	};
}


