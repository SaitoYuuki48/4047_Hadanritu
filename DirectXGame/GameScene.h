#pragma once
#include "PlayScene.h" // PlayScene クラスを読み込む
#include <KamataEngine.h>

using namespace KamataEngine;

class GameScene {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	PlayScene playScene; // PlayScene をメンバとして持つ
};
