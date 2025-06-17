#include <SDL2/SDL.h>
#include <GL/gl.h>

/*
Add physics/gravity to the moving triangle (triangle_move)
*/

int main() {
    // Initialize SDL with video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    // Create SDL window with OpenGL context
    SDL_Window* window = SDL_CreateWindow(" bouncing triangle ",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
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
        
        // Update triangle position
        v_new = v_old + g*dt;
        y_new = y_old + v_old*dt + 0.5*g*dt*dt;

        // Bounce logic at floor
        if (y_new < view_floor){
            // stopping condition to avoid jiggle:
            // if the change in y is very small, just set velocity to zero 
            if (abs(y_new - y_old) < epsilon){
                v_new = 0;
            }
            y_new = view_floor;
            v_new = -v_new * restitution;
        }

        // OpenGL rendering
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
            // top vertex
            glColor3f(1.0, 0.0, 0.0); // Red
            glVertex2f(0.0f, y_new + 0.2f);

            // left vertex
            glColor3f(0.0, 1.0, 0.0); // Green
            glVertex2f(-0.2f, y_new - 0.2f);

            // right vertex
            glColor3f(0.0, 0.0, 1.0); // Blue
            glVertex2f(0.2f, y_new - 0.2f);
        glEnd();

        SDL_GL_SwapWindow(window);

        v_old = v_new;
        y_old = y_new;
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}