program: glad.o car.o car.cpp car.hpp main.cpp main.hpp
	clang++ main.cpp -o program glad.o car.o -I glad/include -I /Library/Frameworks/SDL2.framework/Headers -F /Library/Frameworks -framework SDL2
	echo compiling prog
	./program

car.o:car.hpp car.cpp
	clang++ car.cpp -c car.hpp -I glad/include -I /Library/Frameworks/SDL2.framework/Headers -F /Library/Frameworks
	echo compile car
glad.o:
	clang glad/src/glad.c -c -I glad/include
	echo compile glad
