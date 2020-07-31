
#ifndef HASH_MAP_HPP_
#define HASH_MAP_HPP_

#include <string>
#include <iostream>
#include <sstream>
template<typename T>
int defaultHash(const T& a) { return 0; }

template<typename KEY, typename T, int(*thash)(const KEY& a) = defaultHash<KEY>>
class HashMap {

public:
	typedef std::pair<KEY, T>      Entry;
	typedef std::pair<int, Entry>  HashedEntry;
	typedef int(*hashfunc) (const KEY& a);


	HashMap(double threshold = 1.0, int(*chash)(const KEY& a) = defaultHash<KEY>);
	HashMap(const HashMap<KEY, T, thash>& to_copy, double threshold = 1.0, int(*chash)(const KEY& a) = defaultHash<KEY>);
	~HashMap();

	bool empty() const;
	int  size() const;
	bool has_key(const KEY& key) const;
	bool has_value(const T& value) const;
	std::string str() const; //supplies useful debugging information; contrast to operator <<

	T&       operator [] (const KEY& key);
	const T& operator [] (const KEY& key) const;
	HashMap<KEY, T, thash>& operator = (const HashMap<KEY, T, thash>& rhs);
	//bool operator == (const HashMap<KEY, T, thash>& rhs) const;
	//bool operator != (const HashMap<KEY, T, thash>& rhs) const;

	T add(const KEY& key, const T& value);
	T remove(const KEY& key);
	void clear();


private:

	int(*hash)(const KEY& k);
	int* bin = nullptr;						// bin will hold the index of the actual bin in Hashed_entry
	HashedEntry* hashed_entries = nullptr;	// hashed_entry will hold the BinNumber,Entry pair where Entry is a Key, T pair

	double threshold;
	int bins = 1;
	int entries = 1;
	int used = 0;

	int find_key(const KEY& key) const;
	void compress(const KEY& key, int& hash, int& bin_index) const;
	int unoccupied(int bin_index) const;

	void grow(int new_used);

};
