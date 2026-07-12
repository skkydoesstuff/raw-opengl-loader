mkdir build
compiledb make debug
robocopy assets build\assets /E
build\raw_renderer.exe