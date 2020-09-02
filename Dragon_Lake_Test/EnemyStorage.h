#pragma once


#include <list>

class EnemyObject;


/*
Represents container that stores enemy objects. 
Introduced to cover implementation details and move them from GameEngine class
*/
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

	std::size_t size() const;
	bool empty() const;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;

private:

	container_type cont;
};