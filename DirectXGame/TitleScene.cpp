#include "TitleScene.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

void TitleScene::Initialize() {
	input_ = KamataEngine::Input::GetInstance();
	//テクスチャ
	//uint32_t titleSceneSprite = TextureManager::Load("Title.png");
	//titleScene = Sprite::Create(titleSceneSprite, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f });
}

void TitleScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		if (isTitleSceneEnd == false) {
			isTitleSceneEnd = true;
		}
	}
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	//titleScene->Draw();
}

