// monitorfiles.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <string>
#include <unordered_map>
#include "consts.h"

class Application {
public:
	using WatchFiles = std::unordered_map<int, std::string>;
	static Application* getInstance() {
		static Application app = Application{};
		return &app;
	}
	template<class ContFiles>
	bool setMonitorFiles(const ContFiles& files) {
		/**/
		if (!initialize()){
			return false;
		}

		/*Сохраняем отслеживаемые файлы по ключу дескриптора*/
		for( auto &file : files){
			int wd = addFileToWatch(file);
			if(wd>=0){
				watchFiles_[wd] = file;
			}
		}

		return watchFiles_.size() > 0;
	}
	
	void run();

	~Application();
private:
	bool initialize();
	bool backupFiles();
	int addFileToWatch(std::string_view file);
	static bool restoreFile(std::string_view file);
	static std::string getBackupFileName(std::string_view file);	
private:
	Application() {}
	WatchFiles watchFiles_;
	int inotifyFd_{-1};
};

// TODO: Reference additional headers your program requires here.
