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
	isTitleSceneEnd = false;
}

void TitleScene::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		if (isTitleSceneEnd == false) {
			isTitleSceneEnd = true;
		}
	}
}

void TitleScene::Draw() {

	titleScene->Draw();
}
