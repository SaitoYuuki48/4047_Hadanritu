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

	// 数字スプライト
	Sprite* digitSprites[10] = {nullptr};    // 目標用
	Sprite* toleranceDigits[10] = {nullptr}; // 誤差用
	Sprite* resultDigits[10] = {nullptr};    // 結果用

	// 記号スプライト
	Sprite* textSprite = nullptr;      // "Text.png"（目標用）
	Sprite* percentSprite = nullptr;   // "%.png"   （共通で使う）
	Sprite* toleranceSprite = nullptr; // "+-.png" （誤差表示用）

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
	void SetupStage();
	void DrawNumber(int value, Vector2 pos, Sprite* sprites[10], int spacing);
};
