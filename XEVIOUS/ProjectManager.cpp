#include "ProjectManager.h"


ProjectManager::ProjectManager()
{
	m_pDirectX = DirectX::GetInstance();
}

ProjectManager::~ProjectManager()
{
	FreeDx();
}


int ProjectManager::MessageLoop()
{
	SceneManager SceneManager;
	MSG msg;
	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;
	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60)//1秒間に60回この中に入るはず
			{
				//キー情報の取得に必要
				m_pDirectX->CaptureKeyState();

				//シーンのUpdate
				SceneManager.Update();

				//描画の準備
				m_pDirectX->PrepareDrawing();
				//シーンのRender
				SceneManager.Render();
				//描画の終わり
				m_pDirectX->FinalizeDrawing();

				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);
	return (int)msg.wParam;
}


//メッセージ処理
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

//メモリ開放
void ProjectManager::FreeDx()
{
	m_pDirectX->m_pTexture.clear();
	std::map<std::string, LPDIRECT3DTEXTURE9>().swap(m_pDirectX->m_pTexture);
	if (m_pDirectX->m_pKeyDevice)
	{
		m_pDirectX->m_pKeyDevice->Unacquire();
	}
	SAFE_RELEASE(m_pDirectX->m_pD3Device);
	SAFE_RELEASE(m_pDirectX->m_pDirect3D);
	SAFE_RELEASE(m_pDirectX->m_pKeyDevice);
	SAFE_RELEASE(m_pDirectX->m_pDinput);
	m_pDirectX->DeleteInstence();
}

//ダイレクト3DのDirectX初期化関数
HRESULT ProjectManager::InitDirect3DDevice(HWND hWnd)
{
	//DirectX オブジェクトの生成
	m_pDirectX->m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&m_pDirectX->m_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));

	//Display Mode の設定
	m_pDirectX->m_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&m_pDirectX->m_D3DdisplayMode);
	m_pDirectX->m_D3dPresentParameters.BackBufferFormat = m_pDirectX->m_D3DdisplayMode.Format;
	m_pDirectX->m_D3dPresentParameters.BackBufferCount = 1;
	m_pDirectX->m_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pDirectX->m_D3dPresentParameters.Windowed = TRUE;

	//デバイスを作る
	m_pDirectX->m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_pDirectX->m_D3dPresentParameters, &m_pDirectX->m_pD3Device);

	return S_OK;
}

HRESULT ProjectManager::InitDinput(HWND hWnd)
{
	HRESULT hr;

	//ダイレクトインプットのオブジェの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDirectX->m_pDinput, NULL)))
	{
		return hr;
	}
	//ダイレクトインプットのデバイスの作成
	if (FAILED(hr = m_pDirectX->m_pDinput->CreateDevice(GUID_SysKeyboard,
		&m_pDirectX->m_pKeyDevice, NULL)))
	{
		return hr;
	}
	//デバイスをキーボードの設定
	if (FAILED(hr = m_pDirectX->m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//協調レベル
	if (FAILED(hr = m_pDirectX->m_pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	return S_OK;
}

//メインルーチン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	ProjectManager pProjectManager;

	WNDCLASS Wndclass;
	HWND hWnd;

	//Windows情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TEXT("XEVIOUS");	//クラス名
												//Windowの登録
	RegisterClass(&Wndclass);
	//Windowの生成
	hWnd = CreateWindow(
		TEXT("XEVIOUS"),								//ウィンドウのクラス名
		TEXT("XEVIOUS"), 							//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		DISPLAY_WIDTH,							// Width（幅）
		DISPLAY_HEIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);

	RECT window;
	RECT client;
	// ウィンドウ領域矩形取得
	GetWindowRect(hWnd, &window);
	// クライアント領域矩形取得
	GetClientRect(hWnd, &client);
	// ウィンドウ外枠のサイズ
	int window_size_x = (window.right - window.left);
	int window_size_y = (window.bottom - window.top);
	int client_size_x = (client.right - client.left);
	int client_size_y = (client.bottom - client.top);
	int frame_size_x = window_size_x - client_size_x;
	int frame_size_y = window_size_y - client_size_y;

	// ウィンドウサイズ再設定
	SetWindowPos(
		// ウィンドウハンドル
		hWnd,
		// 配置順序のハンドル(NULLでよし)
		NULL,
		// 表示座標X
		CW_USEDEFAULT,
		// 表示座標Y
		CW_USEDEFAULT,
		// 新規クライアントサイズ(横)		
		frame_size_x + DISPLAY_WIDTH,
		// 新規クライアントサイズ(縦)
		frame_size_y + DISPLAY_HEIGHT,
		// SWP_NOMOVE => 位置変更なし
		SWP_NOMOVE);
	// ウィンドウ表示
	ShowWindow(hWnd, SW_SHOW);
	// クライアント領域更新
	UpdateWindow(hWnd);
	if (!hWnd) return 0;

	pProjectManager.InitDirect3DDevice(hWnd);


	//DirectX オブジェクトの生成
	if (NULL == (pProjectManager.m_pDirectX->m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0,"DirectXの作成に失敗しました","",MB_OK);
		return -1;
	}

	ZeroMemory(&pProjectManager.m_pDirectX->m_D3dPresentParameters,sizeof(D3DPRESENT_PARAMETERS));

	pProjectManager.m_pDirectX->m_D3dPresentParameters.BackBufferFormat = pProjectManager.m_pDirectX->m_D3DdisplayMode.Format;
	pProjectManager.m_pDirectX->m_D3dPresentParameters.BackBufferCount = 1;
	pProjectManager.m_pDirectX->m_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pProjectManager.m_pDirectX->m_D3dPresentParameters.Windowed = TRUE;
				   
	//デバイスを作る
	pProjectManager.m_pDirectX->m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pProjectManager.m_pDirectX->m_D3dPresentParameters, &pProjectManager.m_pDirectX->m_pD3Device);
	//DirectInputの初期化
	if (pProjectManager.InitDinput(hWnd) != S_OK)
	{
		pProjectManager.FreeDx();
		MessageBox(0, "DirectInputの初期化に失敗しました", "", MB_OK);
		return -1;
	}

	//描画設定
	pProjectManager.m_pDirectX->m_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pProjectManager.m_pDirectX->m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//SRCの設定
	pProjectManager.m_pDirectX->m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pProjectManager.m_pDirectX->m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pProjectManager.m_pDirectX->m_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	pProjectManager.m_pDirectX->m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pProjectManager.m_pDirectX->m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//頂点に入れるデータを設定
	pProjectManager.m_pDirectX->m_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	pProjectManager.MessageLoop();
}
