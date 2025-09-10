#pragma once
#include "PlayScene.h" // PlayScene クラスを読み込む
#include "Scene.h"
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
	SceneType NextScene() { return SceneType::kTitle; }


private:
	PlayScene playScene; // PlayScene をメンバとして持つ
	Sprite* fadeSprite = nullptr;
	Sprite* fadeSprite2 = nullptr;
	//フェードアウト用の変数
	Vector4 fadeoutSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	Vector4 fadeoutSprite2Color = { 1.0f,1.0f,1.0f,1.0f };
	bool fadePlay = true;
	bool fade2Play = false;
};
