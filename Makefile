main:	clean
	mkdir Compiled
	# emcc -g src/sudoku.c src/utils.c src/wasm.c -o src-compiled/sudoku.js -s EXPORTED_FUNCTIONS='["_generateBoard", "_validateBoard"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
	emcc -Wl,--whole-archive Source/CVNetwork.c -o Compiled/test.mjs \
		-O3 \
		--std=c17 \
		-Wall \
		-s EXPORT_ES6=1 \
		-s MODULARIZE=1 \
		-s ALLOW_MEMORY_GROWTH=1 \
		-s EXPORT_NAME=HeliosNetwork \
		-s EXPORTED_FUNCTIONS="[_calloc, _malloc]" \
		-s ASSERTIONS=1 \
		-s MAXIMUM_MEMORY=4gb
clean:
	rm -rf Compiled
