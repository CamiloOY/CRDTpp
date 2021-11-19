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

class RGA {
public:
	RGA(int id) {
		ts.id = id;
		ts.local_clock = 0;
		payload.insert(payload.begin(), {-1, {2147483647, 2147483647}});
	}

	std::pair<vertex, vertex> addRight(vertex before, char atom) {
		vertex element = {atom, this->now()};
		return this->addVertexRight(before, element);
	}

	void mergeAddRight(std::pair<vertex, vertex> operation) { // Lots of duplication between this and addRight
		const auto [before, element] = operation;
		this->addVertexRight(before, element);
	}

	vertex remove(vertex element) {
		for(auto itr = payload.begin(); itr != payload.end(); itr++) {
			if(*itr == element) {
				itr->first = 0;
				return element;
			}
		}
	}

	std::string value() const {
		std::string value = "";
		for(auto itr = ++payload.cbegin(); itr != payload.cend(); itr++) {
			if(itr->first) {
				value.push_back(itr->first);
			}
		}
		return value;
	}

	void mergeRemove(vertex element) {
		this->remove(element);
	}

private:
	std::list<vertex> payload;
	timestamp ts;

	timestamp now() {
		timestamp now = ts;
		ts.local_clock++;
		return now;
	}

	std::pair<vertex, vertex> addVertexRight(vertex before, vertex element) {
		bool found_el = false;
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
};