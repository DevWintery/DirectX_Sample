#pragma once

struct Timer
{
	Timer(function<void()> _fuc, float _rate)
	{
		fuc = _fuc;
		rate = _rate;
		time = App::GetInstance()->time;
	}

	float rate;
	double time;
	function<void()> fuc;
};

class Object : public enable_shared_from_this<Object>
{
public:
	Object():
		position(0.f, 0.f), scale(1.f, 1.f), rotation(0.f), zOrder(0), isRemoved(false), isVisible(true), isNonCamera(false), parent(nullptr)
	{}
	virtual ~Object(){}

public:
	Object* parent;

	string name;

	Vec2 scale;
	Vec2 position;
	float rotation;

	int zOrder;

	bool isRemoved;
	bool isVisible;

	bool isNonCamera;

	list<Timer> timers;

public:
	virtual void Update()
	{
		for(auto it = timers.begin(); it != timers.end();)
		{
			if(App::GetInstance()->time - it->time >= it->rate)
			{
				it->fuc();
				it = timers.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	virtual void Draw() {}

	Matrix4 GetTransform()
	{
		Matrix4 matrix;

		D3DXMatrixTransformation2D(&matrix, nullptr, 0, &scale, nullptr, rotation, &position);

		if(parent != nullptr)
		{
			matrix *= parent->GetTransform();
		}

		return matrix;
	}
};

