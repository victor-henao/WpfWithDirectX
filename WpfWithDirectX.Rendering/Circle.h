#pragma once

#include <d3dx9.h>

struct CustomVertex
{
    float x, y, z;
    DWORD color;
};

class Circle
{
public:
    Circle(LPDIRECT3DDEVICE9 device);
    ~Circle();
    void Draw(LPDIRECT3DDEVICE9 device);
    const D3DXMATRIX& GetTransform();
    void SetPosition(float x, float y, float z);
    void SetScale(float x, float y, float z);
    void SetRotation(float x, float y, float z);

private:
    D3DXVECTOR3 position;
    D3DXVECTOR3 scale;
    D3DXVECTOR3 rotation;
    D3DXMATRIX transorm;
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
};

