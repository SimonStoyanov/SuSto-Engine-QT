#include "entitymanager.h"
#include "Events/selectentitychange.h"
#include "eventmanager.h"
#include "globals.h"
#include "Entity/Components/component.h"
#include "Entity/Components/c_transform.h"
#include "Entity/Components/c_shape_renderer.h"
#include "Managers/jsonmanager.h"
#include "functions.h"
#include "Entity/entityabstraction.h"
#include "Entity/Components/c_mesh_renderer.h"
#include "Managers/meshmanager.h"
#include "Managers/texturemanager.h"
#include "Entity/Components/c_material_renderer.h"

EntityManager* EntityManager::instance = nullptr;

EntityManager::EntityManager()
{
    base_instance_uid = GetUIDRandomHexadecimal();
}

void EntityManager::UpdateAllEntities()
{
    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        (*it)->Update();
    }
}

Entity* EntityManager::CreateEntity()
{
    Entity* ret = new Entity(GetUIDRandomHexadecimal(), base_instance_uid);

    ret->Start();

    entities.push_back(ret);

    return ret;
}

Entity *EntityManager::CreateEntity(const std::string &uid, const std::string &instance_uid)
{
    Entity* ret = new Entity(uid, instance_uid);

    ret->Start();

    entities.push_back(ret);

    return ret;
}

void EntityManager::DestroyEntity(Entity*& entity)
{
    if(entity != nullptr)
    {
        for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
        {
            if((*it) == entity)
            {
                entities.erase(it);
                break;
            }
        }

        if (entity == selectedEntity)
            SetSelectedEntity(nullptr);

        entity->CleanUp();
        delete entity;
        entity = nullptr;
    }
}

void EntityManager::DestroyAllEntities()
{
    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
         if ((*it) == selectedEntity)
             SetSelectedEntity(nullptr);

        (*it)->CleanUp();
        delete (*it);
    }

    entities.clear();
}

std::vector<Entity *> EntityManager::GetEntities()
{
    return entities;
}

Entity *EntityManager::GetSelectedEntity()
{
    return selectedEntity;
}

void EntityManager::SetSelectedEntity(Entity* entity)
{
    Entity* last_selected_entity = selectedEntity;

    selectedEntity = entity;

    if(last_selected_entity != entity)
    {
        SelectEntityChange* ev = new SelectEntityChange(selectedEntity);
        EventManager::Instance()->SendEvent(ev);
    }
}

void EntityManager::Start()
{
    AddComponentType(ComponentType::COMPONENT_TRANSFORM, "Transform");
    AddComponentType(ComponentType::COMPONENT_MESH_RENDERER, "Mesh Renderer");
    AddComponentType(ComponentType::COMPONENT_MATERIAL_RENDERER, "Material Renderer");
    AddComponentType(ComponentType::COMPONENT_LIGHT, "Light");
}

void EntityManager::CleanUp()
{
    DestroyAllEntities();
}

void EntityManager::AddComponentType(ComponentType type, const std::string &component_name)
{
    component_types[type] = component_name;
}

ComponentType EntityManager::GetComponentTypeByComponentName(const std::string &component_name) const
{
    ComponentType ret = ComponentType::COMPONENT_NULL;

    for(std::map<ComponentType, std::string>::const_iterator it = component_types.begin(); it != component_types.end(); ++it)
    {
        if((*it).second.compare(component_name) == 0)
        {
            ret = (*it).first;
            break;
        }
    }

    return ret;
}

std::map<ComponentType, std::string> EntityManager::GetAllComponentTypes() const
{
    return component_types;
}

std::vector<Entity *> EntityManager::DuplicateEntity(std::vector<Entity *> entity)
{
    std::vector<Entity*> ret;

    EntityAbstraction abs;
    abs.Abstract(entity);
    ret = abs.DeAbstract();

    return ret;
}

std::vector<Entity*> EntityManager::LoadModel(const std::string &filepath)
{
    std::vector<Entity*> ret;

    std::vector<Mesh*> loaded_meshes = MeshManager::Instance()->LoadMesh(filepath);

    if(loaded_meshes.size() > 0)
    {
        for(std::vector<Mesh*>::iterator it = loaded_meshes.begin(); it != loaded_meshes.end(); ++it)
        {
            MeshManager::Instance()->LoadToVRAM((*it));

            std::vector<std::string> diffuse_textures = (*it)->GetTexturesDifusePaths();
            std::vector<std::string> normal_textures = (*it)->GetTexturesNormalPaths();
            std::vector<std::string> height_textures = (*it)->GetTexturesHeightPaths();
            std::vector<std::string> specular_textures = (*it)->GetTexturesSpecularPaths();

            Entity* new_entity = CreateEntity();
            new_entity->SetName((*it)->GetFilePlusName());

            C_MeshRenderer* c_mesh = (C_MeshRenderer*)new_entity->AddComponent(ComponentType::COMPONENT_MESH_RENDERER);
            C_MaterialRenderer* c_material = (C_MaterialRenderer*)new_entity->AddComponent(ComponentType::COMPONENT_MATERIAL_RENDERER);

            c_mesh->SetMesh((*it));

            if(diffuse_textures.size() > 0)
            {
                Texture* loaded_texture = TextureManager::Instance()->GetLoadedTextureFromFilepath(diffuse_textures[0]);

                if(loaded_texture == nullptr)
                {
                    loaded_texture = TextureManager::Instance()->LoadTexture(diffuse_textures[0]);

                    if(loaded_texture != nullptr)
                        TextureManager::Instance()->LoadToVRAM(loaded_texture);
                }

                if(loaded_texture != nullptr)
                {
                    c_material->SetDiffuseTexture(loaded_texture);
                }
            }

            if(normal_textures.size() > 0)
            {
                Texture* loaded_texture = TextureManager::Instance()->GetLoadedTextureFromFilepath(normal_textures[0]);

                if(loaded_texture == nullptr)
                {
                    loaded_texture = TextureManager::Instance()->LoadTexture(normal_textures[0]);

                    if(loaded_texture != nullptr)
                        TextureManager::Instance()->LoadToVRAM(loaded_texture);
                }

                if(loaded_texture != nullptr)
                {
                    c_material->SetNormalTexture(loaded_texture);
                }
            }

            if(height_textures.size() > 0)
            {
                Texture* loaded_texture = TextureManager::Instance()->GetLoadedTextureFromFilepath(height_textures[0]);

                if(loaded_texture == nullptr)
                {
                    loaded_texture = TextureManager::Instance()->LoadTexture(height_textures[0]);

                    if(loaded_texture != nullptr)
                        TextureManager::Instance()->LoadToVRAM(loaded_texture);
                }

                if(loaded_texture != nullptr)
                {
                    c_material->SetHeightTexture(loaded_texture);
                }
            }

            if(specular_textures.size() > 0)
            {
                Texture* loaded_texture = TextureManager::Instance()->GetLoadedTextureFromFilepath(specular_textures[0]);

                if(loaded_texture == nullptr)
                {
                    loaded_texture = TextureManager::Instance()->LoadTexture(specular_textures[0]);

                    if(loaded_texture != nullptr)
                        TextureManager::Instance()->LoadToVRAM(loaded_texture);
                }

                if(loaded_texture != nullptr)
                {
                    c_material->SetSpecularTexture(loaded_texture);
                }
            }

            ret.push_back(new_entity);
        }
    }

    return ret;
}

