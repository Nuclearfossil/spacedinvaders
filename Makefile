BUILD_DIR    := build
BUILD_VS2022 := build-vs2022
BUILD_VS2026 := build-vs2026
VCPKG_ROOT  ?= E:/vcpkg
VCPKG_ROOT  := $(subst \,/,$(VCPKG_ROOT))
TOOLCHAIN   := $(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake

.PHONY: all configure debug release relwithdebinfo \
        vs2022 vs2026 \
        clean clean-vs2022 clean-vs2026 clean-all rebuild

all: debug

$(BUILD_DIR)/CMakeCache.txt:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)

configure: $(BUILD_DIR)/CMakeCache.txt

debug: $(BUILD_DIR)/CMakeCache.txt
	cmake --build $(BUILD_DIR) --config Debug

release: $(BUILD_DIR)/CMakeCache.txt
	cmake --build $(BUILD_DIR) --config Release

relwithdebinfo: $(BUILD_DIR)/CMakeCache.txt
	cmake --build $(BUILD_DIR) --config RelWithDebInfo

# Generates build-vs2022/SpacedInvaders.sln (requires CMake 3.5+)
vs2022:
	cmake -S . -B $(BUILD_VS2022) \
	      -G "Visual Studio 17 2022" -A x64 \
	      -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)

# Generates build-vs2026/SpacedInvaders.slnx (requires CMake 4.2+)
vs2026:
	cmake -S . -B $(BUILD_VS2026) \
	      -G "Visual Studio 18 2026" -A x64 \
	      -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)

clean:
	rm -rf $(BUILD_DIR)

clean-vs2022:
	rm -rf $(BUILD_VS2022)

clean-vs2026:
	rm -rf $(BUILD_VS2026)

clean-all: clean clean-vs2022 clean-vs2026

rebuild: clean all
