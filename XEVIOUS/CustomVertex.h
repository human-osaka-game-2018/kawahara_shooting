#pragma once

#include <windows.h>

struct CustomVertex
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};
