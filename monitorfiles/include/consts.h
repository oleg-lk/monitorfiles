#pragma once

struct AppConsts {
	static constexpr size_t numFilenameInArg = 2;
	static constexpr const char* TypeConfigFile = ".json";
	static constexpr const char* NameInConfig = "backup";
	static constexpr const char* BackupPath = "./backup/";
	static constexpr const char* BackupFileExt = ".backup";
};
