#include "helpers.h"

#define ENGINE_GL_MAJOR 3
#define ENGINE_GL_MINOR 2

char* file_read(const char* filename) {
	SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
	if (rw == NULL) return NULL;

	Sint64 res_size = SDL_RWsize(rw);
	char* res = (char*)malloc(res_size + 1);

	Sint64 nb_read_total = 0, nb_read = 1;
	char* buf = res;
	while (nb_read_total < res_size && nb_read != 0) {
		nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read;
	}
	SDL_RWclose(rw);
	if (nb_read_total != res_size) {
		free(res);
		return NULL;
	}

	res[nb_read_total] = '\0';
	return res;
}

SDL_Window* create_gl_context() {
	SDL_GLContext glcontext = nullptr;
	SDL_Window *window = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error: %s\n", SDL_GetError());
        goto error;
	}

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ENGINE_GL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ENGINE_GL_MINOR);
	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Could not create window: %s\n", SDL_GetError());
        goto error;
    }
	glcontext = SDL_GL_CreateContext(window);
    if (!glcontext) {
        printf("Could not create OpenGL context %s\n", SDL_GetError());
        goto error;
    }

    if (SDL_GL_MakeCurrent(window, glcontext) != 0) {
        printf("Could make OpenGL context current%s\n", SDL_GetError());
        goto error;
    }

    if (gl3wInit()) {
        printf("Could not load OpenGL\n");
        goto error;
    }

    if (!gl3wIsSupported(ENGINE_GL_MAJOR, ENGINE_GL_MINOR)) {
      printf("OpenGL %d.%d not supported\n", ENGINE_GL_MAJOR, ENGINE_GL_MINOR);
      goto error;
    }

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    return window;
error:
    if (window) {
        SDL_DestroyWindow(window);
    }
    if (glcontext) {
        SDL_GL_DeleteContext(glcontext);
    }
    return nullptr;
}

void do_render(SDL_Window *window, std::function<void()> drawFunc) {
	bool done = false;
    SDL_Event event;
    glClearColor(0,0,0,1);
	int width = 1280, height = 720;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
			} else if (event.type == SDL_WINDOWEVENT) {
				switch (event.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						width = event.window.data1; height = event.window.data2;
						break;
				}
            }
        }
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
		drawFunc();
        SDL_GL_SwapWindow(window);
    }

    SDL_GLContext glcontext = SDL_GL_GetCurrentContext();
    if (glcontext) {
        SDL_GL_DeleteContext(glcontext);
    }
	SDL_DestroyWindow(window);
	SDL_Quit();
}

GLuint create_shader(const char *source, GLuint type) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1 ,&source, nullptr);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		GLchar buf[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, buf);
		printf("Shader compilation failed: %s", buf);
		return 0;
	}
	return shader;
}

GLuint create_program(const char *vertex_source, const char *fragment_source) {
	GLuint vertex = create_shader(vertex_source, GL_VERTEX_SHADER);
	GLuint frag = create_shader(fragment_source, GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, frag);
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
      char log[1024];
      glGetProgramInfoLog(program, 1024, nullptr, log);
      printf("Program linking failed: %s", log);
	  return 0;
    }
    return program;
}
