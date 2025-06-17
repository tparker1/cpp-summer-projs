#include <SDL2/SDL.h>
#include <GL/gl.h>

/*
Add movement to the static triangle by updating its y-position on the screen at each iteration
*/

int main() {
    // Initialize SDL with video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    // Create SDL window with OpenGL context
    SDL_Window* window = SDL_CreateWindow(" moving triangle ",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    // Main loop
    auto y_position = 0.0f; // set the vertical position of the triangle (where the center of the triangle is)
    auto triangle_size = 0.2f; // set the size (1/2 length) of the triangle (triangle will have height=2*size)
    auto y_change = 0.02f; // how much the triangle should move at each frame

    bool running = true;
    SDL_Event event;
    while (running) {
        // update the height/position of the triangle on the screen
        y_position += y_change;

        // If the triangle reaches the top of the screen, start going down instead
        if ((y_position+triangle_size) > 1){ 
            y_position = 1 - triangle_size; // set the top of triangle to the top of screen
            y_change = -1*y_change; // reverse direction
        }
        // If the triangle reaches the bottom of the screen, start going up instead
        if ((y_position-triangle_size) < -1){ 
            y_position = -1 + triangle_size; // set the bottom of triangle to the bottom of screen
            y_change = -1*y_change; // reverse direction
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        
        // CHANGE SDL_DELAY IF TOO FAST OR SLOW
        SDL_Delay(100); 


        // OpenGL rendering
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
            // top vertex 
            glColor3f(1.0, 0.0, 0.0); // Red
            glVertex2f(0.0f, y_position+triangle_size);

            // left vertex
            glColor3f(0.0, 1.0, 0.0); // Green
            glVertex2f(-triangle_size, y_position-triangle_size);

            // right vertex
            glColor3f(0.0, 0.0, 1.0); // Blue
            glVertex2f(triangle_size, y_position-triangle_size);
        glEnd();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}