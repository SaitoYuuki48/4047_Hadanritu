#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class PlayScene {
public:
	void Initialize();
	void Update();
	void Draw();

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
};
