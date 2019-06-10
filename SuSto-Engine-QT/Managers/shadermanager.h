#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <vector>

class Shader;
class ShaderProgram;
class Mesh;
enum ShaderType;

class ShaderManager
{
    friend class AppManager;

private:
    ShaderManager();
    void operator delete(void *) {}

public:
    static ShaderManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new ShaderManager();
        }

        return instance;
    }

    static void DestroyInstance()
    {
        if(instance != nullptr)
        {
            instance->CleanUp();

            delete instance;

            instance = nullptr;
        }
    }

public:
    void Start();
    void CleanUp();

    Shader* CreateShader(ShaderType type);
    void DestroyShader(Shader* sh);

    ShaderProgram* CreateShaderProgram();
    void DestroyShaderProgram(ShaderProgram* sp);

    Shader* LoadShaderFromFile(const std::string& filepath, ShaderType type);
    std::string GetShadersBaseFolder() const;

private:
    void DestroyAllShaders();
    void DestroyAllShaderPrograms();

private:
    std::vector<Shader*> shaders;
    std::vector<ShaderProgram*> programs;

private:
    static ShaderManager* instance;
};

class ShaderProgramParameters;

enum ShaderType
{
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    UNDEFINED,
};

class Shader
{
    friend class ShaderManager;

private:
    void operator delete(void *) {}

public:
    Shader(ShaderType type);

    void CleanUp();

    bool SetShaderCode(const char* code);
    const char* GetShaderCode() const;

    bool GetCompiles() const;
    const char* GetCompilationError();
    int GetID() const;
    ShaderType GetType() const;

private:
    ShaderType type = ShaderType::UNDEFINED;
    std::string shader_code;
    bool compiles = false;
    std::string compilation_error;
    int id = 0;
};


class ShaderProgram
{
    friend class ShaderManager;

private:
    void operator delete(void *) {}

public:
    ShaderProgram();

    void CleanUp();

    void AddShader(Shader* set);
    void RemoveShader(Shader* sh);
    void RemoveShaders();

    bool LinkProgram();
    void UseProgram();
    void StopUsingProgram();
    void SetProgramParameters(ShaderProgramParameters para);

    std::vector<Shader*> GetVertexShaders() const;
    std::vector<Shader*> GetFragmentShaders() const;
    std::vector<Shader*> GetGeometryShaders() const;

    bool GetLinked() const;
    const char* GetLinkError() const;

    int GetID() const;

private:
    void UnlinkProgram();


private:
    int id = 0;

    std::vector<Shader*> vertex_shaders;
    std::vector<Shader*> fragment_shaders;
    std::vector<Shader*> geometry_shaders;

    bool linked = false;
    std::string link_error;
};

#endif // SHADERMANAGER_H
