#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "3rdParty/MathGeoLib/MathGeoLib.h"

class VertexBuffer
{
public:
    VertexBuffer();

    void AddFloat(float set);
    void AddFloat2(const float2& set);
    void AddFloat3(const float3& set);
    void AddFloat4(const float4& set);

    const float* GetBuffer() const;
    const int GetSize() const;

    void AddSpace(int add);

    void Clear();

private:
    void Resize(int size);
    bool NeedsResize(int new_size);

private:
    float* buffer = nullptr;
    int buffer_size = 0;
    int buffer_used = 0;
};

#endif // VERTEXBUFFER_H
