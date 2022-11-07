#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32; 

////////////////////////////////////////////////////////////////////////
// Singature
////////////////////////////////////////////////////////////////////////
// We use a bitset (1 and 0s) to keep track of which components an entity has, and
// also helps keep track of which entities a system is interested in.
////////////////////////////////////////////////////////////////////////
typedef std::bitset <MAX_COMPONENTS> Signature;

// These classes could be split into separate files like Registry.h, etc
class Component {
	// TODO: 
};

class Entity {
	private:
		int id;

	public:
		// this constructor syntax below makes sure the parameter id is passed and inits the members variable id of our class
		Entity(int id) : id(id) {};
		int GetId() const;
};

////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////
// The system processes entities that contain a specific signature... linking of entities together. How do we know what entities a certain system is interested in?
////////////////////////////////////////////////////////////////////////
class System {
	private:
		Signature componentSignature;
		std::vector<Entity> entities;

	public:
		System() = default; // What does this really do? what default values?
		~System() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityFromSystem(Entity entity);
		std::vector<Entity> GetSystemEntities() const;
		Signature& GetcomponentSignature() const;

		template <typename T> void RequireComponent();
};

class Registry {
	// TODO: 
};

#endif
