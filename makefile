all:
	g++ -o game  *.cpp ECSystem/*.cpp -lSDL2 -lSDL2_image

clean:
	rm game *.so

.PHONY: all
