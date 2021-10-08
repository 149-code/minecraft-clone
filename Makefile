all: main.o cubeMesh.o renderer.o chunk.o player.o
	cc *.o -lglfw -lglew -framework OpenGl
clean:
	rm -rf *.o
