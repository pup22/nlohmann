#pragma once

#include <iostream>
#include <algorithm>
#include "nlohmann/json.hpp"

class CShedule : public nlohmann::json
{
public:
	nlohmann::json::iterator findById(const char* c_id) {
		uint32_t id = atoi(c_id);
		auto findIfId{ [id](auto entry)->bool { return entry[0] == id; } };
		return std::find_if(this->begin(), this->end(), findIfId);
	}

	nlohmann::json::iterator findById(uint32_t id) {
		auto findIfId{ [id](auto entry)->bool { return entry[0] == id; } };
		return std::find_if(this->begin(), this->end(), findIfId);
	}

	std::string serialize() {
		return dump();
	}

	CShedule& deserialize(std::string str) {
		nlohmann::json* p_this = this;
		*p_this = nlohmann::json::parse(str);
		return *this;
	}

	void sort() {
		auto fncomp_j{ [](nlohmann::json lhs, nlohmann::json rhs) ->bool { return lhs[0] < rhs[0]; } }; // lambda
		std::sort(this->begin(), this->end(), fncomp_j);
	}

	void unique() {
		auto funique_j{ [](nlohmann::json lhs, nlohmann::json rhs) ->bool { return lhs[0] == rhs[0]; } }; // lambda
		erase(std::unique(this->begin(), this->end(), funique_j), this->end());
	}

	uint32_t firstIdNumeric() {
		if (begin() == end()) return 0xFFFFFFFF;
		nlohmann::json j = *begin();
		return j[0];
	}

	std::string firstIdString() {
		if (begin() == end()) return ""; // error
		nlohmann::json j = *begin();
		std::string str = std::to_string((uint32_t)j[0]);
		return str;
	}

	bool eraseFirst() {
		if (begin() != end())
			erase(begin());
		else return false;
		return true;
	}

	bool eraseById(const char* c_id) {
		if (findById(c_id) != end())
			erase(findById(c_id));
		else return false;
		return true;
	}

	bool eraseById(uint32_t id) {
		if (findById(id) != end())
			erase(findById(id));
		else return false;
		return true;
	}

	bool eraseByIdLess(uint32_t id) {
		auto findIfLess{ [id](auto entry)->bool { return entry[0] < id; } };
		erase(std::remove_if(this->begin(), this->end(), findIfLess), this->end());
		return true;
	}
};
