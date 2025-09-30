#include "LoadData.h"


void Data::LoadData::Load()
{
	if (isLoaded) return;

	//guyScene = LoadSceneModel(guyModelPath, "Guy Model");
	//camScene = LoadSceneModel(camModelPath, "Camera Model");
	shotgunScene = LoadSceneModel(shotgunModelPath, "Shotgun Model");
	groundScene = LoadSceneModel(groundModelPath, "Ground Model");
	bunkerScene = LoadSceneModel(bunkerModelPath, "Bunker Model");
	buildScene = LoadSceneModel(buildModelPath, "Build Model");
	lightScene = LoadSceneModel(lightModelPath, "Light Model");

	callScenes();

	isLoaded = true;
}

bool Data::LoadData::AllDataLoaded()
{

	return 
		shotgunScene &&
		groundScene &&
		bunkerScene &&
		buildScene;
}

const aiScene* Data::LoadData::LoadSceneModel(const std::string& path, const std::string& name)
{
	auto model = std::make_unique<SceneModel>();
	model->name = name;
	model->scene = model->importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!model->scene || model->scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !model->scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP:: " << model->importer.GetErrorString() << " (" << name << ")\n";
		return nullptr;
	}

	std::cerr << name << ": " << " Loaded with success!\n";
	const aiScene* sceneRef = model->scene;
	loadedModels.push_back(std::move(model));
	return sceneRef;
}

void Data::LoadData::callScenes()
{
	for(auto s : scenes)
	{
		std::cerr << s << ": Loaded\n";
	}
}
