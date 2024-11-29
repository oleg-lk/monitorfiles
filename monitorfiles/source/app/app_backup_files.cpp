#include <iostream>
#include <iomanip>
#include "monitorfiles.h"
#include "filesystem_utils.h"

bool Application::backupFiles() {

	if (!FilesystemUtils::createDirectory(AppConsts::BackupPath)) {
		std::cerr << "Ошибка: не удалось создать директорию " << 
			std::quoted(AppConsts::BackupPath) << " для резервирования\n";
		return false;
	}

	std::string backupFile;
	for (const auto& [wd, file]: watchFiles_) {
		backupFile = getBackupFileName(file);
		if ((wd >= 0) && FilesystemUtils::copyFile(file, backupFile)) {
			std::cout << "Создана резервная копия для " << std::quoted(file) << std::endl;
		}
		else {
			std::cerr << "Ошибка: файл " << std::quoted(file) << " не был скопирован\n";
		}
	}
	return true;
}
