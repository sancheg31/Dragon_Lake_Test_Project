#include "EnemyStorage.h"

#include <algorithm>

#include "EnemyObject.h"

void EnemyStorage::addEnemy(EnemyObject* object) {
	cont.push_back(object);
}

auto EnemyStorage::erase(iterator iter) -> iterator {
	delete *iter;
	return cont.erase(iter);
}

void EnemyStorage::clear() {
	for (auto& enemy : cont)
		delete enemy;
	cont.clear();
}

std::size_t EnemyStorage::size() const {
	return cont.size();
}

bool EnemyStorage::empty() const {
	return cont.empty();
}

auto EnemyStorage::begin() -> iterator {
	return cont.begin();
}

auto EnemyStorage::end() -> iterator {
	return cont.end();
}

auto EnemyStorage::begin() const -> const_iterator {
	return cont.begin();
}

auto EnemyStorage::end() const -> const_iterator {
	return cont.end();
}

auto EnemyStorage::cbegin() const -> const_iterator {
	return cont.cbegin();
}

auto EnemyStorage::cend() const -> const_iterator {
	return cont.cend();
}

