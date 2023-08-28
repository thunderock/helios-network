main:	clean
	mkdir Compiled
	em++ -Wl,--whole-archive Source/CVNetwork.cpp -o Compiled/test.mjs \
		-O3 \
		-Wall \
		-s EXPORT_ES6=1 \
		-s MODULARIZE=1 \
		-s ALLOW_MEMORY_GROWTH=1 \
		-s EXPORT_NAME=HeliosNetwork \
		-s EXPORTED_FUNCTIONS="[_calloc, _malloc]" \
		-s ASSERTIONS=1 \
		-s MAXIMUM_MEMORY=4gb \

clean:
	rm -rf Compiled
