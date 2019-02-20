#pragma once

#include "CustomVertex.h"

#include <stdlib.h>
#include <map>
#include <d3dx9.h>
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")


#define DISPLAY_WIDTH 640.f
#define DISPLAY_HEIGHT 480.f
#define MARGIN 128.f

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}


class DirectX
{
public:
	//Directx関係
	std::map<std::string, LPDIRECT3DTEXTURE9> m_pTexture; //画像の情報を入れておく為のポインタ配列
	IDirect3DDevice9*	  m_pD3Device; //Direct3Dのデバイス
	D3DPRESENT_PARAMETERS m_D3dPresentParameters;		//	パラメータ
	D3DDISPLAYMODE		  m_D3DdisplayMode;
	IDirect3D9*			  m_pDirect3D;		//	Direct3Dのインターフェイス
	LPDIRECTINPUTDEVICE8 m_pKeyDevice;
	LPDIRECTINPUT8 m_pDinput;
	HRESULT m_hr;
	BYTE m_diks[256];

	//singleton関係
	static DirectX* GetInstance();

	void LoadTexture(LPCSTR filePath, std::string textureKey);
	void DrawTexture(std::string textureKey, const CustomVertex* ptextureSize);
	void PrepareDrawing();
	void FinalizeDrawing();
	//正方形のCustomVertexを設定する
	void InitSquareCustomVertex(CustomVertex initCustomVertex[4],float centerPlayerPosX, float centerPlayerPosY,float size);
	//長方形のCustomVertexを設定する
	void InitRectangleCustomVertex(CustomVertex initCustomVertex[4], float centerPlayerPosX, float centerPlayerPosY, float sizeWIDTH, float sizeHEIGHT);
	void MoveCustomVertex(CustomVertex initCustomVertex[4], const D3DXVECTOR2 quantity);
	bool IsKeyPressed(int dik);
	void CaptureKeyState();
	void DeleteInstence();

private:
	DirectX();
	~DirectX();
	static DirectX* m_pInstance;
};
