#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class PlayScene {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	// 円スプライト
	Sprite* bigCircle = nullptr;
	Sprite* smallCircle = nullptr;

	// 数字スプライト（0～9）
	Sprite* digitSprites[10] = {nullptr};

	// 記号スプライト
	Sprite* textSprite = nullptr;    // "Text.png"（目標用）
	Sprite* percentSprite = nullptr; // "%.png"   （結果用）
	Sprite* toleranceSprite = nullptr; // +-.png （許容誤差表示用）

	// 白背景
	Sprite* textureBackground_ = nullptr;

	// ゲームデータ
	float R; // 大きい円の半径
	float r; // 小さい円の半径
	float minR;
	float maxR;
	float speed;
	int direction;

	float target;    // 目標破壊率
	float tolerance; // 許容誤差
	int level;       // レベル
	bool finished;   // 判定済みフラグ

	// 内部関数
	void SetupStage();                       // ステージ初期化
	void DrawNumber(int value, Vector2 pos); // 数字をスプライトで描画
};
