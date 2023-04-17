all: main.o cubeMesh.o renderer.o chunk.o player.o texture.o perlin.o
	cc $^ -lglfw -lglew -framework OpenGl -I/opt/homebrew/include -L/opt/homebrew/lib 
release:
	cc -O3 *.c -lglfw -lglew -framework OpenGl -I/opt/homebrew/include -L/opt/homebrew/lib 
clean:
	rm -rf *.o a.out
