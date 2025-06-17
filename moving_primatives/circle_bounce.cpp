#include <SDL2/SDL.h>
#include <GL/gl.h>

/*
Change the bouncing triangle (triangle_bounce.cpp) to a circle
*/

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    // drawFilledCircle method adapted from this: https://gist.github.com/linusthe3rd/803118 
	int i;
	int triangleAmount = 50; // of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * 3.141592;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
            // rgb for orange: (255, 108, 12). Normalize to [0,1] by x/255. 
            glColor3f(1.0, 0.4235294118, 0.04705882353);
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

int main() {
    // Initialize SDL with video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    // Create SDL window with OpenGL context
    SDL_Window* window = SDL_CreateWindow(" hi ",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    // Main loop
    bool running = true;
    SDL_Event event;

    // Note: 3 equiv. ways to define a float:
    // float dt = 0.005;
    // float dt = 0.005f;
    // auto  dt = 0.005f;

    auto  dt = 0.005f;
    auto v_old = 0.0001f;
    auto v_new = 0.00f;
    auto y_old = 0.8f;
    auto y_new = 0.00f;
    auto g = -9.8f;
    auto restitution = 0.6f; // bounciness 
    auto view_floor = -.8f;
    auto epsilon = 0.001f;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        SDL_Delay(16); 
        
        // Update triangle velocity and position
        v_new = v_old + g*dt;
        y_new = y_old + v_old*dt + 0.5*g*dt*dt;

        // Bounce logic at floor
        if (y_new < view_floor){
            // # stopping condition to avoid jiggle
            if (abs(y_new - y_old) < epsilon){
                v_new = 0;
            }
            y_new = view_floor;
            v_new = -v_new * restitution;
        }

        // OpenGL rendering
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // passing (x center, y_center, radius)
        drawFilledCircle(0.0f, y_new, .2f);

        SDL_GL_SwapWindow(window);

        // update
        v_old = v_new;
        y_old = y_new;
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


