//#include <Windows.h>
//#include "KamataEngine.h"
//#include "GameScene.h"
//
//using namespace KamataEngine;
//
//// Windowsアプリでのエントリーポイント(main関数)
//int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
//	
//	// DirectXCommonインスタンスの取得
//	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
//	//エンジンの初期化
//	KamataEngine::Initialize(L"4047_破断率");
//
//	//ゲームシーンのインスタンス生成
//	GameScene* gameScene = new GameScene();
//	//ゲームシーンの初期化
//	gameScene->Initialize();
//	
//	//メインループ
//	while (true) {
//		// エンジンの更新
//		if (KamataEngine::Update()) {
//			break;
//		}
//
//		//ゲームシーンの更新
//
//		//描画開始
//		dxCommon->PreDraw();
//
//		//ここに描画処理を記述する
//		
//		//スプライト描画前処理
//		Sprite::PreDraw();
//		
//		// ゲームシーンの描画
//		gameScene->Draw();
//
//		// 描画終了
//		dxCommon->PostDraw();
//	}
//
//	//ゲームシーンの解放
//	delete gameScene;
//	// nullptrの代入
//	gameScene = nullptr;
//
//	//エンジンの修了処理
//	KamataEngine::Finalize();
//
//	return 0;
//}

#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>
#include "KamataEngine.h"
#include "GameScene.h"
#include "TitleScene.h"

using namespace KamataEngine;

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	uint32_t titleSceneSprite = TextureManager::Load("./Resources/Scene/Title.png");
	Sprite* sprite = Sprite::Create(titleSceneSprite, { 100.0f, 100.0f });
	TitleScene* titleScene = nullptr;
	//タイトルシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();

	SceneType sceneNo = SceneType::kTitle;

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// エンジン初期化
	KamataEngine::Initialize(L"4047_破断率");

	// GameScene インスタンス生成
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	// メインループ
	while (true) {

		// エンジン更新
		if (KamataEngine::Update()) {
			break;
		}

		////シーンごとの処理
		switch (sceneNo) {
		case SceneType::kTitle:
			titleScene->Update();
			if (titleScene->IsSceneEnd()) {
				//次のシーンの値を代入してシーン切り替え
				sceneNo = titleScene->NextScene();
			}
			break;
		case SceneType::kGamePlay:
			break;
		case SceneType::kResult:
			break;
		}
		//描画開始
		dxCommon->PreDraw();

		//ここに描画処理を記述する
		Sprite::PreDraw();
		switch (sceneNo) {
		case SceneType::kTitle:
			sprite->Draw();
			break;
		case SceneType::kGamePlay:
			break;
		case SceneType::kResult:
			break;
		}
		// スプライト描画後処理
		Sprite::PostDraw();
		// 描画終了
		Sprite::PostDraw();
		dxCommon->PostDraw();
	}

	// GameScene 解放
	delete gameScene;
	gameScene = nullptr;

	// エンジン終了
	KamataEngine::Finalize();

	return 0;
}
