#pragma once



#include <list>
#include <utility>
#include <memory>

#include "Utility.h"

class GameObject;
class PlayerObject;

class GameObjectFactory;
class EnemyStorage;

class Rectangle;

/*
Spawns given number of enemies randomly on the map.
Collision-safe.
*/
class EnemySpawner
{
	using container_type = std::list<std::pair<GameObject*, double>>;
	using value_type = typename container_type::value_type;

public:
	EnemySpawner(std::shared_ptr<GameObjectFactory> factory, Size dims);
	
	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner(EnemySpawner&&) = default;
	~EnemySpawner() = default;

	void addProhibitZone(GameObject* object, double threshold);
	void removeProhibitZone(GameObject* object);

	virtual EnemyStorage generate(PlayerObject* player, int amount);

private:

	Rectangle findProhibitArea(GameObject* object, double threshold) const;

	bool isUniquePoint(Point p) const;

	template <typename Engine, typename Dist>
	Point generateUniquePoint(Engine engine, Dist distWidth, Dist distHeight) const;

	std::shared_ptr<GameObjectFactory> objectFactory;
	container_type prohibits{};
	Size dimensions;
	
};


template<typename Engine, typename Dist>
Point EnemySpawner::generateUniquePoint(Engine engine, Dist distWidth, Dist distHeight) const {
	bool unique = false;
	Point position;

	while (!unique) {
		position = Point{ distWidth(engine), distHeight(engine) };
		unique = isUniquePoint(position);
	}

	return position;
}