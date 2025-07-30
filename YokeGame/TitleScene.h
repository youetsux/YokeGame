// TitleScene.h
#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase {
private:
	static int bgImage;
public:
	TitleScene();
	void Init() override;
	void Update(float deltaTime) override;
	void Draw() override;

};
