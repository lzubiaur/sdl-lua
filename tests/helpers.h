#include <GL/gl3w.h>
#include <SDL.h>
#include <functional>

char* file_read(const char *filename);
SDL_Window* create_gl_context();
void do_render(SDL_Window *window, std::function<void()> drawFunc);
GLuint create_shader(const char *source, GLuint type);
GLuint create_program(const char *vertex_source, const char *fragment_source);
