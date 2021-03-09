#pragma once

class Button : public Sprite
{
public:
	Button(const string& name, function<void()> fuc);

public:
	virtual void Update() override;

public:
	shared_ptr<Texture> normalTexture;
	shared_ptr<Texture> highlightTexture;
	shared_ptr<Texture> pushTexture;

	bool alreadyMouseClick;

	function<void ()> fuc;
};