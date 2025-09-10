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
	Sprite* fadeSprite = nullptr;
	Sprite* fadeSprite2 = nullptr;
	//フェードアウト用の変数
	Vector4 fadeoutSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	Vector4 fadeoutSprite2Color = { 1.0f,1.0f,1.0f,1.0f };
	bool titlePlay = false;
	bool titlePlay2 = false;
};

