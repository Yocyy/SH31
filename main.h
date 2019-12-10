#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")

//stb-master
#include <stb-master/stb_image.h>
#include <stb-master/stb_image_write.h>

#define SCREEN_WIDTH	(960)			// ウインドウの幅
#define SCREEN_HEIGHT	(540)			// ウインドウの高さ

#define VS_FILEPATH "./x64/Debug/shader2DTestVS.cso"
#define PS_FILEPATH "./x64/Debug/shader2DTestPS.cso"

HWND GetWindow();
