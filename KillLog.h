#pragma once

class KillLog : public Object
{
public:
	KillLog();
	virtual ~KillLog();

public:
	vector<shared_ptr<Sprite>> killLogs;

public:
	virtual void Update()
	{
		Object::Update();


	}
};

