default: circle

triangle_static: # display a static triangle on screen
	g++ triangle_static.cpp -o triangle_static -lSDL2 -lGL

triangle_move: # move a triangle up and down on the screen
	g++ triangle_move.cpp -o triangle_move -lSDL2 -lGL

triangle_bounce: # model a triangle falling and bouncing using F=ma=mg with restitution
	g++ triangle_bounce.cpp -o triangle_bounce -lSDL2 -lGL

circle: circle_bounce.cpp # model a circle falling and bouncing using F=ma=mg with restitution
	g++ circle_bounce.cpp -o circle -lSDL2 -lGL
