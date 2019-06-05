#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer
{
public:
    IndexBuffer();

    void AddInt(int set);

    const int* GetBuffer() const;
    const int GetSize() const;

    void AddSpace(int add);

    void Clear();

private:
    void Resize(int size);
    bool NeedsResize(int new_size);

private:
    int* buffer = nullptr;
    int buffer_size = 0;
    int buffer_used = 0;
};

#endif // INDEXBUFFER_H
