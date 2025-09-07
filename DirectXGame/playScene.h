#pragma once
#include "Scene.h"
#include <KamataEngine.h>
using namespace KamataEngine;

class PlayScene {
public:
	void Initialize();
	void Update();
	void Draw();

	//シーン切り替え用
	bool isPlaySceneEnd = false;
	bool IsSceneEnd() { return isPlaySceneEnd; }
	SceneType NextScene() { return SceneType::kResult; }

private:
	Sprite* bigCircle = nullptr;
	Sprite* smallCircle = nullptr;

	float R; // 大きい円の半径
	float r; // 小さい円の半径
	float minR;
	float maxR;
	float speed;
	int direction;

	float target;  // 目標破壊率
	bool finished; // 判定済みフラグ


	Input* input_ = nullptr;
};
