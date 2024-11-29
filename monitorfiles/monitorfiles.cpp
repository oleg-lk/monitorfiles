// monitorfiles.cpp : Defines the entry point for the application.
//

#include <memory>
#include <iostream>
#include "monitorfiles.h"
#include "filesystem_utils.h"
#include "parser/parser_fabric.h"

namespace {
std::optional<std::unordered_set<std::string>> parseFiles(std::string_view configFileName)
{
	/*проверка, что файл конфигурации существует*/
	if (!FilesystemUtils::checkIsFile(configFileName)) {
		std::cerr << "Ошибка: не удалось открыть файл конфигурации\n";
		return std::nullopt;
	}
	/*тип файла*/
	const auto configFileType = FilesystemUtils::getFileType(configFileName);
	/*чтение всего файла*/
	auto configStr = FilesystemUtils::readFile(configFileName);

	std::unique_ptr<ParserFabric> parserFabric = std::make_unique<ParserFabric>();
	/*указатель на парсер*/
	auto parser = parserFabric->getParser(configFileType);
	if (!parser) {
		std::cerr << "Ошибка: не найден парсер для файла конфигурации\n";
		return std::nullopt;
	}
	std::unique_ptr<Parser> ptrParser(parser);
	auto files = ptrParser->parseFiles(configStr, AppConsts::NameInConfig);
	if (!files) {
		std::cout << "Ошибка: неверный формат конфигурационного файла\n";
		return std::nullopt;
	}

	return std::move(files->names);
}
}

int main(int argc, char* argv[])
{
	/*проверка что есть аргумент с файлом конфигурации*/
	if (argc < AppConsts::numFilenameInArg) {
		std::cerr << "Использование: monitorfiles <путь_к_конфигурационному_файлу>\n";
		return 1;
	}
	/*читаем из конфигурации список файлов*/
	const auto configFileName = argv[AppConsts::numFilenameInArg - 1];
	auto files = parseFiles(configFileName);
	if (!files) {
		return 1;
	}

	auto app = Application::getInstance();
	if(!app->setMonitorFiles(std::move(files.value()))){
		return 1;		
	}

	app->run();

	return 0;
}
