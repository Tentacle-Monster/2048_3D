make: 
	gcc -o source source.c -lglut -lGLU -lGL -lm 
	gcc source.c -lglut -lGLU -lGL -lm -o source.exe 
	