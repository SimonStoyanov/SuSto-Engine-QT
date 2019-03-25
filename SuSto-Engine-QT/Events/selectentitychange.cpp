#include "selectentitychange.h"
#include "entity.h"

SelectEntityChange::SelectEntityChange(Entity* en) : Event(EventType::EVENT_SELECT_ENTITY_CHANGE)
{
    entity = en;
}

Entity* SelectEntityChange::GetEntity() const
{
    return entity;
}
