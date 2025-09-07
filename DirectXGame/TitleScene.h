#pragma once
#include <Windows.h>
#include "Scene.h"
#include "KamataEngine.h"
class TitleScene{
public:

	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画
	void Draw();

	//リセット
	void sceneReset();

	//シーン切り替え用
	bool isSceneEnd = false;
	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Sprite* sprite;
};

