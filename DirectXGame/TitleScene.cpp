#include "TitleScene.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

void TitleScene::Initialize() {
	input_ = KamataEngine::Input::GetInstance();
	//テクスチャ
	uint32_t titleSceneSprite = TextureManager::Load("Title.png");
	titleScene = Sprite::Create(titleSceneSprite, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f });
	//フェードアウト用
	uint32_t fadeoutSprite = TextureManager::Load("blackout.png");
	fadeSprite = Sprite::Create(fadeoutSprite, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f });
	fadeoutSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	uint32_t fadeoutSprite2 = TextureManager::Load("blackout.png");
	fadeSprite2 = Sprite::Create(fadeoutSprite2, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f });
	fadeoutSpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	fadeoutSprite2Color = { 1.0f,1.0f,1.0f,1.0f };
	isTitleSceneEnd = false;
	titlePlay = false;
	titlePlay2 = true;
	isTitleSceneEnd = false;
}

void TitleScene::Update() {
	if (titlePlay2 == true) {
		fadeoutSprite2Color.w -= 0.01f;
		if (fadeoutSprite2Color.w <= 0.0f) {
			titlePlay2 = false;
		}
		fadeSprite2->SetColor(fadeoutSprite2Color);
	}
	if (titlePlay2 == false) {
		if (input_->TriggerKey(DIK_SPACE)) {
			titlePlay = true;
		}
	}
	if (titlePlay == true) {
		fadeoutSpriteColor.w += 0.01f;
	}

	fadeSprite->SetColor(fadeoutSpriteColor);

	if (fadeoutSpriteColor.w >= 1.25f) {
		isTitleSceneEnd = true;
	}
}

void TitleScene::Draw() {

	titleScene->Draw();
	fadeSprite->Draw();
	fadeSprite2->Draw();
}
