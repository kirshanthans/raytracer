all:
	g++ -O3 main.cc -o exec

clean:
	rm -rf exec image.ppm