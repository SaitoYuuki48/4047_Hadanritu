#include "ResultScene.h"
void ResultScene::Initialize() {
	isResultSceneEnd = false;
}

void ResultScene::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		if (isResultSceneEnd == false) {
			isResultSceneEnd = true;
		}
	}
}