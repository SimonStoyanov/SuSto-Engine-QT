#include "indexbuffer.h"

IndexBuffer::IndexBuffer()
{

}

void IndexBuffer::AddInt(int set)
{
    if(NeedsResize(buffer_used + 1))
        AddSpace(1);

    buffer[buffer_used] = set;

    buffer_used += 1;
}

const float * VertexBuffer::GetBuffer() const
{
    return buffer;
}

const int VertexBuffer::GetSize() const
{
    return (sizeof(float) * buffer_size);
}

void VertexBuffer::Clear()
{
    delete[](buffer);
    buffer_size = 0;
    buffer_used = 0;
}

void VertexBuffer::Resize(int size)
{
    float* new_buffer = new float[size];

    if (buffer != nullptr)
    {
        memcpy(new_buffer, buffer, buffer_size * sizeof(float));

        delete[](buffer);
    }

    buffer = new_buffer;

    buffer_size = size;
}

void VertexBuffer::AddSpace(int add)
{
    Resize(buffer_size + add);
}

bool VertexBuffer::NeedsResize(int new_size)
{
    bool ret = false;

    if (new_size > buffer_size)
        ret = true;

    return ret;
}
