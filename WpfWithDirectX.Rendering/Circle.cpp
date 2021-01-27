#include "pch.h"
#include "Circle.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
const UINT TRIANGLE_COUNT = 32;

Circle::Circle(LPDIRECT3DDEVICE9 device) :
    position(0, 0, 0),
    scale(1, 1, 1),
    rotation(0, 0, 0)
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

    void* bufferData;
    vertexBuffer->Lock(0, 0, &bufferData, 0);
    memcpy(bufferData, &vertices[0], vertices.size() * sizeof(CustomVertex));
    vertexBuffer->Unlock();

    D3DXMatrixIdentity(&transorm);
}

Circle::~Circle()
{
    vertexBuffer->Release();
}

void Circle::Draw(LPDIRECT3DDEVICE9 device)
{
    device->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
    device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, TRIANGLE_COUNT);
}

const D3DXMATRIX& Circle::GetTransform()
{
    D3DXMATRIX translationMatrix;
    D3DXMATRIX scaleMatrix;
    D3DXMATRIX rotationXMatrix;
    D3DXMATRIX rotationYMatrix;
    D3DXMATRIX rotationZMatrix;

    D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);
    D3DXMatrixScaling(&scaleMatrix, scale.x, scale.y, scale.z);
    D3DXMatrixRotationX(&rotationXMatrix, D3DXToRadian(rotation.x));
    D3DXMatrixRotationY(&rotationYMatrix, D3DXToRadian(rotation.y));
    D3DXMatrixRotationZ(&rotationZMatrix, D3DXToRadian(rotation.z));

    return rotationXMatrix * rotationYMatrix * rotationZMatrix * scaleMatrix * translationMatrix;;
}

void Circle::SetPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Circle::SetScale(float x, float y, float z)
{
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

void Circle::SetRotation(float x, float y, float z)
{
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}
