#pragma once

struct Timer
{
	Timer(function<void()> fuc, float time)
	{
		startTime = App::GetInstance()->time;
		this->time = time;
		this->fuc = fuc;
	}

	float startTime;
	float time;
	function<void()> fuc;
};

class Object : public enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object();

public:
	Object* parent;
	string name;
	int zOrder;

	Vec2 position;
	Vec2 scale;
	float rotation;

	bool isVisible;
	bool isRemoved;
	bool isNonCamera;
	bool donDestory;

	list<Timer> timers;

public:
	virtual void Update() 
	{
		for (auto it = timers.begin(); it != timers.end();)
		{
			if (App::GetInstance()->time - it->startTime >= it->time)
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

	virtual void Remove()
	{
		isRemoved = true;
	}

	Matrix4 GetTransform()
	{
		Matrix4 matrix;
		D3DXMatrixIdentity(&matrix);

		//if(isNonCamera)
		{
			D3DXMatrixTransformation2D(&matrix, nullptr, 0.f, &scale, nullptr, rotation, &position);
		}
		//else
		//{
		//	Matrix4 rot;
		//	D3DXMatrixRotationYawPitchRoll(&rot, 0, 0, D3DX_PI / 4);

		//	D3DXVECTOR2 pos;
		//	D3DXVec2TransformCoord(&pos, &position, &rot);

		//	D3DXMatrixTransformation2D(&matrix, nullptr, 0.f, &scale, nullptr, rotation, &pos);//&position);
		//}

		if (parent != nullptr)
		{
			matrix *= parent->GetTransform();
		}

		return matrix;
	}
};