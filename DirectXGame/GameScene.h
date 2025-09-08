#pragma once
#include "PlayScene.h" // PlayScene クラスを読み込む
#include <KamataEngine.h>

using namespace KamataEngine;

class GameScene {
public:
	void Initialize();
	void Update();
	void Draw();
	//シーン切り替え用
	bool isPlaySceneEnd = false;
	bool IsGameEnd() { return isPlaySceneEnd; }
	//SceneType NextScene() { return SceneType::kResult; }


private:
	PlayScene playScene; // PlayScene をメンバとして持つ
};
