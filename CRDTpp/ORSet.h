#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <random>
#include <ctime>

template<typename T>
class ORSet {
public:
	ORSet() :dist(0, 4294967295), engine(std::time(0)) {
	}
	std::pair<T, unsigned int> add(const T elem) {
		int id = dist(engine);
		payload[elem].insert(id);
		return {elem, id};
	};
	std::pair<T, std::unordered_set<unsigned int>> remove(const T elem) {
		try {
			std::unordered_set<unsigned int> removed = payload.at(elem);
			payload.erase(elem);
			return {elem, removed};
		}
		catch(const std::out_of_range& err) {
			return {elem, std::unordered_set<unsigned int>()};
		}
	};
	void mergeAdd(const std::pair<T, unsigned int> elem) {
		payload[elem.first].insert(elem.second);
	};
	void mergeRemove(const std::pair<T, std::unordered_set<unsigned int>> elem) {
		if(!payload.count(elem.first)) {
			return;
		}
		for(auto it = elem.second.cbegin(); it != elem.second.cend(); it++) {
			payload[elem.first].erase(*it);
		}
		if(payload[elem.first].empty()) {
			payload.erase(elem.first);
		}
	};
	std::unordered_set<T> value() const {
		std::unordered_set<T> result;
		for(auto itr = payload.cbegin(); itr != payload.cend(); itr++) {
			result.insert(itr->first);
		}
		return result;
	}

private:
	std::unordered_map<T, std::unordered_set<unsigned int>> payload;
	std::default_random_engine engine;
	std::uniform_int_distribution<unsigned int> dist;
};