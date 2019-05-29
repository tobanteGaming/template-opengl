.PHONY: win64 clean stats format
default: win64


win64:
	cmake -Bbuild -G "Visual Studio 15 Win64" .
	cmake --build build --config Release

clean:
	rm -rf build


# MISC
stats:
	cloc app desktop

format:
	find app -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
