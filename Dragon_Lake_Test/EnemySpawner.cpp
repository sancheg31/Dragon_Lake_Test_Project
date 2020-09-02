#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(std::shared_ptr<GameObjectFactory> factory, Size dims) :
	objectFactory(factory), dimensions(dims) { }

void EnemySpawner::addProhibitZone(GameObject* object, double threshold) {
	prohibits.push_back({ object, threshold });
}

void EnemySpawner::removeProhibitZone(GameObject* object) {
	auto iter = std::find_if(prohibits.begin(), prohibits.end(), [&object](auto pair) {
		return object == pair.first;
	});
	prohibits.erase(iter);
}

std::list<EnemyObject*> EnemySpawner::generate(PlayerObject* player, int amount) {
	
	int counter = 0;
	std::list<EnemyObject*> objects;

	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distWidth(0, dimensions.width);
	std::uniform_int_distribution<> distHeight(0, dimensions.height);

	for (int i = 0; i < amount; ++i) {

		Point position = generateUniquePoint(engine, distWidth, distHeight);

		EnemyObject* enemy = objectFactory->createEnemyObject(position);
		auto trajectory = new LinearTrajectoryGenerator();
		trajectory->setSegment(Rectangle{ *enemy }.center(), Rectangle{ *player }.center());
		enemy->setTrajectory(trajectory);

		objects.push_back(enemy);
		addProhibitZone(enemy, 1.0);
		std::cout << "enemy number " << counter++ << "is generated\n";
	}

	return objects;
}

Rectangle EnemySpawner::findProhibitArea(GameObject* object, double threshold) const {
	auto [width, height] = object->size();
	Point enhancer = Point{ (int)(threshold * width / 2), (int)(threshold * height / 2) };

	Point upperLeft = object->mapPosition() + (Point)object->size() / 2 - enhancer;
	Size size = Size{ (int)(threshold * width), (int)(threshold * height) };
	return Rectangle{ upperLeft, size, VertexPosition::UP_LEFT };
}

bool EnemySpawner::isUniquePoint(Point p) const {
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
