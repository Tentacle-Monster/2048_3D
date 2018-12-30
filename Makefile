make: 
	gcc -o source source.c -lglut -lGLU -lGL -lm 
	gcc -o source.exe -Wall source.c -lopengl32 -lglu32 -lglut32
	