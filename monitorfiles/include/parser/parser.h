#pragma once
#include <unordered_set>
#include <string>
#include <optional>

class Parser {
public:
	struct ParseFiles {
		std::unordered_set<std::string> names;
	};
public:
	Parser() = default;
	virtual ~Parser() {}
	virtual std::optional<ParseFiles> parseFiles(std::stringstream& configStr, std::string_view nameInConfig) = 0;
};