#pragma once

class Animation
{
public:
	Animation();
	Animation(shared_ptr<Sprite> target, float rate, bool loop);
	virtual ~Animation();

	shared_ptr<Sprite> targetSprite;

	vector<shared_ptr<Texture>> frames;

	int curIndex;
	int count;

	float aniTime;
	float freamRate;

	bool isLoop;
	bool isDone;
	bool isStop;

public:
	void Update();
	void AddFrame(const string& frame);
	void Stop();
};

class AnimationManager : public Singleton<AnimationManager>
{
public:
	AnimationManager();
	virtual ~AnimationManager();

private:
	vector<shared_ptr<Animation>> animations;

public:
	shared_ptr<Animation> AddAnimation(Animation* animation);
	void Update();

	void Release();
};