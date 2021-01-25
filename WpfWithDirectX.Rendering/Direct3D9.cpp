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
LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

D3DXMATRIX world;
D3DXMATRIX view;
D3DXMATRIX projection;

float position;
float rotation;
float scale;

void InitializeGraphics();

void InitializeDirect3D9(HWND windowHandle)
{
    d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);

    ZeroMemory(&presentParameters, sizeof(D3DPRESENT_PARAMETERS));
    presentParameters.Windowed = true;
    presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    presentParameters.hDeviceWindow = windowHandle;
    presentParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
    presentParameters.BackBufferWidth = 800;
    presentParameters.BackBufferHeight = 450;

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

    D3DXMatrixIdentity(&world);
    D3DXMatrixIdentity(&view);
    D3DXVECTOR3 cameraPosition(0.0f, 0.0f, -5.0f);
    D3DXVECTOR3 lookAt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
    D3DXMatrixLookAtLH(
        &view,
        &cameraPosition,
        &lookAt,
        &up
    );
    D3DXMatrixIdentity(&projection);
    D3DXMatrixPerspectiveFovLH(
        &projection,
        D3DXToRadian(90),
        (FLOAT)800 / (FLOAT)450,
        0.1f,
        100.0f
    );
}

void RenderDirect3D9()
{
    device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    device->BeginScene();
    device->SetFVF(CUSTOMFVF);
    
    D3DXMATRIX translationMatrix;
    D3DXMATRIX rotationMatrix;
    D3DXMATRIX scaleMatrix;
    D3DXMatrixTranslation(&translationMatrix, position, 0.0f, 0.0f);
    D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(rotation));
    D3DXMatrixScaling(&scaleMatrix, scale, scale, 1);
    world = scaleMatrix * rotationMatrix * translationMatrix;

    device->SetTransform(D3DTS_WORLD, &world);
    device->SetTransform(D3DTS_VIEW, &view);

    device->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
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
    D3DXMatrixPerspectiveFovLH(
        &projection,
        D3DXToRadian(45),
        (FLOAT)width / (FLOAT)height,
        0.1f,
        100.0f
    );
    device->SetTransform(D3DTS_PROJECTION, &projection);
}

void CleanDirect3D9()
{
    vertexBuffer->Release();
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
        &vertexBuffer,
        NULL
    );

    void* voidPointer;
    vertexBuffer->Lock(0, 0, (void**)&voidPointer, 0);
    memcpy(voidPointer, &vertices[0], vertices.size() * sizeof(CustomVertex));
    vertexBuffer->Unlock();
}
