#include "RenderObject.h"
#include "MultidimensionalVector.h"
#include <opencv2/opencv.hpp>

using namespace std;




void RenderObject::Initialize()
{
    //vec = { { 0.5f + movement,  0.0f + movement, 0.0f, 1.f, 0.f, 0.f, 1, 1},
    //{ 0.5f + movement, -1.f + movement, 0.0f,  0.f, 1.f, 0.f, 1, 0 },
    //{ -1.f + movement, -1.f + movement, 0.0f,  0.f, 0.f, 1.f, 0, 0},
    //{ -1.f + movement,  0.0f + movement, 0.0f,  1.f, 0.f, 1.f, 0, 1},
    //{ 0.5f + movement,  0.0f + movement, 0.5f, 1.f, 0.f, 0.f, 0.5, 1 },
    //{ 0.5f + movement, -1.f + movement, 0.5f,  0.f, 1.f, 0.f, 1, 0 },
    //{ -1.f + movement, -1.f + movement, 1.0f,  0.f, 0.f, 1.f, 0, 0 },
    //{ -1.f + movement,  0.0f + movement, 1.0f,  1.f, 0.f, 1.f, 0, 1 } };
    vec = { { -0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f, 0.0f, 0.0f },
   { 0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f, 1.0f, 0.0f},
        { 0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
        {0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
        {-0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},

        {-0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
        { 0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
        { 0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
        { 0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
        {-0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
        {-0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},

        {-0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
        {-0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
        {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
        {-0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
        {-0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},

        {0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
        { 0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
        {0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
        {0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
        {0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
        {0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},

        {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
        {0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
        {0.5f, -0.5f,  0.5f, 0.f, 1.f, 0.f, 1.0f, 0.0f},
        { 0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
        {-0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
        {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},

        {-0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
        {0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
        {0.5f,  0.5f,  0.5f, 0.f, 1.f, 0.f, 1.0f, 0.0f},
        { 0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
        {-0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
        {-0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f} 
    };



    //unsigned int indices[] = {  // note that we start from 0!
    //0, 1, 3,   // first triangle
    //1, 2, 3,
    //4, 5, 7,
    //5, 6, 7    // second triangle
    //};


    glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vec.getArraySize(), vec.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    addTexture("Textures/wall.jpg");
}

void RenderObject::Render()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, vec.size());
}

//void RenderObject::Render(const Program& program)
//{
//    auto idProgram = program.getIdProgram();
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glUseProgram(idProgram);
//    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, vec.size());
//}

RenderObject::~RenderObject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
}

void RenderObject::addTexture(const std::string& texturePath)
{

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    auto data = cv::imread(texturePath);
    if (!data.empty())
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.rows, data.cols, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }


}
