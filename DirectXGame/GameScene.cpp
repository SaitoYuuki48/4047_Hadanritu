#include "GameScene.h"

void GameScene::Initialize() {
	// PlayScene の初期化
	playScene.Initialize();
	//フェードアウト用
	uint32_t fadeoutSprite = TextureManager::Load("blackout.png");
	fadeSprite = Sprite::Create(fadeoutSprite, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f });
	uint32_t fadeoutSprite2 = TextureManager::Load("blackout.png");
	fadeSprite2 = Sprite::Create(fadeoutSprite2, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f });
	fadeoutSpriteColor = { 1.0f,1.0f,1.0f,1.0f };
	fadeoutSprite2Color = { 1.0f,1.0f,1.0f,0.0f };
	isPlaySceneEnd = false;
	fadePlay = true;
	fade2Play = false;
}
void GameScene::Update() {
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
		// ★ PlaySceneの更新
		playScene.Update();

		// ★ PlaySceneが終了（ゲームオーバーでSpace押された）らフェードアウト開始
		if (playScene.IsFinished()) {
			fade2Play = true;
		}

		if (fade2Play == true) {
			if (fadeoutSprite2Color.w <= 1.0f) {
				fadeoutSprite2Color.w += 0.01f;
			}
			fadeSprite2->SetColor(fadeoutSprite2Color);
		}
		if (fadeoutSprite2Color.w >= 1.0f) {
			isPlaySceneEnd = true; // → TitleSceneへ遷移
		}
	}
}

void GameScene::Draw() {
	// PlayScene の描画
	playScene.Draw();
	fadeSprite->Draw();
	fadeSprite2->Draw();
}