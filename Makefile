make: 
	gcc -o source source.c -lglut -lGLU -lGL -lm 
	i686-w64-mingw32-gcc -o source.exe -Wall source.c -I/usr/x86_64-w64-mingw32/include -L/usr/x86_64-w64-mingw32/lib -lopengl32 -lglu32  --static	