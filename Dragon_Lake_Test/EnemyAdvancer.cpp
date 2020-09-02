#include "EnemyAdvancer.h"


double distance(Point p1, Point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

EnemyAdvancer::EnemyAdvancer(PlayerObject* pl, std::list<EnemyObject*> obj) : player(pl) {
	obj.sort([pl](auto enemy1, auto enemy2) {
		double dist1 = distance(Rectangle{ *pl }.center(), Rectangle{ *enemy1 }.center());
		double dist2 = distance(Rectangle{ *pl }.center(), Rectangle{ *enemy2 }.center());
		return dist1 < dist2;
	});

	std::transform(obj.begin(), obj.end(), std::back_inserter(objects), [](auto enemy) {
		//std::cout << "Point with coords: " << enemy->mapPosition().x << " " << enemy->mapPosition().y << '\n';
		Point direction = enemy->next() - enemy->mapPosition();
		//std::cout << "Direction: { " << direction.x << " " << direction.y << " }\n";
		return ExEnemyObject{ enemy, DirectionState(direction) };
	});
}

void EnemyAdvancer::advance() {

	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {

		auto collided = findCollidedObjects(iter, twoPixelBoundary(iter->enemy));
		//std::cout << "New Coords: " << twoPixelBoundary(iter->enemy).upLeft().x << " " << twoPixelBoundary(iter->enemy).upLeft().y << '\n';
		//std::cout << "Collided objects: " << collided.size() << '\n';
		//std::cout << "checkpoint 1\n";

		std::vector<Rectangle> newPositions;
		std::transform(collided.begin(), collided.end(), std::back_inserter(newPositions), [](auto exEnemy) {
			return Rectangle{ exEnemy.enemy->mapPosition() + exEnemy.currentState.currentDirection(),
				exEnemy.enemy->size(), VertexPosition::UP_LEFT };
		});

		bool accepted = false;
		Point stopPoint = iter->currentState.currentDirection();

		//std::cout << "checkpoint 2\n";

		while (!accepted) {

			auto exEnemy = *iter;

			Rectangle enemyRect{ exEnemy.enemy->mapPosition() + exEnemy.currentState.currentDirection(),
				exEnemy.enemy->size(), VertexPosition::UP_LEFT };

			accepted = true;
			for (auto it = newPositions.begin(); accepted && it != newPositions.end(); ++it) {
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

		}
	}

	

	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {
		auto exEnemy = *iter;
		auto [enemy, dir] = exEnemy;

		auto traj = enemy->removeTrajectory();
		enemy->move(dir.currentDirection());
		traj->setSegment(enemy->mapPosition(), objectCenter(player));
		enemy->setTrajectory(traj);
	}
}

Point EnemyAdvancer::objectCenter(GameObject* object) {
	return Rectangle{ *object }.center();
}

Point EnemyAdvancer::nextObjectCenter(Advanceable* object, Size size) {
	return Rectangle{ object->next(), size, VertexPosition::UP_LEFT }.center();
}

Rectangle EnemyAdvancer::twoPixelBoundary(GameObject* object) {
	return Rectangle{ object->mapPosition() - Point{ 2, 2 }, object->size() + Size{ 4, 4 }, VertexPosition::UP_LEFT };
}

auto EnemyAdvancer::findCollidedObjects(typename container_type::iterator start, Rectangle boundary) 
-> container_type
{

	bool inBoundaries = true;
	container_type result;

	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {

		Rectangle rect{ *iter->enemy };
		inBoundaries = boundary.isCollide(rect);

		if (inBoundaries && iter != start)
			result.push_back(*iter);
	}

	return result;
}
