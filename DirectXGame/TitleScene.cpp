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

	// 説明画像
	uint32_t explanationTex = TextureManager::Load("Explanation.png");
	explanationSprite = Sprite::Create(explanationTex, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

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

//void TitleScene::Update() {
//	if (titlePlay2 == true) {
//		fadeoutSprite2Color.w -= 0.01f;
//		if (fadeoutSprite2Color.w <= 0.0f) {
//			titlePlay2 = false;
//		}
//		fadeSprite2->SetColor(fadeoutSprite2Color);
//	}
//	if (titlePlay2 == false) {
//		if (input_->TriggerKey(DIK_SPACE)) {
//			titlePlay = true;
//		}
//	}
//	if (titlePlay == true) {
//		fadeoutSpriteColor.w += 0.01f;
//	}
//
//	fadeSprite->SetColor(fadeoutSpriteColor);
//
//	if (fadeoutSpriteColor.w >= 1.25f) {
//		isTitleSceneEnd = true;
//	}
//}
//
//void TitleScene::Draw() {
//
//	titleScene->Draw();
//	fadeSprite->Draw();
//	fadeSprite2->Draw();
//}

void TitleScene::Update() {
	if (titlePlay2) {
		fadeoutSprite2Color.w -= 0.01f;
		if (fadeoutSprite2Color.w <= 0.0f) {
			titlePlay2 = false;
			showExplanation = true; // フェード後に説明画像を表示
		}
		fadeSprite2->SetColor(fadeoutSprite2Color);
	}

	if (!titlePlay2 && showExplanation) {
		// スペースで次に進む
		if (input_->TriggerKey(DIK_SPACE)) {
			titlePlay = true;
			showExplanation = false; // 説明を非表示にしてフェード
		}
	}

	if (titlePlay) {
		fadeoutSpriteColor.w += 0.01f;
	}

	fadeSprite->SetColor(fadeoutSpriteColor);

	if (fadeoutSpriteColor.w >= 1.25f) {
		isTitleSceneEnd = true;
	}
}

void TitleScene::Draw() {
	titleScene->Draw();

	if (showExplanation) {
		explanationSprite->Draw(); // 説明画像を描画
	}

	fadeSprite->Draw();
	fadeSprite2->Draw();
}
