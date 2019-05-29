.PHONY: win64 clean stats format
default: win64

SOURCE_DIR = app
EXAMPLES_DIR = examples

win64:
	@cmake -Bbuild -G "Visual Studio 15 Win64" .
	@cmake --build build --config Release

clean:
	@rm -rf build

stats:
	@cloc $(SOURCE_DIR) $(EXAMPLES_DIR)

format:
	@find $(SOURCE_DIR) -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
	@find $(EXAMPLES_DIR) -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
