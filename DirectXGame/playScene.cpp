#include "PlayScene.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

void PlayScene::Initialize() {
	srand((unsigned int)time(nullptr));

	// --- 数字スプライト（0〜9） ---
	for (int i = 0; i < 10; i++) {
		std::string filename = std::to_string(i) + ".png";
		uint32_t tex = TextureManager::Load(filename);
		digitSprites[i] = Sprite::Create(tex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
		digitSprites[i]->SetSize({90, 90}); // 数字は 90x90
	}

	// --- 記号スプライト ---
	uint32_t textTex = TextureManager::Load("Text.png");
	uint32_t percentTex = TextureManager::Load("%.png");

	textSprite = Sprite::Create(textTex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	textSprite->SetSize({500, 500});

	percentSprite = Sprite::Create(percentTex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	percentSprite->SetSize({500, 500});

	// --- 円スプライト ---
	uint32_t bigTex = TextureManager::Load("BlackCircle.png");
	uint32_t smallTex = TextureManager::Load("WhiteCircle.png");

	Vector2 centerPos = {640.0f, 360.0f};
	bigCircle = Sprite::Create(bigTex, centerPos, {1, 1, 1, 1}, {0.5f, 0.5f});
	smallCircle = Sprite::Create(smallTex, centerPos, {1, 1, 1, 1}, {0.5f, 0.5f});

	// --- 初期設定 ---
	level = 1;
	finished = false;
	SetupStage();
}

void PlayScene::SetupStage() {
	R = 50.0f + rand() % 51;
	target = 30.0f + rand() % 51;

	tolerance = 15.0f - (level - 1);
	if (tolerance < 5.0f)
		tolerance = 5.0f;

	r = R * 0.5f;
	minR = R * 0.2f;
	maxR = R * 0.9f;

	speed = 0.5f + (level - 1) * 0.1f;
	direction = 1;
	finished = false;
}

void PlayScene::Update() {
	if (finished)
		return;

	// 白丸の伸縮
	r += speed * direction;
	if (r >= maxR) {
		r = maxR;
		direction = -1;
	}
	if (r <= minR) {
		r = minR;
		direction = 1;
	}

	// Spaceキーで判定
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		// 半径比で破壊率を計算（直感的）
		float destroyedPercentF = (r / R) * 100.0f;
		int destroyedPercent = (int)roundf(destroyedPercentF);

		std::cout << "レベル: " << level << std::endl;
		std::cout << "目標: " << target << "%, 実際: " << destroyedPercent << "% (許容誤差 ±" << tolerance << "%)" << std::endl;

		if (fabs(target - destroyedPercent) <= tolerance) {
			std::cout << "成功！次のレベルへ！" << std::endl;
			level++;
			SetupStage();
		} else {
			std::cout << "ゲームオーバー…" << std::endl;
			finished = true;
		}
	}
}

void PlayScene::DrawNumber(int value, Vector2 pos) {
	std::string str = std::to_string(value);
	float offsetX = 0.0f;

	for (char c : str) {
		int digit = c - '0';
		if (digit < 0 || digit > 9)
			continue;

		digitSprites[digit]->SetPosition({pos.x + offsetX, pos.y});
		digitSprites[digit]->Draw();

		offsetX += 90; // 数字サイズに合わせた間隔
	}
}

void PlayScene::Draw() {
	// 円
	bigCircle->SetSize({R * 2, R * 2});
	bigCircle->Draw();
	smallCircle->SetSize({r * 2, r * 2});
	smallCircle->Draw();

	// --- 目標（左上） ---
	Vector2 targetPos = {50, 50};
	DrawNumber((int)target, targetPos);

	int digits = (int)std::to_string((int)target).size();
	float textOffsetX = targetPos.x + digits * 90 + 150;
	textSprite->SetPosition({textOffsetX, targetPos.y});
	textSprite->Draw();

	// --- 結果（Space 後、少し下に表示） ---
	if (finished) {
		Vector2 resultPos = {50, 200};
		int result = (int)roundf((r / R) * 100.0f);
		DrawNumber(result, resultPos);

		int resDigits = (int)std::to_string(result).size();
		float percentOffsetX = resultPos.x + resDigits * 90 + 150;
		percentSprite->SetPosition({percentOffsetX, resultPos.y});
		percentSprite->Draw();
	}
}
