#include "PlayScene.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

void PlayScene::Initialize() {

	srand((unsigned int)time(nullptr));

	// --- テクスチャ読み込み ---
	uint32_t bigTexture = TextureManager::Load("./Resources/BlackCircle.png");
	uint32_t smallTexture = TextureManager::Load("./Resources/WhiteCircle.png");

	Vector2 centerPos = {400.0f, 300.0f};

	// --- スプライト生成（中心を基準に設定） ---
	bigCircle = Sprite::Create(bigTexture, centerPos, {1, 1, 1, 1}, {0.5f, 0.5f});
	smallCircle = Sprite::Create(smallTexture, centerPos, {1, 1, 1, 1}, {0.5f, 0.5f});

	// --- ランダム設定 ---
	R = 50.0f + rand() % 51;
	target = 30.0f + rand() % 51;

	r = R * 0.5f;
	minR = R * 0.2f;
	maxR = R * 0.9f;
	speed = 0.5f;
	direction = 1;

	finished = false;
}

void PlayScene::Update() {

	if (finished)
		return;

	r += speed * direction;
	if (r >= maxR) {
		r = maxR;
		direction = -1;
	}
	if (r <= minR) {
		r = minR;
		direction = 1;
	}

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		float destroyedPercent = ((R * R - r * r) / (R * R)) * 100.0f;
		std::cout << "目標: " << target << "%, 実際: " << destroyedPercent << "%" << std::endl;

		if (std::fabs(target - destroyedPercent) <= 5.0f)
			std::cout << "成功！" << std::endl;
		else
			std::cout << "失敗…" << std::endl;

		finished = true;
	}
}

void PlayScene::Draw() {

	// 大きい円描画
	bigCircle->SetTextureRect({0, 0}, {R * 2, R * 2});
	bigCircle->Draw();

	// 小さい円描画
	smallCircle->SetTextureRect({0, 0}, {r * 2, r * 2});
	smallCircle->Draw();
}
