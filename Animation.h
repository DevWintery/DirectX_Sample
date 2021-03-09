#pragma once

class Animation
{
private:
	vector<shared_ptr<Texture>> frames;

public:
	Animation(shared_ptr<Sprite> _target, float _rate, bool _loop):
		target(_target), count(0), curIndex(0), isDone(false), isStop(false), rate(_rate), loop(_loop), aniTime(0.f)
	{}
	virtual ~Animation()
	{}

public:
	shared_ptr<Sprite> target;
	int count;
	int curIndex;
	float aniTime;
	float rate;
	bool loop;

	bool isDone;
	bool isStop;

public:
	void AddFrame(const string& name)
	{
		auto tex = TextureManager::GetInstance()->LoadTexture(name);

		frames.push_back(tex);
		count ++;
	}

	void Update()
	{
		if (curIndex == count)
		{
			if(loop) { curIndex = 0; }
			else { isDone = true; return; }
		}

		aniTime += App::GetInstance()->deltaTime;
		if(aniTime >= rate && !isStop)
		{
			aniTime = 0.f;
			target->tex = frames[curIndex];
			curIndex ++;
		}
	}
};

class AnimationManager : public Singleton<AnimationManager>
{
private:
	list<shared_ptr<Animation>> animations;

public:
	AnimationManager()
	{}
	virtual ~AnimationManager()
	{}

public:
	shared_ptr<Animation> AddAnimation(Animation* ani)
	{
		auto tmp = shared_ptr<Animation>(ani);
		animations.push_back(tmp);

		return tmp;
	}

	void Update()
	{
		for(auto it = animations.begin(); it != animations.end();)
		{
			if((*it)->isDone)
			{
				it->reset();
				it = animations.erase(it);
			}
			else
			{
				it++;
			}
		}

		for(auto ani : animations)
		{
			ani->Update();
		}
	}

	void Release()
	{
		animations.clear();
	}
};

