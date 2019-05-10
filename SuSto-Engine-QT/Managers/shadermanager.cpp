#include "shadermanager.h"
#include "Managers/rendermanager.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager()
{

}

void ShaderManager::Start()
{

}

void ShaderManager::CleanUp()
{
    DestroyAllShaderPrograms();
    DestroyAllShaders();
}

Shader *ShaderManager::CreateShader(ShaderType type)
{
    Shader* shader = new Shader(type);

    shaders.push_back(shader);

    return shader;
}

void ShaderManager::DestroyShader(Shader *sh)
{
    if (sh != nullptr)
        {
            for (std::vector<Shader*>::iterator it = shaders.begin(); it != shaders.end(); ++it)
            {
                if ((*it) == sh)
                {
                    for (std::vector<ShaderProgram*>::iterator pro = programs.begin(); pro != programs.end(); ++pro)
                    {
                        (*pro)->RemoveShader((*it));
                    }

                    (*it)->CleanUp();
                    delete(*it);

                    shaders.erase(it);
                    break;
                }
            }
        }
}

ShaderProgram *ShaderManager::CreateShaderProgram()
{
    ShaderProgram* program = new ShaderProgram();

    programs.push_back(program);

    return program;
}

void ShaderManager::DestroyShaderProgram(ShaderProgram *sp)
{
    if (sp != nullptr)
    {
        for (std::vector<ShaderProgram*>::iterator it = programs.begin(); it != programs.end(); ++it)
        {
            if ((*it) == sp)
            {
                (*it)->CleanUp();

                delete(*it);

                programs.erase(it);
                break;
            }
        }
    }
}

void ShaderManager::DestroyAllShaders()
{
    for (std::vector<Shader*>::iterator it = shaders.begin(); it != shaders.end(); ++it)
    {
        (*it)->CleanUp();

        delete(*it);
    }

    shaders.clear();
}

void ShaderManager::DestroyAllShaderPrograms()
{
    for (std::vector<ShaderProgram*>::iterator it = programs.begin(); it != programs.end(); ++it)
    {
        (*it)->CleanUp();

        delete(*it);
    }

    programs.clear();
}

// --------------------------------------------------


Shader::Shader(ShaderType _type)
{
    type = _type;
}

void Shader::CleanUp()
{
    if (id > 0)
    {
        RenderManager::Instance()->DeleteShader(id);

        id = 0;
    }
}

bool Shader::SetShaderCode(const char * code)
{
    bool ret = false;

    if (id > 0)
        RenderManager::Instance()->DeleteShader(id);

    id = 0;
    compiles = false;

    switch (type)
    {
    case ShaderType::VERTEX:
        id = RenderManager::Instance()->CreateVertexShader(code, compilation_error);
        break;
    case ShaderType::FRAGMENT:
        id = RenderManager::Instance()->CreateFragmentShader(code, compilation_error);
        break;
    case ShaderType::GEOMETRY:
        id = RenderManager::Instance()->CreateGeometryShader(code, compilation_error);
    }

    if (id > 0)
    {
        compiles = true;
        ret = true;
    }

    return ret;
}

const char * Shader::GetShaderCode() const
{
    return shader_code.c_str();
}

bool Shader::GetCompiles() const
{
    return compiles;
}

const char * Shader::GetCompilationError()
{
    return compilation_error.c_str();
}

int Shader::GetID() const
{
    return id;
}

ShaderType Shader::GetType() const
{
    return type;
}

// --------------------------------------------------

ShaderProgram::ShaderProgram()
{
}

void ShaderProgram::CleanUp()
{
    if (id > 0)
    {
        RenderManager::Instance()->DeleteProgram(id);

        id = 0;
    }
}

void ShaderProgram::AddShader(Shader * set)
{
    if (set != nullptr)
    {
        switch (set->GetType())
        {
        case ShaderType::VERTEX:
            vertex_shaders.push_back(set);
            break;
        case ShaderType::FRAGMENT:
            fragment_shaders.push_back(set);
            break;
        case ShaderType::GEOMETRY:
            geometry_shaders.push_back(set);
            break;
        }

        UnlinkProgram();
    }
}

