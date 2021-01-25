#pragma once

#include <d3d9.h>

#define RENDERINGLIBRARY_EXPORTS __declspec(dllexport)

extern "C" RENDERINGLIBRARY_EXPORTS void InitializeDirect3D9(HWND windowHandle);

extern "C" RENDERINGLIBRARY_EXPORTS void RenderDirect3D9();

extern "C" RENDERINGLIBRARY_EXPORTS void SetTrianglePosition(float value);

extern "C" RENDERINGLIBRARY_EXPORTS void SetTriangleRotation(float value);

extern "C" RENDERINGLIBRARY_EXPORTS void SetTriangleScale(float value);

extern "C" RENDERINGLIBRARY_EXPORTS void ResizeDirect3D9Viewport(UINT width, UINT height);

extern "C" RENDERINGLIBRARY_EXPORTS void CleanDirect3D9();