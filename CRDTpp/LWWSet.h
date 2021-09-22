#pragma once

#include <set>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>

template<typename T>
class LWWSet {
public:
	std::unordered_set<T> value() const {
		std::unordered_set<T> result;
		for(auto iter = add_set.cbegin(); iter != add_set.cend(); iter++) {
			if(remove_set.count(iter->first)) {
				if(iter->second >= remove_set.at(iter->first)) {
					result.insert(iter->first);
				}
			}
			else {
				result.insert(iter->first);
			}
		}
		return result;
	};
	void add(T elem, int timestamp) {
		if(timestamp > add_set[elem]) {
			add_set[elem] = timestamp;
		}
	};
	void remove(T elem, int timestamp) {
		if(timestamp > remove_set[elem]) {
			remove_set[elem] = timestamp;
		}
	};
	void merge(const LWWSet& other) {
		for(auto it = other.add_set.cbegin(); it != other.add_set.cend(); it++) {
			if(it->second > add_set[it->first]) {
				add_set[it->first] = it->second;
			}
		}
		for(auto itr = other.remove_set.cbegin(); itr != other.remove_set.cend(); itr++) {
			if(itr->second > remove_set[itr->first]) {
				remove_set[itr->first] = itr->second;
			}
		}
	};

private:
	std::unordered_map<T, int> add_set;
	std::unordered_map<T, int> remove_set;
};