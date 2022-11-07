#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

// everything in struct is by defualt public
struct TransformComponent {
	glm::vec2 position;
	glm::vec2 scale;
	double rotation; // This would need to be more than a simple angle for 3D
};

#endif
