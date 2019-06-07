#ifndef MESH_H
#define MESH_H

#include <vector>
#include "globals.h"
#include "Renderers/vertexbuffer.h"

class SubMesh
{
    friend class MeshManager;
    friend class DefaultRenderer;

public:
    SubMesh();

    void CleanUp();

    void LoadToVRAM();
    void UnloadFromVRAM();

    int GetLoaded() const;

    int GetVao() const;
    int GetVbo() const;
    int GetVbio() const;

    int GetElementsCount();

private:
    std::vector<float> vertex_buffer;
    std::vector<uint> index_buffer;

    bool has_uvs = false;

    bool loaded = false;

    int vao = 0;
    int vbo = 0;
    int vbio = 0;
};

class Mesh
{
    friend class MeshManager;
    friend class DefaultRenderer;

private:
    Mesh();
    void operator delete(void *) {}

public:
    std::vector<SubMesh*> GetSubMeshes() const;

private:
    std::vector<SubMesh*> sub_meshes;
};

#endif // MESH_H
