#pragma once
#include "../graphics/Model.h"


namespace Data
{
	class LoadData {

	public:

		Model* guyModel;
		Model* camModel;
		Model* shotgunModel;
		Model* groundModel;
		Model* bunkerModel;

		void Load()
		{

			guyModel = new Model("./assets/models/guy/guy.obj");
			camModel = new Model("./assets/models/camera/camera.obj");
			shotgunModel = new Model("./assets/models/shotgun/shotgun.obj");
			groundModel = new Model("./assets/models/ground2/ground2.obj");
			bunkerModel = new Model("./assets/models/bunker/bunker.obj");

		};

		bool AllDataLoaded()
		{
			if (guyModel->loadedWithSucess(guyModel->loadedScene) &&
				camModel->loadedWithSucess(camModel->loadedScene) &&
				shotgunModel->loadedWithSucess(shotgunModel->loadedScene) &&
				groundModel->loadedWithSucess(groundModel->loadedScene) &&
				bunkerModel->loadedWithSucess(bunkerModel->loadedScene))
			{
				return true;
			}

			return false;
		}
	};
}
