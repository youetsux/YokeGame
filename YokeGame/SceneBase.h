// SceneBase.h
#pragma once

class SceneBase {
protected:
    bool isFinished = false;
public:
	virtual ~SceneBase() {}
	virtual void Init() {}
	virtual void Update( float deltaTime ) = 0;
	virtual void Draw() = 0;
	virtual bool IsFinished() const
	{
		return isFinished;
	}
};