void ShaderProgram::RemoveShader(Shader * sh)
{
    if (sh != nullptr)
    {
        switch (sh->GetType())
        {
        case ShaderType::VERTEX:
            for (std::vector<Shader*>::iterator it = vertex_shaders.begin(); it != vertex_shaders.end(); ++it)
            {
                if ((*it) == sh)
                {
                    vertex_shaders.erase(it);
                    break;
                }
            }
            break;
        case ShaderType::FRAGMENT:
            for (std::vector<Shader*>::iterator it = fragment_shaders.begin(); it != fragment_shaders.end(); ++it)
            {
                if ((*it) == sh)
                {
                    fragment_shaders.erase(it);
                    break;
                }
            }
            break;
        case ShaderType::GEOMETRY:
            for (std::vector<Shader*>::iterator it = geometry_shaders.begin(); it != geometry_shaders.end(); ++it)
            {
                if ((*it) == sh)
                {
                    geometry_shaders.erase(it);
                    break;
                }
            }
            break;
        }

        UnlinkProgram();
    }
}

void ShaderProgram::RemoveShaders()
{
    vertex_shaders.clear();
    fragment_shaders.clear();
    geometry_shaders.clear();

    UnlinkProgram();
}

bool ShaderProgram::LinkProgram()
{
    bool ret = false;

    UnlinkProgram();

    if (vertex_shaders.size() > 0 && fragment_shaders.size() > 0)
    {
        bool all_compile = true;

        for (std::vector<Shader*>::iterator it = vertex_shaders.begin(); it != vertex_shaders.end(); ++it)
        {
            if (!(*it)->GetCompiles())
            {
                all_compile = false;
                break;
            }
        }

        for (std::vector<Shader*>::iterator it = fragment_shaders.begin(); it != fragment_shaders.end(); ++it)
        {
            if (!(*it)->GetCompiles())
            {
                all_compile = false;
                break;
            }
        }

        for (std::vector<Shader*>::iterator it = geometry_shaders.begin(); it != geometry_shaders.end(); ++it)
        {
            if (!(*it)->GetCompiles())
            {
                all_compile = false;
                break;
            }
        }

        if (all_compile)
        {
            id = RenderManager::Instance()->CreateShaderProgram();

            for (std::vector<Shader*>::iterator it = vertex_shaders.begin(); it != vertex_shaders.end(); ++it)
            {
                RenderManager::Instance()->AttachShaderToProgram(id, (*it)->GetID());
            }

            for (std::vector<Shader*>::iterator it = geometry_shaders.begin(); it != geometry_shaders.end(); ++it)
            {
                RenderManager::Instance()->AttachShaderToProgram(id, (*it)->GetID());
            }

            for (std::vector<Shader*>::iterator it = fragment_shaders.begin(); it != fragment_shaders.end(); ++it)
            {
                RenderManager::Instance()->AttachShaderToProgram(id, (*it)->GetID());
            }

            linked = RenderManager::Instance()->LinkProgram(id, link_error);

            if (linked)
                ret = true;
        }
    }

    return ret;
}

void ShaderProgram::UseProgram()
{
    if (id > 0 && linked)
    {
        RenderManager::Instance()->UseShaderProgram(id);
    }
}

std::vector<Shader*> ShaderProgram::GetVertexShaders() const
{
    return vertex_shaders;
}

std::vector<Shader*> ShaderProgram::GetFragmentShaders() const
{
    return fragment_shaders;
}

std::vector<Shader*> ShaderProgram::GetGeometryShaders() const
{
    return geometry_shaders;
}

bool ShaderProgram::GetLinked() const
{
    return linked;
}

const char * ShaderProgram::GetLinkError() const
{
    return link_error.c_str();
}

int ShaderProgram::GetID() const
{
    return id;
}

void ShaderProgram::UnlinkProgram()
{
    if (id > 0)
        RenderManager::Instance()->DeleteProgram(id);

    id = 0;
    linked = false;
}
