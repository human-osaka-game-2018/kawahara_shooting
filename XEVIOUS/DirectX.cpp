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

//メモリ開放
void DirectX::FreeDx()
{
	m_pTexture.clear();
	std::map<std::string, LPDIRECT3DTEXTURE9>().swap(m_pTexture);
	if (m_pKeyDevice)
	{
		m_pKeyDevice->Unacquire();
	}
	SAFE_RELEASE(m_pD3Device);
	SAFE_RELEASE(m_pDirect3D);
	SAFE_RELEASE(m_pKeyDevice);
	SAFE_RELEASE(m_pDinput);
	DeleteInstence();
}

//ダイレクト3DのDirectX初期化関数
HRESULT DirectX::InitDirect3DDevice(HWND hWnd)
{
	//DirectX オブジェクトの生成
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&m_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));

	//Display Mode の設定
	m_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&m_D3DdisplayMode);
	m_D3dPresentParameters.BackBufferFormat = m_D3DdisplayMode.Format;
	m_D3dPresentParameters.BackBufferCount = 1;
	m_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3dPresentParameters.Windowed = TRUE;

	//デバイスを作る
	m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3dPresentParameters, &m_pD3Device);

	return S_OK;
}

HRESULT DirectX::InitDinput(HWND hWnd)
{
	HRESULT hr;

	//ダイレクトインプットのオブジェの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDinput, NULL)))
	{
		return hr;
	}
	//ダイレクトインプットのデバイスの作成
	if (FAILED(hr = m_pDinput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice, NULL)))
	{
		return hr;
	}
	//デバイスをキーボードの設定
	if (FAILED(hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//協調レベル
	if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	return S_OK;
}

void DirectX::SetD3DeviceState()
{
	ZeroMemory(&m_D3dPresentParameters, sizeof(D3DPRESENT_PARAMETERS));

	m_D3dPresentParameters.BackBufferFormat = m_D3DdisplayMode.Format;
	m_D3dPresentParameters.BackBufferCount = 1;
	m_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3dPresentParameters.Windowed = TRUE;

	//描画設定
	m_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//SRCの設定
	m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//頂点に入れるデータを設定
	m_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
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

void DirectX::InitSquareCustomVertex(CustomVertex initCustomVertex[4], float centerPlayerPosX, float centerPlayerPosY, float size)
{
	InitRectangleCustomVertex(initCustomVertex, centerPlayerPosX, centerPlayerPosY, size, size);
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

bool DirectX::CustomVertexCollision(CustomVertex FirstCustomVertex[4], CustomVertex SecondCustomVertex[4])
{
	if (FirstCustomVertex[0].x <= SecondCustomVertex[2].x  && SecondCustomVertex[0].x <= FirstCustomVertex[2].x)
	{
		if (FirstCustomVertex[0].y <= SecondCustomVertex[2].y && SecondCustomVertex[0].y <= FirstCustomVertex[2].y)
		{
			return true;
		}
	}
	return false;
}
