#include "Game.h"
#include "SceneManager.h"

GameNode* SceneManager::currentScene = NULL;
GameNode* SceneManager::readyScene = NULL;
//신 생성과 추가, 해제, 이미지 처리는 메인 게임에서
//신 교체만 매니저에서 하는 것이 좋다.(안정성 면에서)

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	currentScene = NULL;
	readyScene = NULL;
}

void SceneManager::Release()
{
	map<string, GameNode*>::iterator it;

	for (it = sceneList.begin(); it != sceneList.end();)
	{
		if (it->second != NULL)
		{
			if (it->second == currentScene)
				it->second->Release();

			delete it->second;
			it = sceneList.erase(it);
		}
		else
			it++;
	}

	sceneList.clear();
}

void SceneManager::Update()
{
	if (currentScene)
		currentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
		currentScene->Render(hdc);
}

GameNode* SceneManager::AddScene(string sceneName, GameNode * scene)
{
	if (!scene)
		return NULL;

	sceneList.insert(make_pair(sceneName, scene));

	return scene;
}

bool SceneManager::ChangeScene(string sceneName)
{
	map<string, GameNode*>::iterator it;

	it = sceneList.find(sceneName);

	if(it == sceneList.end())
		return false;

	if (it->second == currentScene)
		return false;

	if (it->second->Init())
	{
		if (currentScene)
			currentScene->Release();

		currentScene = it->second;

		return true;
	}

	return false;
}
