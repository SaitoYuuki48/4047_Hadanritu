#include "ResultScene.h"
void ResultScene::Initialize() {
	isResultSceneEnd = false;
	//フェードアウト用
	uint32_t fadeoutSprite = TextureManager::Load("blackout.png");
	fadeSprite = Sprite::Create(fadeoutSprite, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f });
	fadeoutSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	fadePlay = true;
}

void ResultScene::Update() {
	if (fadePlay == true) {
		if (fadeoutSpriteColor.w >= 0.0f) {
			fadeoutSpriteColor.w -= 0.01f;
		}
		fadeSprite->SetColor(fadeoutSpriteColor);
	}
	if (fadeoutSpriteColor.w <= 0.0f) {
		fadePlay = false;
	}
	if (fadePlay == false) {
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			if (isResultSceneEnd == false) {
				isResultSceneEnd = true;
			}
		}
	}
}

void ResultScene::Draw() {
	fadeSprite->Draw();
}