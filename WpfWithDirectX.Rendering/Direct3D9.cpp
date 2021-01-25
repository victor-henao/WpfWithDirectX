#include "pch.h"
#include "Direct3D9.h"
#include <d3dx9.h>

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct CustomVertex
{
    float x, y, z;
    DWORD color;
};

D3DPRESENT_PARAMETERS presentParameters;
LPDIRECT3D9 d3dInterface;
LPDIRECT3DDEVICE9 device;
LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
D3DXMATRIX view;
D3DXMATRIX world;
D3DXMATRIX projection;

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
    D3DXVECTOR3 cameraPosition(0.0f, 0.0f, 5.0f);
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
        D3DXToRadian(45),
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
    
    device->SetTransform(D3DTS_WORLD, &world);
    device->SetTransform(D3DTS_VIEW, &view);

    device->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
    device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
    device->EndScene();
    device->Present(NULL, NULL, NULL, NULL);
}

void SetTriangleRotation(float value)
{   
    D3DXMatrixRotationY(&world, D3DXToRadian(value));
    device->SetTransform(D3DTS_WORLD, &world);
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
    CustomVertex vertices[] =
    {
        { 0.0, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0) },
        { -1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0) },
        { 1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255) }
    };

    device->CreateVertexBuffer(
        3 * sizeof(CustomVertex),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        NULL
    );

    void* voidPointer;
    vertexBuffer->Lock(0, 0, (void**)&voidPointer, 0);
    memcpy(voidPointer, vertices, sizeof(vertices));
    vertexBuffer->Unlock();
}
