.PHONY: all win64 clean stats format
default: all

# Source
SOURCE_DIR = app
EXAMPLES_DIR = examples

# Build
BUILD_DIR = build
BUILD_TYPE = Release

all:
	@cmake -B$(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) .
	@cmake --build $(BUILD_DIR)

win64:
	@cmake -B$(BUILD_DIR) -G "Visual Studio 15 Win64" .
	@cmake --build $(BUILD_DIR) --config $(BUILD_TYPE)

clean:
	@rm -rf $(BUILD_DIR)

stats:
	@cloc $(SOURCE_DIR) $(EXAMPLES_DIR)

format:
	@find $(SOURCE_DIR) -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
	@find $(EXAMPLES_DIR) -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
