#include "ProjectManager.h"

HWND ProjectManager::m_hWnd;

ProjectManager::ProjectManager()
{
	m_pDirectX = DirectX::GetInstance();
}

ProjectManager::~ProjectManager()
{
	m_pDirectX->FreeDx();
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


void ProjectManager::InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS Wndclass;

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
	m_hWnd = CreateWindow(
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
	GetWindowRect(m_hWnd, &window);
	// クライアント領域矩形取得
	GetClientRect(m_hWnd, &client);
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
		m_hWnd,
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
	ShowWindow(m_hWnd, SW_SHOW);
	// クライアント領域更新
	UpdateWindow(m_hWnd);
}

void ProjectManager::InitDirect3DDevice()
{
	GetDXInstace()->InitDirect3DDevice(m_hWnd);
}

void ProjectManager::InitDinput()
{
	GetDXInstace()->InitDinput(m_hWnd);
}

void ProjectManager::SetD3DeviceState()
{
	GetDXInstace()->SetD3DeviceState();
}

//メインルーチン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	ProjectManager pProjectManager;
	pProjectManager.InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	pProjectManager.InitDirect3DDevice();
	pProjectManager.InitDinput();
	pProjectManager.SetD3DeviceState();
	pProjectManager.MessageLoop();
}