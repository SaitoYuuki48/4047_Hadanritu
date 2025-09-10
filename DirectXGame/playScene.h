#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

enum class GameState { Playing, ResultFadeIn, ResultCounting, GameOver };

class PlayScene {
public:
	void Initialize();
	void SetupStage();
	void Update();
	void Draw();
	void DrawNumber(int value, Vector2 pos, uint32_t textures[10], int spacing, Vector2 size);

	// GameScene から終了検知する用
	bool IsFinished() const { return finished; }

private:
	// スプライト類
	Sprite* textureBackground_ = nullptr;
	Sprite* textSprite = nullptr;
	Sprite* percentSprite = nullptr;
	Sprite* toleranceSprite = nullptr;
	Sprite* bigCircle = nullptr;
	Sprite* smallCircle = nullptr;
	Sprite* blackOverlay = nullptr;
	Sprite* clearSprite = nullptr;
	Sprite* gameoverSprite = nullptr;

	// テクスチャ
	uint32_t digitTextures[10];
	uint32_t textTexture;
	uint32_t percentTexture;
	uint32_t toleranceTexture;

	// ゲーム進行
	GameState state;
	bool finished = false;
	bool isClear = false;
	int level = 1;

	// 円関連
	float R; // 大きい円の半径
	float r; // 小さい円の半径
	float minR;
	float maxR;
	float speed;
	int direction;

	// 破壊率関連
	float target;
	float tolerance;
	int finalResult;
	int displayedResult;

	// 演出用
	float overlayAlpha;
};
