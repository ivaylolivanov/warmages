#ifndef ECS
#define ECS

#include <array>
#include <vector>
#include <memory>
#include <bitset>
#include <iostream>
#include <algorithm>

class Entity;
class Manager;
class Component;



using Group = std::size_t;
using ComponentID = std::size_t;

constexpr std::size_t maxGroups = 32;
constexpr std::size_t maxComponents = 32;

using GroupBitSet = std::bitset< maxGroups >;
using ComponentBitSet = std::bitset< maxComponents >;
using ComponentArray = std::array< Component* , maxComponents >;




inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template < typename T > inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

class Component
{
public:

    Entity* entity;
    virtual void init()   { };
    virtual void update() { };
    virtual void draw()   { };

    virtual ~Component()  { };
};

class Entity
{
private:
    Manager& manager;

    bool active = true;
    std::vector< std::unique_ptr< Component > > components;

    GroupBitSet groupBitSet;
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;


public:

    Entity( Manager& memManager ) : manager( memManager ) {}

    void draw()     { for( auto& comp : components ) comp->draw(); }
    void update()   { for( auto& comp : components ) comp->update(); }
    void destroy()  { this->active = false; }
    bool isActive() { return this->active; }

    void addGroup( Group memGroup );
    void delGroup( Group memGroup ) { groupBitSet[ memGroup ] = false; }
    bool hasGroup( Group memGroup ) { return groupBitSet[ memGroup ]; }



    template < typename T > bool hasComponent() const {
	return componentBitSet[ getComponentTypeID< T >() ];
    }


    template < typename T, typename... TArgs >
    T& addComponent( TArgs&&... mArgs ) {

	T* comp ( new T( std::forward< TArgs >( mArgs )... ));
	comp->entity = this;

	std::unique_ptr< Component > uniqPtr ( comp );
	components.emplace_back( std::move ( uniqPtr ) );

	componentArray  [ getComponentTypeID< T >() ] = comp;
	componentBitSet [ getComponentTypeID< T >() ] = true;

	comp->init();

	return *comp;
    }


    template < typename T > T& getComponent() const {
	auto ptr( componentArray [ getComponentTypeID< T >() ]);
	return *static_cast< T* >( ptr );
    }

};


class Manager
{

private:
    std::vector< std::unique_ptr< Entity >> entities;
    std::array< std::vector< Entity* >, maxGroups > groupEntities;

public:
    void draw()    { for ( auto& ent : entities ) ent->draw();   }
    void update()  { for ( auto& ent : entities ) ent->update(); }


    void refresh() {

	for ( auto i( 0u ); i < maxGroups; ++i )
	{
	    auto& vec( groupEntities[ i ] );

	    vec.erase(
		std::remove_if(
		    std::begin( vec ),
		    std::end( vec ),
		    [ i ]( Entity* memEntity )
			{
			    return !memEntity->isActive() || !memEntity->hasGroup( i );
			} ),
		std::end( vec ) );
	}


	entities.erase(
	    std::remove_if(
		std::begin( entities ),
		std::end( entities ),
		[](const std::unique_ptr<Entity> &mEntity) { return !mEntity->isActive(); }
		),
	    std::end( entities ));
    }


    std::vector< Entity* >& getGroup( Group memGroup )  { return groupEntities[ memGroup ]; }
    void addToGroup( Entity* memEntity, Group memGroup ) { groupEntities[ memGroup ].emplace_back( memEntity ); }


    Entity& addEntity() {
	Entity* ent = new Entity( *this );
	std::unique_ptr< Entity > uniqPtr { ent };
	entities.emplace_back( std::move ( uniqPtr ) );
	return *ent;
    }

};


#endif
