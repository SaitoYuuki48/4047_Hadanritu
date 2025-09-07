#pragma once
#include "Scene.h"
#include "KamataEngine.h"
using namespace KamataEngine;

class TitleScene {
public:

	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画
	void Draw();

	//シーン切り替え用
	bool isTitleSceneEnd = false;
	bool IsTitleEnd() { return isTitleSceneEnd; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Sprite* titleScene = nullptr;
};

