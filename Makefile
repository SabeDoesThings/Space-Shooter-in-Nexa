build:
	gcc -o SpaceShooter.exe src/*.c src/code/*.c src/code/*.h -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

run:
	.\app.exe