#include "TitleScene.h"

void TitleScene::Initialize() {
	input_ = KamataEngine::Input::GetInstance();
	//テクスチャ
	//uint32_t titleScene = KamataEngine::TextureManager::Load("Scene/Title.png");
	//sprite = KamataEngine::Sprite::Create(titleScene, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f });
}

void TitleScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		if (isSceneEnd == false) {
			isSceneEnd = true;
		}
	}
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	sprite->Draw();
}

