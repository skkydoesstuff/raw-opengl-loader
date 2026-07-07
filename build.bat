mkdir build
cmake -B build -G "MinGW Makefiles"
cmake --build build
copy build\compile_commands.json compile_commands.json
robocopy "assets" "build\assets" /e
build\raw_renderer.exe