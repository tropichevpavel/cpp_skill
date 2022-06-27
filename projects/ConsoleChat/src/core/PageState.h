#pragma once

#include <utility>
#include <string>
#include <map>

#include "AnyData.h"

class PageState {
	int _page;
	std::map<std::string, AnyData*> _state;

public:
	PageState(const int& page) : _page(page) {}
	PageState(const int& page, std::initializer_list<std::pair<std::string, AnyData>>& state) : _page(page) {
		this->initState(state);
	}

	template <typename T>
	T& get(const std::string& name) {
		return this->_state.find(name)->second->get<T>();
	}

	void initState(std::map<std::string, AnyData*> state) {
		if (!_state.size()) _state = state;
	}

	void initState(std::initializer_list<std::pair<std::string, AnyData>> state) {
		if (!_state.size())
			for (auto& param : state)
				this->_state[param.first] = new AnyData(std::move(const_cast<AnyData&>(param.second)));
	}

	int getPage() const {
		return this->_page;
	}
};
