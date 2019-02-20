#include "DirectX.h"

DirectX* DirectX::m_pInstance = NULL;

DirectX::DirectX()
{
	
}


DirectX::~DirectX()
{

}

DirectX* DirectX::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new DirectX();
	}
	return m_pInstance;
}

void DirectX::DeleteInstence()
{
	delete m_pInstance;
	m_pInstance = NULL;
}

void DirectX::CaptureKeyState()
{
	m_hr = m_pKeyDevice->Acquire();
	m_pKeyDevice->GetDeviceState(sizeof(m_diks), &m_diks);
}

void DirectX::LoadTexture(LPCSTR filePath, std::string textureKey)
{
	D3DXCreateTextureFromFile(
		m_pD3Device,
		filePath,
		&m_pTexture[textureKey]);
}

void DirectX::DrawTexture(std::string textureKey, const CustomVertex* pTextureSize)
{
	m_pD3Device->SetTexture(0, m_pTexture[textureKey]);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, pTextureSize, sizeof(CustomVertex));
}

void DirectX::PrepareDrawing()
{
	//画面の消去
	m_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);
	//描画の開始
	m_pD3Device->BeginScene();
}

void DirectX::FinalizeDrawing()
{
	//描画の終了
	m_pD3Device->EndScene();
	//表示
	m_pD3Device->Present(NULL, NULL, NULL, NULL);
}

void DirectX::InitSquareCustomVertex(CustomVertex initCustomVertex[4],float centerPlayerPosX, float centerPlayerPosY,float size)
{
	InitRectangleCustomVertex(initCustomVertex, centerPlayerPosX,centerPlayerPosY, size, size);
}

void DirectX::InitRectangleCustomVertex(CustomVertex initCustomVertex[4], float centerPlayerPosX, float centerPlayerPosY, float sizeWIDTH, float sizeHEIGHT)
{
	sizeWIDTH = sizeWIDTH / 2;
	sizeHEIGHT = sizeHEIGHT / 2;
	float left = centerPlayerPosX - sizeWIDTH;
	float right = centerPlayerPosX + sizeWIDTH;
	float top = centerPlayerPosY - sizeHEIGHT;
	float bottom = centerPlayerPosY + sizeHEIGHT;
	initCustomVertex[0] = { left, top, 0.f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	initCustomVertex[1] = { right,top, 0.f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	initCustomVertex[2] = { right,bottom, 0.f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	initCustomVertex[3] = { left, bottom, 0.f, 1.f, 0xFFFFFFFF, 0.f, 1.f };
}

void DirectX::MoveCustomVertex(CustomVertex initCustomVertex[4], const D3DXVECTOR2 quantity)
{
	for (int i = 0;i < 4;i++)
	{
		initCustomVertex[i].x += quantity.x;
		initCustomVertex[i].y += quantity.y;
	}
}


bool DirectX::IsKeyPressed(int dik)
{
	if (m_diks[dik] & 0x80)
	{
		return true;
	}
	return false;
}
