# Blappy Fird

This is my flappy bird

## Requirements

- conan
- meson
- raylib
- gcc
- ninja
- clang-format
- clang-tidy
- cppcheck

## Setup conan
```
 conan profile detect
 conan install . --output-folder=build --build=missing -pr .conanprofile
```

## Build

```
meson setup --native-file .\build\build\Release\generators\conan_meson_native.ini build
meson compile -C build
```

## Run clang-tidy

```
clang-tidy --config-file=.clang-tidy -p .\build src/*.c 
```

## Run cppcheck

```
cppcheck --project=build/compile_commands.json --enable=all --suppress=missingIncludeSystem
```

## Run

```
./build/blappy-fird
```

## Create nsis installer

```
makensis config.nsi
```

## Development

```
clang-format -style=file -i <path/to/source/file>
```
