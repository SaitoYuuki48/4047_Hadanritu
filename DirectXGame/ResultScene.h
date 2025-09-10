#pragma once
#include "Scene.h"
#include "KamataEngine.h"
using namespace KamataEngine;
class ResultScene
{
public:
	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画
	void Draw();

	//シーン切り替え用
	bool isResultSceneEnd = false;
	bool IsResultEnd() { return isResultSceneEnd; }
	SceneType NextScene() { return SceneType::kTitle; }

private:
	Sprite* fadeSprite = nullptr;
	Vector4 fadeoutSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	bool fadePlay = true;
};

