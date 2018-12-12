all:
	g++ -O3 -I./src src/main.cc -o exec

clean:
	rm -rf exec image.ppm