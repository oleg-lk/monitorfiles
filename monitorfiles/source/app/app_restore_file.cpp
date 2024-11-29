#include <iostream>
#include <iomanip>
#include "monitorfiles.h"
#include "filesystem_utils.h"

std::string Application::getBackupFileName(std::string_view file){
    std::string fileName = AppConsts::BackupPath + FilesystemUtils::getFileName(file) + AppConsts::BackupFileExt;
    return fileName;
}

bool Application::restoreFile(std::string_view file) {

    std::string backupFile = getBackupFileName(file);
    return FilesystemUtils::copyFile(backupFile, file);
}
