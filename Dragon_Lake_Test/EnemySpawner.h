#pragma once

#include <algorithm>
#include <list>
#include <random>
#include <iostream>

#include "EnemyObject.h"
#include "PlayerObject.h"
#include "GameObjectFactory.h"
#include "Rectangle.h"
#include "CSpriteFactory.h"

#include "LinearTrajectoryGenerator.h"

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

	std::list<EnemyObject*> generate(PlayerObject* player, int amount);

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