#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <iomanip>
#include "monitorfiles.h"

Application::~Application()
{
    if(inotifyFd_>=0){
        close(inotifyFd_);
    }
}

bool Application::initialize() {

    if(inotifyFd_>=0){
        return true;    
    }

    /*Инициализация Inotify*/
    inotifyFd_ = inotify_init1(0/*IN_NONBLOCK*/);
    if (inotifyFd_ < 0) {
        std::cerr << "Ошибка: не удалось инициализировать inotify";
        return false;
    }
    return true;
}

int Application::addFileToWatch(std::string_view file) {
    /*добавим файл для наблюдения*/
    int wd = inotify_add_watch(inotifyFd_, file.data(), IN_CLOSE_WRITE);
    if (wd < 0) {
        std::cerr << "Не удалось взять под контроль файл " << std::quoted(file) << "\n";
    }
    else {
        std::cout << "Файл "<< std::quoted(file) << " взят под контроль\n";
    }
    return wd;
}
