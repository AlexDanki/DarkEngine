#pragma once
#include "../graphics/Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "../graphics/Mesh.h"
#include <vector>


namespace Data
{
	class LoadData {

	public:

		struct SceneModel {
			Assimp::Importer importer;
			const aiScene* scene;
			std::string name;
		};

		const aiScene* guyScene;
		const aiScene* camScene;
		const aiScene* shotgunScene;
		const aiScene* groundScene;
		const aiScene* bunkerScene;
		const aiScene* buildScene;
		const aiScene* lightScene;

		std::string const& guyModelPath = "./assets/models/guy/guy.obj";
		std::string const& camModelPath = "./assets/models/camera/camera.obj";
		std::string const& shotgunModelPath = "./assets/models/shotgun/shotgun.obj";
		std::string const& groundModelPath = "./assets/models/ground2/ground2.obj";
		std::string const& bunkerModelPath = "./assets/models/bunker/bunker.obj";
		std::string const& buildModelPath = "./assets/models/build/build.obj";
		std::string const& lightModelPath = "./assets/models/light/light.obj";

		//const aiScene* scene;
		const aiScene* loadedScene;
		std::vector<const aiScene*> scenes;
		std::vector<std::unique_ptr<SceneModel>> loadedModels;
		std::vector <Assimp::Importer> importers;
		std::string directory;
		vector<Mesh*> meshes;

		void Load();

		bool AllDataLoaded();

		const aiScene* LoadSceneModel(std::string const& path, std::string const& name);

		void callScenes();
	private:
		bool isLoaded;
	};


}
