#include <thread>
#include <chrono>
#include <iomanip>
#include <unistd.h>
#include <iostream>
#include <sys/inotify.h>
#include "monitorfiles.h"

void Application::run() {

	if (!backupFiles()) {
		return;
	}

    char buffer[1024];
    int nextWd = -1;
	while (true) {
        int length = read(inotifyFd_, buffer, sizeof(buffer));
        if (length < 0) {
            perror("Ошибка чтения из inotify");
            break;
        }        
        int i = 0;
        while (i < length) {
            struct inotify_event* event = (struct inotify_event*)&buffer[i];
            if (event->mask & IN_CLOSE_WRITE) {
                /*произошла модификация отслеживаемого файла*/
                if(nextWd==event->wd){
                    nextWd = -1;
                }
                else if(watchFiles_.find(event->wd) != watchFiles_.end()){
                    const auto &modifiedFile = watchFiles_[event->wd];
                    const auto resRestore = restoreFile(modifiedFile);
                    if(resRestore){
                        std::cout << std::quoted(modifiedFile) << " восстановлен\n";
                    }
                    nextWd = event->wd;
                }

            }
            i += sizeof(inotify_event) + event->len;
        }
	}
}