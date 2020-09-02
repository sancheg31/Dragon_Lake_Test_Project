#include "EnemyAdvancePolicy.h"

#include <algorithm>
#include <iterator>
#include <cmath>


#include "GameObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"

#include "EnemyStorage.h"

#include "Rectangle.h"
#include "Utility.h"

#include <iostream>

double distance(Point p1, Point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

EnemyAdvancePolicy::EnemyAdvancePolicy(PlayerObject* player, int ticks) : playerObject(player), ticksCount(ticks) { }

void EnemyAdvancePolicy::advance(const EnemyStorage& obj) {
	if (ticks < ticksCount) {
		++ticks;
		return;
	}

	container_type objects;
	std::transform(obj.begin(), obj.end(), std::back_inserter(objects), [](auto enemy) {
		Point direction = enemy->next() - enemy->mapPosition();
		return ExEnemyObject{ enemy, DirectionState(direction) };
	});

	objects.sort([this](auto exEnemy1, auto exEnemy2) {
		auto enemy1 = exEnemy1.enemy, enemy2 = exEnemy2.enemy;
		double dist1 = distance(centerPoint(playerObject), centerPoint(enemy1));
		double dist2 = distance(centerPoint(playerObject), centerPoint(enemy2));
		return dist1 < dist2;
	});

	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {

		auto collidedObjects = findCollidedObjects(objects, iter, twoPixelBoundary(iter->enemy));

		auto collidedRects = findCollidedRectangles(collidedObjects);

		DirectionState direction = findDirection(iter->enemy, iter->currentState,collidedRects);
		iter->currentState = direction;

		/*
		bool accepted = false;
		Point stopPoint = iter->currentState.currentDirection();

		
		while (!accepted) {

			auto exEnemy = *iter;

			Rectangle enemyRect{ exEnemy.enemy->mapPosition() + exEnemy.currentState.currentDirection(),
				exEnemy.enemy->size(), VertexPosition::UP_LEFT };

			accepted = true;
			for (auto it = collidedRects.begin(); accepted && it != collidedRects.end(); ++it) {
				if (it->isCollide(enemyRect)) {
					accepted = false;
				//	std::cout << "inside objects collide\n";
				}
			}

			if (!accepted) {
				iter->currentState = iter->currentState.left();
				if (iter->currentState.currentDirection() == stopPoint) {
					iter->currentState = DirectionState{ Point{0, 0} };
					accepted = true;
				}
			}

		}*/
	}

	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {
		auto exEnemy = *iter;
		auto [enemy, dir] = exEnemy;

		auto traj = enemy->removeTrajectory();
		enemy->move(dir.currentDirection());
		traj->setSegment(enemy->mapPosition(), centerPoint(playerObject));
		enemy->setTrajectory(traj);
	}

	ticks = 0;
}

std::vector<Rectangle> EnemyAdvancePolicy::findCollidedRectangles(const container_type& objects) const {
	std::vector<Rectangle> newPositions;
	std::transform(objects.begin(), objects.end(), std::back_inserter(newPositions), [](auto exEnemy) {
		return Rectangle{ exEnemy.enemy->mapPosition() + exEnemy.currentState.currentDirection(),
			exEnemy.enemy->size(), VertexPosition::UP_LEFT };
	});
	return newPositions;
}

DirectionState EnemyAdvancePolicy::findDirection(EnemyObject* object, DirectionState currentState, const std::vector<Rectangle>& collidedRects) {

	bool accepted = false;
	Point stopPoint = currentState.currentDirection();

	while (!accepted) {

		Rectangle enemyRect{ object->mapPosition() + currentState.currentDirection(), object->size(), VertexPosition::UP_LEFT };

		accepted = true;
		for (auto it = collidedRects.begin(); accepted && it != collidedRects.end(); ++it) {
			if (it->isCollide(enemyRect)) {
				accepted = false;
			}
		}

		if (!accepted) {
			currentState = currentState.left();
			if (currentState.currentDirection() == stopPoint) {
				currentState = DirectionState{ Point{0, 0} };
				accepted = true;
			}
		}

	}

	return currentState;
}


Point EnemyAdvancePolicy::nextObjectCenter(Advanceable* object, Size size) const {
	return Rectangle{ object->next(), size, VertexPosition::UP_LEFT }.center();
}

Rectangle EnemyAdvancePolicy::twoPixelBoundary(GameObject* object) const {
	return Rectangle{ object->mapPosition() - Point{ 2, 2 }, object->size() + Size{ 4, 4 }, VertexPosition::UP_LEFT };
}

auto EnemyAdvancePolicy::findCollidedObjects(const container_type& cont, iterator start, Rectangle boundary) const
-> container_type
{

	bool inBoundaries = true;
	container_type result;

	for (auto iter = cont.begin(); iter != cont.end(); ++iter) {

		Rectangle rect{ iter->enemy };
		inBoundaries = boundary.isCollide(rect);

		if (inBoundaries && iter != start)
			result.push_back(*iter);
	}

	return result;
}

