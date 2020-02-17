#include "main.h"
#include "renderer.h"
#include "shader.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<DWORD> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::setupMesh()
{

}