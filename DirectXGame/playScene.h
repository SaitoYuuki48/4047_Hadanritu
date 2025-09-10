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

	// 数字テクスチャ
	uint32_t digitTextures[10];

	// 記号スプライト
	uint32_t textTexture;
	uint32_t percentTexture;
	uint32_t toleranceTexture;

	Sprite* textSprite = nullptr;      // "Text.png"
	Sprite* percentSprite = nullptr;   // "%.png"
	Sprite* toleranceSprite = nullptr; // "+-.png"

	// 背景
	Sprite* textureBackground_ = nullptr;

	// フェード用黒背景
	Sprite* blackOverlay = nullptr;
	float overlayAlpha = 0.0f;

	// 演出用スプライト
	Sprite* clearSprite = nullptr;
	Sprite* gameoverSprite = nullptr;

	// 判定フラグ
	bool isClear = false;

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

	int displayedResult = 0; // カウントアップ用
	int finalResult = 0;     // 実際の破壊率

	enum class GameState { Playing, ResultFadeIn, ResultCounting, ResultWait, GameOver };
	GameState state;

	// 内部関数
	void SetupStage();
	void DrawNumber(int value, Vector2 pos, uint32_t textures[10], int spacing, Vector2 size);
};
