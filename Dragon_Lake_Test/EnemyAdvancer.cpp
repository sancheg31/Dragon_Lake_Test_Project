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
		auto trajectory = enemy->removeTrajectory();
		auto [left, right] = trajectory->possibleStates();
		enemy->setTrajectory(trajectory);
		return ExEnemyObject{ enemy, DirectionState(left), DirectionState(right) };
	});
}

void EnemyAdvancer::advance() {

	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {

		auto [collided, next] = findCollidedObjects(iter, twoPixelBoundary(iter->enemy));

		std::vector<Rectangle> newPositions;
		std::transform(collided.begin(), collided.end(), std::back_inserter(newPositions), [](auto exEnemy) {
			return Rectangle{ exEnemy.enemy->mapPosition() + exEnemy.leftState.currentDirection(),
				exEnemy.enemy->size(), VertexPosition::UP_LEFT };
		});

		bool accepted = false;
		bool leftStateActive = true, rightStateActive = false;
		DirectionState currentState = iter->leftState;

		
		/*{
			//output
			auto [x1, y1] = iter->leftState.currentDirection();
			auto [x2, y2] = iter->rightState.currentDirection();
			std::cout << "leftState: " << x1 << " " << y1 << '\n';
			std::cout << "rightState: " << x2 << " " << y2 << '\n';
		}*/

		while (!accepted) {

			auto exEnemy = *iter;

			Rectangle enemyRect{ exEnemy.enemy->mapPosition() + currentState.currentDirection(),
				exEnemy.enemy->size(), VertexPosition::UP_LEFT };

			accepted = true;
			for (auto it = newPositions.begin(); accepted && it != newPositions.end(); ++it) {
				if (it->isCollide(enemyRect))
					accepted = false;
			}

			if (!accepted) {
				if (leftStateActive) {
					leftStateActive = false;
					rightStateActive = true;
					currentState = exEnemy.rightState;
					exEnemy.leftState = exEnemy.leftState.left();
				}
				else if (rightStateActive) {
					rightStateActive = false;
					leftStateActive = true;
					currentState = exEnemy.leftState;
					exEnemy.rightState = exEnemy.rightState.right();
				}
			}
			else {
				exEnemy.leftState = currentState;
			}

			/*{
				//output
				auto [x, y] = exEnemy.enemy->mapPosition();
				std::cout << "For point " << x << " " << y << ":\n";
				std::cout << std::boolalpha << '\t' << leftStateActive << " " << rightStateActive << '\n';
			}*/

		}

	}

	for (auto iter = objects.begin(); iter != objects.end(); ++iter) {
		auto exEnemy = *iter;
		if (exEnemy.leftState.currentDirection() == exEnemy.enemy->next()) {
			exEnemy.enemy->advance();
		}
		else {
			auto [enemy, dir, junk] = exEnemy;

			{
				//output
				auto [x, y] = enemy->mapPosition();
				std::cout << "For point " << x << " " << y << " new direction is: ";
				auto [px, py] = dir.currentDirection();
				std::cout << px << " " << py << "\n\n";
			}

			auto traj = enemy->removeTrajectory();
			enemy->move(dir.currentDirection());
			traj->setSegment(objectCenter(enemy), objectCenter(player));
			enemy->setTrajectory(traj);


		}
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
-> std::pair<container_type, typename container_type::iterator> 
{

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
