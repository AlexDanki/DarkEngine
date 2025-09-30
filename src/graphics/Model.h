#pragma once


//#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <stb_image_resize2.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
    // model data 
    vector<graph::Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
    bool loaded = false;
    const aiScene* loadedScene;
    //Assimp::Importer importer;

    // constructor, expects a filepath to a 3D model.
    Model(const aiScene* _scene ,string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(_scene, path);
        setupModel();
    }

	void setupModel()
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].setupMesh();
	}

    bool loadedWithSucess(const aiScene* scene)
    {
        return scene && !(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode && scene->HasMeshes();
    }

    // draws the model, and thus all its meshes
    void Draw(Shader& shader)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            //shader.use();
            meshes[i].draw(shader);
        }
            
    }

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(const aiScene* scene, string const& path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<graph::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);


    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
};