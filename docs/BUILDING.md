# Building SpacedInvaders (Windows + vcpkg)

This project can be built with CMake. If you use `vcpkg` for dependency management, the repository's top-level `CMakeLists.txt` will try to detect vcpkg automatically (via `VCPKG_ROOT`) or you can pass the toolchain file explicitly.

Quick steps (recommended)

1. Install dependencies with vcpkg (example triplet: `x64-windows`):

```powershell
# from your vcpkg root
.\vcpkg install allegro:x64-windows
```

2. Configure the project using the vcpkg toolchain file (explicit):

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

3. Build:

```powershell
cmake --build build --config Release
```

Alternative: set `VCPKG_ROOT` (PowerShell example) and run CMake normally:

```powershell
$env:VCPKG_ROOT = 'D:\vcpkg'
cmake -S . -B build
cmake --build build --config Debug
```

Notes & troubleshooting

- If CMake cannot find a package provided by vcpkg, ensure the vcpkg `installed/<triplet>` directory exists and the correct triplet was used when installing packages.
- You may override the toolchain file at configure time using `-DCMAKE_TOOLCHAIN_FILE=...` (this is the recommended, explicit approach for CI).
- The root `CMakeLists.txt` will not overwrite a `CMAKE_TOOLCHAIN_FILE` passed on the command line. Subprojects should not hardcode a toolchain file.
- If a package offers a CMake CONFIG package (preferred), the project prefers that. Otherwise it falls back to `pkg-config` where available.

Example `vcpkg` commands you might need:

```powershell
# Install Allegro for x64 Windows
D:\vcpkg\vcpkg install allegro:x64-windows

# Install other common libs (example)
D:\vcpkg\vcpkg install sdl2:x64-windows
```

If you'd like, I can add more platform-specific notes (MSVC vs MinGW) or automate triplet detection in the CMake files.