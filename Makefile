.PHONY: all debug win64 doc clean stats format
default: all

# Source
SOURCE_DIR = remisen_run
EXAMPLES_DIR = examples
RESOURCE_DIR = resources

# Build
BUILD_DIR = build
BUILD_DOC_DIR = build-documentation
BUILD_TYPE = Release

all:
	@cmake -B$(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) .
	@cmake --build $(BUILD_DIR) --config $(BUILD_TYPE)

debug:
	@cmake -B$(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug .
	@cmake --build $(BUILD_DIR) --config Debug

win64:
	@cmake -B$(BUILD_DIR) -G "Visual Studio 15 Win64" .
	@cmake --build $(BUILD_DIR) --config $(BUILD_TYPE) -- /m

doc:
	@doxygen Doxyfile.in

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DOC_DIR)

stats:
	@cloc $(SOURCE_DIR) cmake CMakeLists.txt $(RESOURCE_DIR)/shaders

format:
	@find $(SOURCE_DIR) -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
	@find $(EXAMPLES_DIR) -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
