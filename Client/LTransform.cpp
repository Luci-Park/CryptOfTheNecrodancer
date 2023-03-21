#include "LTransform.h"


namespace cl
{
	Transform::Transform()
		:Component(eComponentType::Transform)
		, mLocalPos(Vector2::Zero)
		, mWorldPos(Vector2::Zero)
		, mLocalScale(Vector2::One)
		, mWorldScale(Vector2::One)
		, mParent(this)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
		CalculateWorldPos();
		CalculateWorldScale();
	}
	void Transform::Render(HDC hdc)
	{
	}
	void Transform::CalculateWorldPos()
	{
		if (mParent != this)
			mWorldPos = mLocalPos + mParent->GetPos();
		else
			mWorldPos = mLocalPos;
	}
	void Transform::CalculateLocalPos()
	{
		if (mParent != this)
			mLocalPos = mWorldPos - mParent->GetPos();
		else
			mLocalPos = mWorldPos;
	}
	void Transform::CalculateWorldScale()
	{
		if (mParent != this)
		{
			Vector2 parentScale = mParent->GetScale();
			mWorldScale.x = mLocalScale.x * parentScale.x;
			mWorldScale.y = mLocalScale.y * parentScale.y;
		}
		else
			mWorldScale = mLocalScale;
	}
	void Transform::CalculateLocalScale()
	{
		if (mParent != this)
		{
			Vector2 parentScale = mParent->GetScale();
			mLocalScale.x = parentScale.y == 0? 0: mWorldScale.x / parentScale.x;
			mLocalScale.y = parentScale.y == 0 ? 0 : mWorldScale.y / parentScale.y;
		}
		else
			mLocalScale = mWorldScale;
	}
}