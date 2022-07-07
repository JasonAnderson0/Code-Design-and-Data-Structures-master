#include <string>
#pragma once

template<typename KeyType, typename T>
class Hashtable
{
public:
	Hashtable(unsigned int size) : m_size(size), m_data(new T[size]) { ; }
	~Hashtable() {delete[] m_data;}

	T& operator[] (const KeyType& key) {
		auto hashedKey = hash(key) % m_size;
		return m_data[hashedKey];
	}
	const T& operator[](const KeyType& key) const {
		auto hashedKey = hash(key) % m_size;
		return m_data[hashedKey];
	}

	unsigned int hash(const KeyType& key);

private:
	T* m_data;
	unsigned int m_size;
};

template<typename KeyType, typename T>
inline unsigned int Hashtable<KeyType, T>::hash(const KeyType& key)
{
	unsigned int value = 0;
	for (int i = 0; i < key.length(); i++)
		value = value * 1313 + key[i];
	return value;
}