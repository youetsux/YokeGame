// ResultScene.h
#pragma once
#include "SceneBase.h"

class ResultScene : public SceneBase {
private:
	static int bgImage;
public:
	ResultScene();
	void Init() override;
	void Update( float deltaTime ) override;

	void Draw() override;

};
