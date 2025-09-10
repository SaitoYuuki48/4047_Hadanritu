#include "PlayScene.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

void PlayScene::Initialize() {
	srand((unsigned int)time(nullptr));

	// 数字テクスチャの読み込み
	for (int i = 0; i < 10; i++) {
		digitTextures[i] = TextureManager::Load(std::to_string(i) + ".png");
	}

	// 背景
	uint32_t backHandle = TextureManager::Load("WhiteBack.png");
	textureBackground_ = Sprite::Create(backHandle, {0, 0});

	// 記号スプライト
	textTexture = TextureManager::Load("Text.png");
	percentTexture = TextureManager::Load("%.png");
	toleranceTexture = TextureManager::Load("+-.png");

	textSprite = Sprite::Create(textTexture, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	textSprite->SetSize({330, 330});

	percentSprite = Sprite::Create(percentTexture, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	percentSprite->SetSize({60, 60});

	toleranceSprite = Sprite::Create(toleranceTexture, {0, 0}, {1, 1, 1, 1}, {0.5f, 0.5f});
	toleranceSprite->SetSize({60, 60});

	// 円スプライト
	uint32_t bigTex = TextureManager::Load("BlackCircle.png");
	uint32_t smallTex = TextureManager::Load("WhiteCircle.png");

	Vector2 centerPos = {640.0f, 360.0f};
	bigCircle = Sprite::Create(bigTex, centerPos, {1, 1, 1, 1}, {0.5f, 0.5f});
	smallCircle = Sprite::Create(smallTex, centerPos, {1, 1, 1, 1}, {0.5f, 0.5f});

	// 黒背景 (フェード用)
	uint32_t blackTex = TextureManager::Load("blackout.png");
	blackOverlay = Sprite::Create(blackTex, {0, 0}, {1, 1, 1, 0.0f}, {0.0f, 0.0f});
	blackOverlay->SetSize({1280, 720});

	level = 1;
	finished = false;
	state = GameState::Playing;

	SetupStage();
}

void PlayScene::SetupStage() {
	R = 100.0f + rand() % 101;
	target = 15.0f + rand() % 66;

	tolerance = 15.0f - (level - 1);
	if (tolerance < 5.0f)
		tolerance = 5.0f;

	r = R * 0.5f;
	minR = R * 0.01f;
	maxR = R;

	speed = 0.5f + (level - 1) * 0.1f;
	direction = 1;
	finished = false;

	overlayAlpha = 0.0f;
}

void PlayScene::Update() {
	if (state == GameState::Playing) {
		// 円の伸縮
		r += speed * direction;
		if (r >= maxR) {
			r = maxR;
			direction = -1;
		}
		if (r <= minR) {
			r = minR;
			direction = 1;
		}

		// Space押したらリザルトへ
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			finalResult = (int)roundf((r / R) * 100.0f);
			displayedResult = 0;
			overlayAlpha = 0.0f;
			state = GameState::ResultFadeIn;
		}
	} else if (state == GameState::ResultFadeIn) {
		// フェードイン（1秒でα=0.7）
		overlayAlpha += 0.012f;
		if (overlayAlpha >= 0.7f) {
			overlayAlpha = 0.7f;
			state = GameState::ResultCounting;
		}
	} else if (state == GameState::ResultCounting) {
		// カウントアップ
		if (displayedResult < finalResult) {
			displayedResult += 1;
			if (displayedResult > finalResult) {
				displayedResult = finalResult;
			}
		} else {
			state = GameState::ResultWait;
		}
	} else if (state == GameState::ResultWait) {
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			if (fabs(target - finalResult) <= tolerance) {
				level++;
				SetupStage();
				state = GameState::Playing;
			} else {
				state = GameState::GameOver;
			}
		}
	} else if (state == GameState::GameOver) {
		// 今は結果％だけ表示
	}
}

void PlayScene::DrawNumber(int value, Vector2 pos, uint32_t textures[10], int spacing, Vector2 size) {
	std::string str = std::to_string(value);
	float totalWidth = (str.size() * size.x) + (spacing * (str.size() - 1));

	// pos を中央として全体をずらす
	float startX = pos.x - totalWidth / 2.0f;
	float offsetX = 0.0f;

	for (char c : str) {
		int digit = c - '0';
		if (digit < 0 || digit > 9)
			continue;

		Sprite* temp = Sprite::Create(textures[digit], {startX + offsetX, pos.y}, {1, 1, 1, 1}, {0.5f, 0.5f});
		temp->SetSize(size);
		temp->Draw();
		//delete temp;

		offsetX += size.x + spacing; // spacingを広めに
	}
}

void PlayScene::Draw() {
	textureBackground_->Draw();

	if (state == GameState::Playing) {
		bigCircle->SetSize({R * 2, R * 2});
		bigCircle->Draw();
		smallCircle->SetSize({r * 2, r * 2});
		smallCircle->Draw();

		// 目標の表示（左上）
		Vector2 targetPos = {150, 70};
		DrawNumber((int)target, targetPos, digitTextures, 0, {90, 90});

		int digits = (int)std::to_string((int)target).size();
		float textOffsetX = targetPos.x + digits * 70 + 50;
		textSprite->SetPosition({textOffsetX, targetPos.y - 10});
		textSprite->Draw();

		// 誤差の表示
		Vector2 tolPos = {targetPos.x , targetPos.y + 100};
		toleranceSprite->SetPosition(tolPos);
		toleranceSprite->Draw();

		DrawNumber((int)tolerance, {tolPos.x + 120, tolPos.y - 0}, digitTextures, 0, {60, 60});
		percentSprite->SetSize({60, 60});
		percentSprite->SetPosition({tolPos.x + 80 + 100, tolPos.y + 10});
		percentSprite->Draw();
	}

	// リザルト演出
	if (state == GameState::ResultFadeIn || state == GameState::ResultCounting || state == GameState::ResultWait) {

		blackOverlay->SetColor({1, 1, 1, overlayAlpha});
		blackOverlay->Draw();
	}

	if (state == GameState::ResultCounting || state == GameState::ResultWait || state == GameState::GameOver) {
		Vector2 resultPos = {640, 360}; // 中央
		DrawNumber(displayedResult, resultPos, digitTextures, 0, {180, 180});

		// 数字列の右端に % を配置
		int resDigits = (int)std::to_string(displayedResult).size();
		float totalWidth = (resDigits * 180.0f) + (30.0f * (resDigits - 1));
		float percentOffsetX = resultPos.x + totalWidth / 2.0f + 90;

		percentSprite->SetSize({180, 180});
		percentSprite->SetPosition({percentOffsetX, resultPos.y});
		percentSprite->Draw();

	}
}
