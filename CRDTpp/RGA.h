#pragma once

#include <random>
#include <ctime>
#include <list>

class timestamp { // Simple class to represent a timestamp
public:
	int local_clock; // Clock at node
	int id; // Node's id (just a simple int for now)

	bool operator<(timestamp other) const {
		if(local_clock < other.local_clock) {
			return true;
		}
		else if(local_clock == other.local_clock) {
			return id < other.id;
		}
		else {
			return false;
		}
	}

	bool operator==(timestamp other) const {
		return local_clock == other.local_clock && id == other.id;
	}
};

//template<typename T>
using vertex = std::pair<char, timestamp>;

template<typename T>
class RGAInfo {
public:
	static T getBeginning();
	static T getTombstone();
};

//template<typename T, typename Info = RGAInfo<T>>
class RGA {
public:
	RGA(int id) {
		ts.id = id;
		ts.local_clock = 0;
		payload.insert(payload.begin(), {-1, {2147483647, 2147483647}});
	}

	std::pair<vertex, vertex> addRight(vertex before, char atom) {
		bool found_el = false;
		vertex element = {atom, this->now()};
		for(auto itr = payload.begin(); itr != payload.end(); itr++) {
			if(itr->second == before.second) {
				found_el = true;
				continue;
			}
			if(found_el) {
				if(itr->second < element.second) {
					payload.insert(itr, element);
					return {before, element};
				}
			}
		}
		if(found_el) {
			payload.insert(payload.end(), element);
			return {before, element};
		}
	}

	void mergeAddRight(std::pair<vertex, vertex> operation) { // Lots of duplication between this and addRight
		bool found_el = false;
		const auto [before, element] = operation;
		for(auto itr = payload.begin(); itr != payload.end(); itr++) {
			if(itr->second == before.second) {
				found_el = true;
				continue;
			}
			if(found_el) {
				if(itr->second < element.second) {
					payload.insert(itr, element);
					return;
				}
			}
		}
		if(found_el) {
			payload.insert(payload.end(), element);
		}
	}

	vertex remove(vertex element) {
		for(auto itr = payload.begin(); itr != payload.end(); itr++) {
			if(*itr == element) {
				itr->first = 0;
				return element;
			}
		}
	}

	std::string value() {
		std::string value = "";
		for(auto itr = payload.begin(); itr != payload.end(); itr++) {
			if(itr->first) {
				value.push_back(itr->first);
			}
		}
		return value;
	}

	void mergeRemove(vertex element) {
		for(auto itr = payload.begin(); itr != payload.end(); itr++) {
			if(*itr == element) {
				itr->first = 0;
			}
		}
	}

	void debug() {
		for(auto itr = payload.begin(); itr != payload.end(); itr++) {
			std::cout << '(' << itr->first << ',' << itr->second.local_clock << '.' << itr->second.id << ')';
		}
	}

private:
	std::list<vertex> payload;
	timestamp ts;

	timestamp now() {
		timestamp now = ts;
		ts.local_clock++;
		return now;
	}
};