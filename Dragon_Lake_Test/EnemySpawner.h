#pragma once

#include <algorithm>
#include <list>
#include <random>
#include <iostream>

#include "EnemyObject.h"
#include "GameObjectFactory.h"
#include "Rectangle.h"
#include "CSpriteFactory.h"


class EnemySpawner
{
public:
	EnemySpawner(std::shared_ptr<GameObjectFactory> factory, Size dims) :
		objectFactory(factory), dimensions(dims) { }

	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner(EnemySpawner&&) = default;
	~EnemySpawner() = default;

	void addProhibitZone(GameObject* object) {
		prohibits.push_back(object);
	}

	void removeProhibitZone(GameObject* object) {
		auto iter = std::find(prohibits.begin(), prohibits.end(), object);
		prohibits.erase(iter);
	}

	std::list<EnemyObject*> generate(int amount, double threshold) {

		std::list<EnemyObject*> objects;

		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<> distWidth(0, dimensions.width);
		std::uniform_int_distribution<> distHeight(0, dimensions.height);
		for (int i = 0; i < amount; ++i) {

			bool generated = false;
			Point upLeft{};

			while (!generated) {

				upLeft = Point{ distWidth(engine), distHeight(engine) };
				auto size = CSpriteFactory::spriteSize("enemy");
				Rectangle rect{ upLeft, size, VertexPosition::UP_LEFT };

				bool collided = false;
				for (auto it = prohibits.begin(); !collided && it != prohibits.end(); ++it) {
					auto [width, height] = (*it)->size();
					auto [x, y] = (*it)->mapPosition();
					Rectangle objectRect{ Point{x + width / 2 - (int)(threshold * width / 2), y + height / 2 - (int)(threshold * height / 2) },
											Size { (int)threshold * width, (int)threshold * height },
											VertexPosition::UP_LEFT };
					if (objectRect.isCollide(rect))
						collided = true;
				}

				if (!collided)
					generated = true;
			}

			std::cout << "Generated point: " << upLeft.x << " " << upLeft.y << '\n';
			auto enemy = objectFactory->createEnemyObject();
			enemy->setPosition(upLeft);
			objects.push_back(enemy);
			prohibits.push_back(enemy);
		}
		return objects;
	}

private:
	std::shared_ptr<GameObjectFactory> objectFactory;
	std::list<GameObject*> prohibits{};
	Size dimensions;
	
};

