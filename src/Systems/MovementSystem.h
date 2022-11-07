#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

class MovementSystem: public System {
public:
	MovementSystem() {
		// TODO: RequireComponent<TransformComponent>();
		// TODO: RequireComponent<...>();
	}

	void Update() {
		// Loop all entities that the system is interested in
		for (auto entity: GetEntities()) {
			// TODO: update entity positiobn based on its velocity
			// every frame of the game loop
		}
	}
};

#endif
