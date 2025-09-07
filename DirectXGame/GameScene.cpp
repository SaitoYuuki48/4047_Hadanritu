#include "GameScene.h"

void GameScene::Initialize() {
	// PlayScene の初期化
	playScene.Initialize();
	isPlaySceneEnd = false;
}

void GameScene::Update() {
	// PlayScene の更新
	playScene.Update();
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		if (isPlaySceneEnd == false) {
			isPlaySceneEnd = true;
		}
	}
}

void GameScene::Draw() {
	// PlayScene の描画
	playScene.Draw();
}