#include "shadermanager.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager()
{

}

#include "Managers/rendermanager.h"

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

uint Shader::GetID() const
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

void ShaderProgram::SetProgramParameters(ShaderProgramParameters para)
{
    if (id > 0 && linked)
    {
        int count = RenderManager::Instance()->GetUniformsCount(id);

        for (int i = 0; i < count; ++i)
        {
            std::string uniform_name;
            GLenum uniform_type;

            RenderManager::Instance()->GetUniformInfo(id, i, uniform_name, uniform_type);

            switch (uniform_type)
            {
            case GL_INT:
            {
                std::map<std::string, int> int_vals = para.GetIntValues();

                for (std::map<std::string, int>::iterator it = int_vals.begin(); it != int_vals.end(); ++it)
                {
                    if (it->first.compare(uniform_name) == 0)
                    {
                        int val = int_vals[uniform_name];

                        RenderManager::Instance()->SetUniformInt(id, uniform_name.c_str(), val);
                    }
                }

                break;
            }
            case GL_FLOAT_VEC3:
            {
                std::map<std::string, float3> vector3_vals = para.GetVector3Values();

                for (std::map<std::string, float3>::iterator it = vector3_vals.begin(); it != vector3_vals.end(); ++it)
                {
                    if (it->first.compare(uniform_name) == 0)
                    {
                        float3 val = vector3_vals[uniform_name];

                        RenderManager::Instance()->SetUniformVec3(id, uniform_name.c_str(), val);
                    }
                }

                break;
            }
            case GL_FLOAT_VEC4:
            {
                std::map<std::string, float4> vector4_vals = para.GetVector4Values();

                for (std::map<std::string, float4>::iterator it = vector4_vals.begin(); it != vector4_vals.end(); ++it)
                {
                    if (it->first.compare(uniform_name) == 0)
                    {
                        float4 val = vector4_vals[uniform_name];

                        RenderManager::Instance()->SetUniformVec4(id, uniform_name.c_str(), val);
                    }
                }

                break;
            }
            case GL_BOOL:
            {
                std::map<std::string, bool> bool_vals = para.GetBoolValues();

                for (std::map<std::string, bool>::iterator it = bool_vals.begin(); it != bool_vals.end(); ++it)
                {
                    if (it->first.compare(uniform_name) == 0)
                    {
                        bool val = bool_vals[uniform_name];

                        RenderManager::Instance()->SetUniformBool(id, uniform_name.c_str(), val);
                    }
                }
                break;
            }
            case GL_SAMPLER_2D:
            {
                std::map<std::string, uint> text_vals = para.GetTextureValues();

                for (std::map<std::string, uint>::iterator it = text_vals.begin(); it != text_vals.end(); ++it)
                {
                    if (it->first.compare(uniform_name) == 0)
                    {
                        uint index = text_vals[uniform_name];

                        RenderManager::Instance()->SetUniformInt(id, uniform_name.c_str(), index);
                    }
                }
                break;
            }

            default:
                break;
            }
        }
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

uint ShaderProgram::GetID() const
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
