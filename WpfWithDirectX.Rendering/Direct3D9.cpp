#include "pch.h"
#include "Direct3D9.h"
#include "Circle.h"
#include <d3dx9.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
const UINT TRIANGLE_COUNT = 32;

D3DPRESENT_PARAMETERS presentParameters;
LPDIRECT3D9 d3dInterface;
LPDIRECT3DDEVICE9 device;
D3DXMATRIX view;
D3DXMATRIX projection;

Circle* circle;

float position = 0;
float rotation = 0;
float scale = 1;

void InitializeGraphics();

void InitializeDirect3D9(HWND windowHandle, UINT width, UINT height)
{
    d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);

    ZeroMemory(&presentParameters, sizeof(D3DPRESENT_PARAMETERS));
    presentParameters.Windowed = true;
    presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    presentParameters.hDeviceWindow = windowHandle;
    presentParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
    presentParameters.BackBufferWidth = width;
    presentParameters.BackBufferHeight = height;

    d3dInterface->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        windowHandle,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &presentParameters,
        &device
    );

    InitializeGraphics();

    device->SetRenderState(D3DRS_LIGHTING, false);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    D3DXMatrixIdentity(&view);
    D3DXMatrixScaling(&view, (float)1 / 16, (float)1 / 16, 1.0f);
    D3DXMatrixIdentity(&projection);
    float ratio = (float)width / height;
    D3DXMatrixOrthoOffCenterLH(&projection, -ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);
}

void RenderDirect3D9()
{
    device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(240, 240, 240), 1.0f, 0);
    device->BeginScene();
    device->SetFVF(CUSTOMFVF);
    
    device->SetTransform(D3DTS_WORLD, &circle->GetTransform());
    device->SetTransform(D3DTS_VIEW, &view);
    //device->SetTransform(D3DTS_PROJECTION, &projection);

    circle->Draw(device);

    device->EndScene();
    device->Present(NULL, NULL, NULL, NULL);
}

void SetCirclePosition(float value)
{
    circle->SetPosition(value, 0, 0);
}

void SetCircleScale(float value)
{
    circle->SetScale(value, value, 0);
}

void SetCircleRotation(float value)
{   
    circle->SetRotation(0, value, 0);
}

void ResizeDirect3D9Viewport(UINT width, UINT height)
{
    presentParameters.BackBufferWidth = width;
    presentParameters.BackBufferHeight = height;

    device->Reset(&presentParameters);
    device->SetRenderState(D3DRS_LIGHTING, false);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    D3DXMatrixIdentity(&projection);
    float ratio = (float)width / height;
    D3DXMatrixOrthoOffCenterLH(&projection, -ratio, ratio, -1.0f, 1.0f, -1.0f, 1.0f);

    device->SetTransform(D3DTS_VIEW, &view);
    device->SetTransform(D3DTS_PROJECTION, &projection);
}

void CleanDirect3D9()
{
    delete circle;
    device->Release();
    d3dInterface->Release();
}

void InitializeGraphics()
{
    circle = new Circle(device);
}
