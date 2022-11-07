#include "ECS.h"

int Entity::GetId() const {
	// Encampsulation: protect variables inside and only access thru public methods
	return id;
}