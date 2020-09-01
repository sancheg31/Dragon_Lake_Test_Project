#pragma once


#include <list>

class BulletObject;

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


	void setMaxCapacity(std::size_t capacity);
	void addBullet(BulletObject*);
	void clear();
	
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;	

	const_iterator cbegin() const;
	const_iterator cend() const;

	container_type& storage();

private:

	void removeFirstN(std::size_t n);
	
	container_type cont;
	std::size_t maxCapacity;
};

