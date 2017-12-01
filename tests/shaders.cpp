#include "helpers.h"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Shader test", "[RENDERING]") {

    char *vertex_source = file_read("shader.vert");
    if (!vertex_source) {
        std::cout << "Could not read vertex shader file." << std::endl;
    }

    char *frag_source = file_read("shader.frag");
    if (!frag_source) {
        std::cout << "Could not read fragment shader file." << std::endl;
    }

    SDL_Window* window = create_gl_context();
    if (!window) {
        return;
    }

    std::vector<GLfloat> vertices = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
    };

    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    GLuint program = create_program(vertex_source, frag_source);

    do_render(window,[&]() {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    });

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
