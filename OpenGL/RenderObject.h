#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ObjectCounter.h"
#include "IRenderObject.h"
#include "MultidimensionalVector.h"


class RenderObject : public IRenderObject
{
public:
	static RenderObject& getInstance()
	{
		static RenderObject instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
	
	RenderObject(const RenderObject& obj) = delete;
	void operator=(RenderObject const&) = delete;
	void Initialize();
	void Render();
	//void Render(const Program& program);
	~RenderObject();

private:
	RenderObject() :VAO(-1), VBO(-1)/*, EBO(-1)*/, texture(-1)
	{
		vec = MultidimensionalVector<float, 3, 3, 2>();
	};
	unsigned int VAO;
	unsigned int VBO;
	//unsigned int EBO;
	unsigned int texture;
	MultidimensionalVector<float, 3, 3, 2> vec;
	void addTexture(const std::string& texturePath);
	
};

