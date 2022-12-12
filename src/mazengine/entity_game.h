#ifndef ENTITY_GAME_H_
#define ENTITY_GAME_H_

#include "mazengine.h"
#include <yaml-cpp/yaml.h>

namespace mazengine {
	class Entity;
	class EntityGame;

	typedef std::vector<Entity> EntityVector;

	class EntityGame : public Game {
	protected:
		EntityVector *entities;

	public:
		EntityGame(YAML::Node game_data) { entities = new EntityVector; };
	};

	class Entity {};
}; // namespace mazengine

#endif // ENTITY_GAME_H_
