all:
	cmake -B build
	cmake --build build

run: all
	./build/PolyCore	

clean:
	rm -rf build