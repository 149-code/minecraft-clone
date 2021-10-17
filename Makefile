all: main.o cubeMesh.o renderer.o chunk.o player.o texture.o perlin.o
	cc $^ -lglfw -lglew -framework OpenGl
release:
	cc -O3 *.c -lglfw -lglew -framework OpenGl
clean:
	rm -rf *.o a.out
prof:
	xcrun xctrace record --template 'Time Profiler' --target-stdout - --launch a.out
