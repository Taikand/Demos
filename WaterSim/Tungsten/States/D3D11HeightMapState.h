#pragma once
#include "D3D11CommonState.h"
#include "HeightMapGrid.h"

#include "..\Vector.h"
#include "..\Camera.h"
namespace Tungsten
{

	class D3D11HeightMapState :
		public D3D11CommonState
	{
	private:
		HeightMapGrid* grid;
		
		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* layout;
		

		ID3D11Buffer* mapBuffer;
		ID3D11Buffer* indexBuffer;
		ID3D11Buffer* heightNormBuffer;

	public:
		struct
		{
			Vector<4> lightDir;
			Vector<4> ambientLight;
			Vector<4> diffuseLight;
			Vector<4> specularLight;
		}light;

		Tungsten::Texture map;
		Tungsten::Texture terrain;
		void Apply();
		void SetGrid(Vector<2, int> cellCount, Vector<2, int> textureRes, int textureStep, float heightNorm, float scaleFactor);
		void Draw(Camera& perspective);
		D3D11HeightMapState(const WCHAR* pShader,const WCHAR* vShader);
		~D3D11HeightMapState();
	};

}