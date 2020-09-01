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
	EnemySpawner(std::shared_ptr<GameObjectFactory> factory, Size dims) :
		objectFactory(factory), dimensions(dims) { }

	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner(EnemySpawner&&) = default;
	~EnemySpawner() = default;

	void addProhibitZone(GameObject* object, double threshold) {
		prohibits.push_back({ object, threshold });
	}

	void removeProhibitZone(GameObject* object) {
		auto iter = std::find_if(prohibits.begin(), prohibits.end(), [&object](auto pair) {
			return object == pair.first;
		});
		prohibits.erase(iter);
	}

	std::list<EnemyObject*> generate(PlayerObject* player, int amount) {

		std::list<EnemyObject*> objects;

		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<> distWidth(0, dimensions.width);
		std::uniform_int_distribution<> distHeight(0, dimensions.height);

		for (int i = 0; i < amount; ++i) {

			Point position = generateUniquePoint(engine, distWidth, distHeight);

			EnemyObject* enemy = objectFactory->createEnemyObject(position);
			auto trajectory = new LinearTrajectoryGenerator();
			trajectory->setSegment(Rectangle{ *enemy }.center(), Rectangle{ *player }.center(), 8);
			enemy->setTrajectory(trajectory);
			
			objects.push_back(enemy);
			addProhibitZone(enemy, 1.0);

		}

		return objects;
	}

private:

	Rectangle findProhibitArea(GameObject* object, double threshold) const {
		auto [x, y] = object->mapPosition();
		auto [width, height] = object->size();
		Point upperLeft = Point{ x + width / 2 - (int)(threshold * width / 2), y + height / 2 - (int)(threshold * height / 2) };
		Size size = Size{ (int)(threshold * width), (int)(threshold * height) };
		return Rectangle{ upperLeft, size, VertexPosition::UP_LEFT };
	}

	bool isUniquePoint(Point p) const {
		bool unique = true;
		Rectangle enemyRect = Rectangle{ p, CSpriteFactory::spriteSize("enemy"), VertexPosition::UP_LEFT };
		for (auto it = prohibits.begin(); unique && it != prohibits.end(); ++it) {
			auto [object, threshold] = *it;
			Rectangle rect = findProhibitArea(object, threshold);
			if (rect.isCollide(enemyRect))
				unique = false;
		}
		return unique;
	}

	template <typename Engine, typename Dist>
	Point generateUniquePoint(Engine engine, Dist distWidth, Dist distHeight) const {
		bool unique = false;
		Point position;

		while (!unique) {
			position = Point{ distWidth(engine), distHeight(engine) };
			unique = isUniquePoint(position);
		}

		return position;
	}

	std::shared_ptr<GameObjectFactory> objectFactory;
	container_type prohibits{};
	Size dimensions;
	
};

