#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "parser/parser_json.h"
#include "filesystem_utils.h"

std::optional<JsonParser::ParseFiles> JsonParser::parseFiles(
	std::stringstream& configStr, 
	std::string_view nameInConfig) {

	ParseFiles filesInfo;

	try {

		boost::property_tree::ptree pt;
		boost::property_tree::read_json(configStr, pt);

		BOOST_FOREACH(boost::property_tree::ptree::value_type & v, pt.get_child(nameInConfig.data()))
		{
			const auto& curFile = v.second.data();
			if (FilesystemUtils::checkIsFile(curFile)) {
				filesInfo.names.insert(curFile);
			}
		}
	}
	catch (std::exception const&) {
		return std::nullopt;
	}
	return filesInfo;
}
