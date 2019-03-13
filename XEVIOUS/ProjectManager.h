#pragma once

#include "SceneManager.h"
#include "DirectX.h"
#include "CustomVertex.h"

class SceneManager;

#include <windows.h>
#include <mmsystem.h>



class ProjectManager
{
public:
	ProjectManager();
	~ProjectManager();
	int MessageLoop();
	void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow);
	void InitDirect3DDevice();
	void InitDinput();
	void SetD3DeviceState();

	DirectX* GetDXInstace()
	{
		return m_pDirectX;
	}

private:
	DirectX * m_pDirectX;
	static HWND m_hWnd;
};

