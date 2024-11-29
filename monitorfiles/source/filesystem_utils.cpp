#include <filesystem>
#include <fstream>
#include <iostream>
#include "filesystem_utils.h"
#include <unistd.h>
#include <stdio.h>

namespace fs = std::filesystem;

bool FilesystemUtils::checkIsFile(
	std::string_view path) {

	fs::path filePath{ path };
	const auto isFile = fs::is_regular_file(filePath);
	return isFile;
}

bool FilesystemUtils::checkIsDirectory(
	std::string_view path) {

	fs::path filePath{ path };
	const auto isDir = fs::is_directory(filePath);
	return isDir;
}

bool FilesystemUtils::createDirectory(std::string_view path)
{
	if (!FilesystemUtils::checkIsDirectory(path)) {
		if (!std::filesystem::create_directories(path)) {
			return false;
		}
	}
	return true;
}

bool FilesystemUtils::copyFile(std::string_view file, std::string_view pathTo)
{
	fs::copy_options my_options;
	my_options = fs::copy_options::overwrite_existing;
	auto resCopy = std::filesystem::copy_file(file, pathTo, my_options);
	return resCopy;
}

std::stringstream FilesystemUtils::readFile(std::string_view fileName) {
	std::ifstream f(fileName.data());
	std::stringstream ss;
	ss << f.rdbuf();
	return ss;
}

std::string FilesystemUtils::getFileType(std::string_view path) {
	fs::path filePath{ path };
	auto ext = filePath.extension();
	return ext.string();
}

std::string FilesystemUtils::getFileName(std::string_view path) {
	fs::path filePath{ path };
	auto ext = filePath.filename();
	return ext.string();
}