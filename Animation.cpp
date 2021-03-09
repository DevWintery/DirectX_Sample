#include"DXUT.h"
#include"Precompile.h"
#include"Animation.h"
#include"GameManager.h"

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

shared_ptr<Animation> AnimationManager::AddAnimation(Animation * animation)
{
	auto tmp = shared_ptr<Animation>(animation);
	animations.push_back(tmp);

	return tmp;
}

void AnimationManager::Update()
{
	for (auto it = animations.begin(); it != animations.end();)
	{
		if ((*it)->isDone)
		{
			(*it)->targetSprite.reset();
			(*it).reset();
			it = animations.erase(it);
		}
		else
		{
			it++;
		}
	}

	for (size_t i = 0; i < animations.size(); i++)
	{
		animations[i]->Update();
	}
}

void AnimationManager::Release()
{
	animations.clear();
}

Animation::Animation()
{
}

Animation::Animation(shared_ptr<Sprite> target, float rate, bool loop) :
	freamRate(rate), isLoop(loop), aniTime(0), curIndex(0), count(0), targetSprite(target), isDone(false), isStop(false)
{
	auto tmp = shared_ptr<Sprite>(target);
	
	targetSprite = tmp;
}

Animation::~Animation()
{
	targetSprite = nullptr;
	frames.clear();
}

void Animation::Update()
{
	if (targetSprite == nullptr) { isDone = true; }
	if(isStop) { return; }
	if(targetSprite->name == "Enemy" && GameManager::GetInstance()->timeStop) { return; }

	if (curIndex == count)
	{
		if (isLoop) { curIndex = 0; }
		else { isDone = true; }
		return;
	}

	aniTime += App::GetInstance()->deltaTime;
	if (aniTime >= freamRate)
	{
		targetSprite->texture = frames[curIndex];
		aniTime = 0.f;
		curIndex++;
	}
}

void Animation::AddFrame(const string& frame)
{
	auto tmp = TextureManager::GetInstance()->LoadTexture(frame);
	count++;
	frames.push_back(tmp);
}

void Animation::Stop()
{
	isStop = true;
}
