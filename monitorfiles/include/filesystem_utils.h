#include <string_view>
#include <sstream>
#include <string>

class FilesystemUtils {
public:
	static bool checkIsFile(std::string_view path);

	static bool checkIsDirectory(std::string_view path);
	static bool createDirectory(std::string_view path);
	static bool copyFile(std::string_view file, std::string_view pathTo);

	static std::stringstream readFile(std::string_view fileName);

	static std::string getFileType(std::string_view path);
	static std::string getFileName(std::string_view path);

};