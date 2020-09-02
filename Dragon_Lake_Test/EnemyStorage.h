#pragma once


#include <list>

class EnemyObject;

class EnemyStorage
{
	using container_type = std::list<EnemyObject*>;
	using iterator = typename container_type::iterator;
	using const_iterator = typename container_type::const_iterator;

public:
	EnemyStorage() = default;
	EnemyStorage(const EnemyStorage&) = default;
	EnemyStorage(EnemyStorage&&) = default;
	EnemyStorage& operator=(const EnemyStorage&) = default;
	EnemyStorage& operator=(EnemyStorage&&) = default;


	iterator erase(iterator iter);
	void addEnemy(EnemyObject*);
	void clear();


	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;

private:

	container_type cont;
};