#include "RenderObject.h"


RenderObject::RenderObject():VAO(-1), VBO(-1), EBO(-1)
{
}

void RenderObject::Initialize(float movement)
{
  float vertices[] = {
      0.0f + movement,  0.0f + movement, 0.0f, 1.f, 0.f, 0.f,   // top right
      0.0f + movement, -1.f + movement, 0.0f,  0.f, 1.f, 0.f, // bottom right
     -1.f + movement, -1.f + movement, 0.0f,  0.f, 0.f, 1.f, // bottom left
     -1.f + movement,  0.0f + movement, 0.0f,  1.f, 0.f, 1.f,  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void RenderObject::Render(const Program& program)
{
    auto idProgram = program.getIdProgram();
    glUseProgram(idProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

RenderObject::~RenderObject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
