#pragma once

#include <algorithm>
#include <list>
#include <random>

#include "EnemyObject.h"
#include "GameObjectFactory.h"
#include "Rectangle.h"
#include "CSpriteFactory.h"


class EnemySpawner
{
public:
	EnemySpawner(std::shared_ptr<GameObjectFactory> factory, Size dims, int amount, double threshold) :
		objectFactory(factory), distWidth(0, dims.width), distHeight(0, dims.height), 
		enemyAmount(amount), objectThreshold(threshold) { }

	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner(EnemySpawner&&) = default;
	~EnemySpawner() = default;

	void setThreshold(double threshold) {
		objectThreshold = threshold;
	}

	void addProhibitZone(GameObject* object) {
		prohibits.push_back(object);
	}

	void removeProhibitZone(GameObject* object) {
		auto iter = std::find(prohibits.begin(), prohibits.end(), object);
		prohibits.erase(iter);
	}

	EnemyObject* generate() {
		bool generated = false;
		Point upLeft;
		while (!generated) {
			
			upLeft = Point{ distWidth(engine), distHeight(engine) };
			auto size = CSpriteFactory::spriteSize("enemy");
			Rectangle rect{ upLeft, size, VertexPosition::UP_LEFT };

			bool collided = false;
			for (auto it = prohibits.begin(); !collided && it != prohibits.end(); ++it) {
				auto [width, height] = (*it)->size();
				Rectangle objectRect{ (*it)->mapPosition(), 
										Size { (int)objectThreshold * width, (int)objectThreshold * height }, 
										VertexPosition::UP_LEFT	};
				if (rect.isCollide(objectRect))
					collided = true;
			}

			if (!collided)
				generated = true;
		}
		return objectFactory->createEnemyObject();
	}

private:
	std::shared_ptr<GameObjectFactory> objectFactory;
	std::uniform_int_distribution<> distWidth;
	std::uniform_int_distribution<> distHeight;
	int enemyAmount;
	double objectThreshold;

	std::random_device r{};
	std::default_random_engine engine{ r() };
	std::list<GameObject*> prohibits{};
	
};

