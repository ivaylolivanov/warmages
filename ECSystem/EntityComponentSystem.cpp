#include "EntityComponentSystem.hpp"

void Entity::addGroup( Group memGroup )
{
    groupBitSet[ memGroup ] = true;
    manager.addToGroup( this, memGroup );
}
