mkdir build
cmake -B build -G"Ninja"
cmake --build build
copy build\compile_commands.json compile_commands.json
build\raw_renderer.exe