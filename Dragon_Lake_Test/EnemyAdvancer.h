#pragma once


#include <algorithm>
#include <list>
#include <cmath>

#include "Rectangle.h"
#include "Utility.h"

#include "EnemyObject.h"
#include "PlayerObject.h"
#include "DirectionState.h"

double distance(Point p1, Point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

class EnemyAdvancer
{

	struct ExEnemyObject
	{
		EnemyObject* enemy;
		DirectionState state;
	};

	using container_type = std::list<ExEnemyObject>;

public:
	EnemyAdvancer(PlayerObject* pl, std::list<EnemyObject*> obj): player(pl) {
		obj.sort([pl](auto enemy1, auto enemy2) {
			double dist1 = distance(Rectangle{ *pl }.center(), Rectangle{ *enemy1 }.center());
			double dist2 = distance(Rectangle{ *pl }.center(), Rectangle{ *enemy2 }.center());
			return dist1 < dist2;
		});
		std::transform(obj.begin(), obj.end(), std::back_inserter(objects), [](auto enemy) {
				return ExEnemyObject{ enemy, DirectionState(enemy->next()) };
		});

	}

	void advance() {

		for (auto iter = objects.begin(); iter != objects.end(); ++iter) {

			auto [collided, next] = findCollidedObjects(iter, twoPixelBoundary(iter->enemy));

			std::vector<Rectangle> newPositions;
			std::transform(collided.begin(), collided.end(), std::back_inserter(newPositions), [](auto exEnemy) {
				return Rectangle{ exEnemy.enemy->mapPosition() + exEnemy.state.currentDirection(), 
									exEnemy.enemy->size(), VertexPosition::UP_LEFT };
			});

		}

	}

private:


	Point objectCenter(GameObject* object) {
		return Rectangle{ *object }.center();
	}

	Point nextObjectCenter(Advanceable* object, Size size) {
		return Rectangle{ object->next(), size, VertexPosition::UP_LEFT }.center();
	}

	Rectangle twoPixelBoundary(GameObject* object) {
		Rectangle{ object->mapPosition() - Point{2, 2}, object->size() + Size{4, 4}, VertexPosition::UP_LEFT };
	}


	std::pair<container_type, typename container_type::iterator> 
	findCollidedObjects(typename container_type::iterator start, Rectangle boundary) {

		bool inBoundaries = true;
		container_type result;
		auto iter = start;
		++iter;
		for (; inBoundaries && iter != objects.end(); ++iter) {

			Rectangle rect{ *iter->enemy };
			inBoundaries = boundary.isCollide(rect);

			if (inBoundaries)
				result.push_back(*iter);
		}

		return { result, iter };
	}


	PlayerObject* player;
	container_type objects;
};

