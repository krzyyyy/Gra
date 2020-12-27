#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ObjectCounter.h"
#include "IRenderObject.h"
#include "MultidimensionalVector.h"


template<typename ModelCreator>
class RenderObject : private ModelCreator, public IRenderObject
{
public:
	static RenderObject< ModelCreator>& getInstance()
	{
		static RenderObject< ModelCreator> instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
	
	RenderObject(const RenderObject< ModelCreator>& obj) = delete;
	void operator=(RenderObject< ModelCreator> const&) = delete;
	void Initialize();
	void Load();
    using ModelCreator::computeMeshVertexes;
	~RenderObject();
    
private:
	RenderObject() :VAO(-1), VBO(-1)/*, EBO(-1)*/, texture(-1)
	{
		vec = MultidimensionalVector<float, 3>();
	};
	unsigned int VAO;
	unsigned int VBO;
	//unsigned int EBO;
	unsigned int texture;
	MultidimensionalVector<float, 3> vec;
	void addTexture(const std::string& texturePath);
    using ModelCreator::getShape;
};

template<typename Model>
void RenderObject<typename Model>::Initialize()
{

    auto meshPoints = std::vector<cv::Point3f>();
    const double R = 1;
    vec = getShape();
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


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    addTexture("Textures/wall.jpg");
}

template<typename Model>
void RenderObject<typename Model>::Load()
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
template<typename Model>
RenderObject<typename Model>::~RenderObject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
}

template<typename Model>
void RenderObject<typename Model>::addTexture(const std::string& texturePath)
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
    auto data = cv::imread(texturePath, cv::ImreadModes::IMREAD_COLOR);
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