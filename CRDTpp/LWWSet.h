#pragma once

#include <set>
#include <unordered_set>
#include <algorithm>

template<typename T>
class LWWSet {
public:
	std::unordered_set<T> value() const {
		std::unordered_set<T> result;
		for(const auto& added_item : add_set) {
			bool should_add = true;
			for(const auto& removed_item : remove_set) {
				if(removed_item.first == added_item.first && removed_item.second > added_item.second) {
					should_add = false;
					break;
				}
			}
			if(should_add) {
				result.insert(added_item.first);
			}
		}
		return result;
	};
	void add(T elem, int timestamp) {
		add_set.insert({elem, timestamp});
	};
	void remove(T elem, int timestamp) {
		remove_set.insert({elem, timestamp});
	};
	void merge(const LWWSet& other) {
		add_set.insert(other.add_set.begin(), other.add_set.end());
		remove_set.insert(other.remove_set.begin(), other.remove_set.end());
	};

private:
	// Could optimise by replacing these sets with hash tables so for faster lookup of the timestamps of an object
	std::set<std::pair<T, int>> add_set;
	std::set<std::pair<T, int>> remove_set;
};