#include "ProjectManager.h"


ProjectManager::ProjectManager()
{
	
}

ProjectManager::~ProjectManager()
{

}

void ProjectManager::PrepareDrawing()
{
	//画面の消去
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);
	//描画の開始
	g_pD3Device->BeginScene();
}

void ProjectManager::FinalizeDrawing()
{
	//描画の終了
	g_pD3Device->EndScene();
	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
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
				//シーンのUpdate
				SceneManager.Update();

				//描画の準備
				PrepareDrawing();
				//シーンのRender
				SceneManager.Render();
				//描画の終わり
				FinalizeDrawing();

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
void FreeDx()
{
	for (int i = 0; i <= TEXMAX; i++)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}
	SAFE_RELEASE(g_pD3Device);
	SAFE_RELEASE(g_pDirect3D);
}

//ダイレクト3Dの初期化関数
HRESULT InitDirect3DDevice(HWND hWnd)
{
	//DirectX オブジェクトの生成
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&g_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));

	//Display Mode の設定
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = TRUE;

	//デバイスを作る
	g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3dPresentParameters, &g_pD3Device);

	return S_OK;
}

//メインルーチン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	ProjectManager* pProjectManager = new ProjectManager();

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

	InitDirect3DDevice(hWnd);

	//描画設定
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//SRCの設定
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//頂点に入れるデータを設定
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);


	//フォントオブジェクトの作成
	D3DXCreateFont(
		g_pD3Device,				// Direct3Dデバイス
		100,						// 高さ 表示する文字の大きさ
		100,					// 幅　表示する文字の大きさ
		FW_REGULAR,				// フォントの太さ 普通
		NULL,					// 下線
		FALSE,					// 斜体
		SHIFTJIS_CHARSET,		// 文字セット
		OUT_DEFAULT_PRECIS,		// 出力制度は普通
		PROOF_QUALITY,			// 文字品質を重視
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリ
		TEXT("ＭＳ　Ｐゴシック"),	// フォント名
		&pFont);					// ID3DXFontポインタ

	pProjectManager->MessageLoop();
}


