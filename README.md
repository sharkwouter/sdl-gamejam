# Sharkwouter's SDL Enthusiasts Gamejam entry

Will see if this becomes anything.

## Building

```
mkdir build && cd build
cmake ..
make
```

## Building on Windows

Install dependencies:

```
vcpkg install --triplet x64-windows-static sdl2
```

Do the actual build:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static ..
cmake --build . --config Release
```
