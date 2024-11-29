#include <string_view>
#include "parser/parser.h"
#include "parser/parser_json.h"

class ParserFabric {
public:
	Parser* getParser(std::string_view type) {
		if (type.compare(".json")==0) {
			return new JsonParser;
		}
		return nullptr;
	}
};