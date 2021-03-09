#pragma once

class ProgressBar : public Sprite
{
public:
	ProgressBar(const string& name);
	virtual ~ProgressBar();

public:
	virtual void Draw() override;
	virtual void Update() override;

	float value;
	float curValue;
	RECT rect;

public:
	void SetValue(float value);
};