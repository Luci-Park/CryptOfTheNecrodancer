#include "LComponent.h"

namespace cl
{
	Component::Component(eComponentType type)
		: mType(type)
	{
	}
	Component::~Component()
	{
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
	void Component::Release()
	{
	}
}
