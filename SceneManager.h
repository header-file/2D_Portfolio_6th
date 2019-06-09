#pragma once
#include "SingletonBase.h"

class SceneManager : public SingletonBase<SceneManager>
{
	static GameNode*		currentScene;
	static GameNode*		readyScene;

	map<string, GameNode*>	sceneList;

public:
	SceneManager();
	~SceneManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	GameNode*	AddScene(string sceneName, GameNode* scene);
	bool		ChangeScene(string sceneName);
};

