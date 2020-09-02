#pragma once


#include <list>

class BulletObject;

/*
Represents container that stores bullet objects.
Introduced to cover implementation details and move them from GameEngine class
*/
class BulletStorage
{
	using container_type = std::list<BulletObject*>;
	using iterator = typename container_type::iterator;
	using const_iterator = typename container_type::const_iterator;

public:
	BulletStorage(std::size_t maxCapacity);
	BulletStorage(const BulletStorage&) = default;
	BulletStorage(BulletStorage&&) = default;
	BulletStorage& operator=(const BulletStorage&) = default;
	BulletStorage& operator=(BulletStorage&&) = default;


	iterator erase(iterator iter);
	void setMaxCapacity(std::size_t capacity);
	void addBullet(BulletObject*);
	void clear();
	
	std::size_t capacity() const;
	std::size_t size() const;
	bool empty() const;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;	

	const_iterator cbegin() const;
	const_iterator cend() const;

private:

	void removeFirstN(std::size_t n);
	
	container_type cont;
	std::size_t maxCapacity;
};

