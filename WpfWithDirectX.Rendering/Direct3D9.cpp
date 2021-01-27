#include "pch.h"
#include "Direct3D9.h"
#include <d3dx9.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
const UINT TRIANGLE_COUNT = 32;

struct CustomVertex
{
    float x, y, z;
    DWORD color;
};

D3DPRESENT_PARAMETERS presentParameters;
LPDIRECT3D9 d3dInterface;
LPDIRECT3DDEVICE9 device;
LPDIRECT3DVERTEXBUFFER9 vertexBuffer1;
LPDIRECT3DVERTEXBUFFER9 vertexBuffer2;

D3DXMATRIX world1;
D3DXMATRIX world2;
D3DXMATRIX view;
D3DXMATRIX projection;

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

    D3DXMatrixIdentity(&world1);
    D3DXMatrixIdentity(&world2);
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
    
    D3DXMATRIX translationMatrix1;
    D3DXMATRIX rotationMatrix1;
    D3DXMATRIX scaleMatrix1;
    D3DXMatrixTranslation(&translationMatrix1, position, 0.0f, 0.0f);
    D3DXMatrixRotationY(&rotationMatrix1, D3DXToRadian(rotation));
    D3DXMatrixScaling(&scaleMatrix1, scale, scale, 1);
    world1 = rotationMatrix1 * scaleMatrix1 * translationMatrix1;

    device->SetTransform(D3DTS_WORLD, &world1);
    device->SetTransform(D3DTS_VIEW, &view);
    device->SetTransform(D3DTS_PROJECTION, &projection);

    device->SetStreamSource(0, vertexBuffer1, 0, sizeof(CustomVertex));
    device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, TRIANGLE_COUNT);

    D3DXMATRIX translationMatrix2;
    D3DXMATRIX rotationMatrix2;
    D3DXMATRIX scaleMatrix2;
    D3DXMatrixTranslation(&translationMatrix2, 5.0f, 0.0f, 0.0f);
    D3DXMatrixRotationY(&rotationMatrix2, D3DXToRadian(0));
    D3DXMatrixScaling(&scaleMatrix2, 2, 2, 1);
    world2 = rotationMatrix2 * scaleMatrix2 * translationMatrix2;

    device->SetTransform(D3DTS_WORLD, &world2);
    device->SetTransform(D3DTS_VIEW, &view);
    device->SetTransform(D3DTS_PROJECTION, &projection);

    device->SetStreamSource(0, vertexBuffer2, 0, sizeof(CustomVertex));
    device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, TRIANGLE_COUNT);

    device->EndScene();
    device->Present(NULL, NULL, NULL, NULL);
}

void SetTrianglePosition(float value)
{
    position = value;
}

void SetTriangleRotation(float value)
{   
    rotation = value;
}

void SetTriangleScale(float value)
{
    scale = value;
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

    device->SetTransform(D3DTS_PROJECTION, &projection);
}

void CleanDirect3D9()
{
    vertexBuffer1->Release();
    vertexBuffer2->Release();
    device->Release();
    d3dInterface->Release();
}

void InitializeGraphics()
{
    std::vector<CustomVertex> vertices;
    vertices.push_back({ 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255) });
    for (float angle = 0; angle < 2 * (float)M_PI; angle += 2 * (float)M_PI / TRIANGLE_COUNT)
    {
        vertices.push_back({ std::cosf(angle), std::sinf(angle), 0.0f, D3DCOLOR_XRGB(255, 255, 255) });
    }
    vertices.push_back({ 1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255) });

    device->CreateVertexBuffer(
        vertices.size() * sizeof(CustomVertex),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &vertexBuffer1,
        NULL
    );

    device->CreateVertexBuffer(
        vertices.size() * sizeof(CustomVertex),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &vertexBuffer2,
        NULL
    );

    void* bufferData1;
    vertexBuffer1->Lock(0, 0, &bufferData1, 0);
    memcpy(bufferData1, &vertices[0], vertices.size() * sizeof(CustomVertex));
    vertexBuffer1->Unlock();

    void* bufferData2;
    vertexBuffer2->Lock(0, 0, &bufferData2, 0);
    memcpy(bufferData2, &vertices[0], vertices.size() * sizeof(CustomVertex));
    vertexBuffer2->Unlock();
}
