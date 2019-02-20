#pragma once

#include "SceneManager.h"

class SceneManager;

#include <windows.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <stdlib.h>


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}
#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGHT 480


struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};

enum TEXTURE
{
	NO_TEX,
	TEXMAX
};

//Directx関係
LPDIRECT3DTEXTURE9 g_pTexture[TEXMAX]; //画像の情報を入れておく為のポインタ配列
IDirect3DDevice9*  g_pD3Device; //Direct3Dのデバイス
D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
D3DDISPLAYMODE		  g_D3DdisplayMode;
LPD3DXFONT	pFont;
IDirect3D9*			  g_pDirect3D;		//	Direct3Dのインターフェイス



class ProjectManager
{
public:
	ProjectManager();
	~ProjectManager();
	int MessageLoop();
	void PrepareDrawing();
	void FinalizeDrawing();

private:


};
