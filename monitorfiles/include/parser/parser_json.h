#pragma once
#include "parser/parser.h"

class JsonParser : public Parser {
public:
	JsonParser() = default;
	std::optional<ParseFiles> parseFiles(std::stringstream& configStr, std::string_view nameInConfig) override;
};