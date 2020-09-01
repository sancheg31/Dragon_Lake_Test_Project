
#include "BulletStorage.h"

#include <algorithm>

#include "BulletObject.h"

BulletStorage::BulletStorage(std::size_t maxCap): maxCapacity(maxCap) { }

void BulletStorage::addBullet(BulletObject* object) {
	cont.push_back(object);
	if (cont.size() > maxCapacity)
		removeFirstN(cont.size() - maxCapacity);
}

void BulletStorage::setMaxCapacity(std::size_t capacity) {
	maxCapacity = capacity;
	if (cont.size() > maxCapacity)
		removeFirstN(cont.size() - maxCapacity);
}

void BulletStorage::removeFirstN(std::size_t n) {
	for (int i = 0; i < n; ++i) {
		delete *cont.begin();
		cont.erase(cont.begin());
	}
}

auto BulletStorage::erase(iterator iter) -> iterator {
	return cont.erase(iter);
}

void BulletStorage::clear() {
	for (auto& enemy : cont)
		delete enemy;
	cont.clear();
}

auto BulletStorage::begin() -> iterator {
	return cont.begin();
}

auto BulletStorage::end() -> iterator {
	return cont.end();
}

auto BulletStorage::begin() const -> const_iterator {
	return cont.begin();
}

auto BulletStorage::end() const -> const_iterator {
	return cont.end();
}

auto BulletStorage::cbegin() const -> const_iterator {
	return cont.cbegin();
}

auto BulletStorage::cend() const -> const_iterator {
	return cont.cend();
}

