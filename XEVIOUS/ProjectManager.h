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
	DirectX* m_pDirectX;
	HRESULT InitDirect3DDevice(HWND hWnd);
	HRESULT InitDinput(HWND hWnd);
	void FreeDx();

private:

};

