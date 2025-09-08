#include "GameScene.h"

void GameScene::Initialize() {
	// PlayScene の初期化
	playScene.Initialize();
	//フェードアウト用
	uint32_t fadeoutSprite = TextureManager::Load("blackout.png");
	fadeSprite = Sprite::Create(fadeoutSprite, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f });
	fadeoutSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	isPlaySceneEnd = false;
	dafePlay = true;
}

void GameScene::Update() {
	if (dafePlay == true) {
		if (fadeoutSpriteColor.w >= 0.0f) {
			fadeoutSpriteColor.w -= 0.01f;
		}
	}
	if (fadeoutSpriteColor.w <= 0.0f) {
		dafePlay = false;
	}
	fadeSprite->SetColor(fadeoutSpriteColor);
	if (dafePlay == false) {
		// PlayScene の更新
		playScene.Update();
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			if (isPlaySceneEnd == false) {
				isPlaySceneEnd = true;
			}
		}
	}
}

void GameScene::Draw() {
	// PlayScene の描画
	playScene.Draw();
	fadeSprite->Draw();
}