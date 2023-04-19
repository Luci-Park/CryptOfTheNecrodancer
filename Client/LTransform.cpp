#include "LTransform.h"
#include "LGameObject.h"
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
	void Transform::SetParent(Transform* parent)
	{
		if (mParent != nullptr && mParent != this && mParent != parent)
		{
			mParent->RemoveChildren(this);
		}
		mParent = parent;
		parent->SetChildren(this);
		CalculateWorldPos();
		CalculateWorldScale();
	}
	void Transform::SetChildren(Transform* child)
	{
		if(child != nullptr && child != this)
			mChildren.push_back(child);
	}
	void Transform::RemoveChildren(Transform* child)
	{
		auto it = std::find(mChildren.begin(), mChildren.end(), child);
		if (it != mChildren.end())
		{
			mChildren.erase(it);
		}
	}
	void Transform::CalculateWorldPos()
	{
		if (mParent != this && mParent != nullptr)
			mWorldPos = mLocalPos + mParent->GetPos();
		else
			mWorldPos = mLocalPos;
	}
	void Transform::CalculateLocalPos()
	{
		if (mParent != this && mParent != nullptr)
			mLocalPos = mWorldPos - mParent->GetPos();
		else
			mLocalPos = mWorldPos;
	}
	void Transform::CalculateWorldScale()
	{
		if (mParent != this && mParent != nullptr)
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
		if (mParent != this && mParent != nullptr)
		{
			Vector2 parentScale = mParent->GetScale();
			mLocalScale.x = parentScale.y == 0? 0: mWorldScale.x / parentScale.x;
			mLocalScale.y = parentScale.y == 0 ? 0 : mWorldScale.y / parentScale.y;
		}
		else
			mLocalScale = mWorldScale;
	}
}