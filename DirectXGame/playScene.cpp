#include "PlayScene.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

void PlayScene::Initialize() {
	srand((unsigned int)time(nullptr));

	// --- 数字スプライト（目標用） ---
	for (int i = 0; i < 10; i++) {
		uint32_t tex = TextureManager::Load(std::to_string(i) + ".png");
		digitSprites[i] = Sprite::Create(tex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
		digitSprites[i]->SetSize({90, 90});
	}

	// --- 数字スプライト（誤差用） ---
	for (int i = 0; i < 10; i++) {
		uint32_t tex = TextureManager::Load(std::to_string(i) + ".png");
		toleranceDigits[i] = Sprite::Create(tex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
		toleranceDigits[i]->SetSize({60, 60});
	}

	// --- 数字スプライト（結果用） ---
	for (int i = 0; i < 10; i++) {
		uint32_t tex = TextureManager::Load(std::to_string(i) + ".png");
		resultDigits[i] = Sprite::Create(tex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
		resultDigits[i]->SetSize({90, 90});
	}

	// --- 記号スプライト ---
	uint32_t textTex = TextureManager::Load("Text.png");
	uint32_t percentTex = TextureManager::Load("%.png");
	uint32_t tolTex = TextureManager::Load("+-.png");

	textSprite = Sprite::Create(textTex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	textSprite->SetSize({500, 500});

	percentSprite = Sprite::Create(percentTex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	percentSprite->SetSize({60, 60}); // 誤差用に小さくも使える

	toleranceSprite = Sprite::Create(tolTex, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	toleranceSprite->SetSize({60, 60});

	// --- 円スプライト ---
	uint32_t bigTex = TextureManager::Load("BlackCircle.png");
	uint32_t smallTex = TextureManager::Load("WhiteCircle.png");

	Vector2 centerPos = {640.0f, 360.0f};
	bigCircle = Sprite::Create(bigTex, centerPos, {1, 1, 1, 1}, {0.5f, 0.5f});
	smallCircle = Sprite::Create(smallTex, centerPos, {1, 1, 1, 1}, {0.5f, 0.5f});

	level = 1;
	finished = false;
	SetupStage();
}

void PlayScene::SetupStage() {
	R = 100.0f + rand() % 101; // 半径 100〜200

	target = 15.0f + rand() % 66; // 15〜80%

	tolerance = 15.0f - (level - 1);
	if (tolerance < 5.0f)
		tolerance = 5.0f;

	r = R * 0.5f;
	minR = R * 0.01f;
	maxR = R;

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
		float destroyedPercentF = (r / R) * 100.0f;
		int destroyedPercent = (int)roundf(destroyedPercentF);

		if (fabs(target - destroyedPercent) <= tolerance) {
			level++;
			SetupStage();
		} else {
			finished = true;
		}
	}
}

void PlayScene::DrawNumber(int value, Vector2 pos, Sprite* sprites[10], int spacing) {
	std::string str = std::to_string(value);
	float offsetX = 0.0f;

	for (char c : str) {
		int digit = c - '0';
		if (digit < 0 || digit > 9)
			continue;

		sprites[digit]->SetPosition({pos.x + offsetX, pos.y});
		sprites[digit]->Draw();

		offsetX += spacing;
	}
}

void PlayScene::Draw() {
	// 円
	bigCircle->SetSize({R * 2, R * 2});
	bigCircle->Draw();
	smallCircle->SetSize({r * 2, r * 2});
	smallCircle->Draw();

	// === 目標 ===
	Vector2 targetPos = {50, 50};
	DrawNumber((int)target, targetPos, digitSprites, 70);

	int digits = (int)std::to_string((int)target).size();
	float textOffsetX = targetPos.x + digits * 70 + 150;
	textSprite->SetPosition({textOffsetX, targetPos.y});
	textSprite->Draw();

	// === 誤差 ===
	Vector2 tolPos = {targetPos.x, targetPos.y + 150};
	toleranceSprite->SetPosition(tolPos);
	toleranceSprite->Draw();

	DrawNumber((int)tolerance, {tolPos.x + 80, tolPos.y}, toleranceDigits, 60);

	percentSprite->SetSize({60, 60});
	percentSprite->SetPosition({tolPos.x + 80 + 60, tolPos.y});
	percentSprite->Draw();

	// === 結果 ===
	if (finished) {
		Vector2 resultPos = {50, 350};
		int result = (int)roundf((r / R) * 100.0f);
		DrawNumber(result, resultPos, resultDigits, 70);

		int resDigits = (int)std::to_string(result).size();
		float percentOffsetX = resultPos.x + resDigits * 70 + 150;
		percentSprite->SetSize({500, 500}); // 結果表示は大きく
		percentSprite->SetPosition({percentOffsetX, resultPos.y});
		percentSprite->Draw();
	}
}
