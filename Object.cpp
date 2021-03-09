#include"DXUT.h"
#include"Precompile.h"
#include"Object.h"

Object::Object():
	isRemoved(false), name(""), zOrder(0), position(0.f, 0.f), scale(1.f, 1.f), rotation(0.f), isNonCamera(false), parent(nullptr), isVisible(true), donDestory(false)
{
}

Object::~Object()
{
}
