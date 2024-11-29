# CMakeList.txt : CMake project for monitorfiles, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (monitorfiles 
  "include/monitorfiles.h" 
  "include/parser/parser.h" 
  "include/consts.h"  
  "include/parser/parser_json.h" 
  "include/filesystem_utils.h" 
  "include/parser/parser_fabric.h" 
  "monitorfiles.cpp" 
  "source/parser/parser_json.cpp" 
  "source/filesystem_utils.cpp" 
  "source/app/app_backup_files.cpp" 
  "source/app/app_run.cpp" 
  "source/app/app_initialize.cpp"
  "source/app/app_restore_file.cpp" )

include_directories(include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET monitorfiles PROPERTY CXX_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.
