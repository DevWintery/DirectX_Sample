#pragma once

class Camera : public Object
{
public:
	Camera();
	virtual ~Camera();

	Vec2 position;

	virtual void Update() override;
	virtual void Draw() override;

	void SetTransform();

	void Shake();

public:
	bool shaking;

public:
	Matrix4 orthographicMatrix;
	Matrix4 identityMatrix;
	Matrix4 viewMatrix;
};