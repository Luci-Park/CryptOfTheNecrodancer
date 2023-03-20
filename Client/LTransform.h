#pragma once
#include "LComponent.h"

namespace cl
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetPos(Vector2 pos) { mWorldPos = pos; CalculateLocalPos(); }
		void SetLocalPos(Vector2 pos) { mLocalPos = pos; CalculateWorldPos(); }
		void SetScale(Vector2 scale) { mWorldScale = scale; CalculateLocalScale(); }
		void SetLocalScale(Vector2 scale) { mLocalScale = scale; CalculateWorldScale(); }
		Vector2 GetPos() { return mWorldPos; }
		Vector2 GetScale() { return mWorldScale; }
		Vector2 GetLocalPos() { return mLocalPos; }
		Vector2 GetLocalScale() { return mLocalScale; }

		void SetParent(Transform* parent) { mParent = parent; }
		void SetChildren(Transform* child) { mChildren.push_back(child); }
	private:
		void CalculateWorldPos();
		void CalculateLocalPos();
		void CalculateWorldScale();
		void CalculateLocalScale();
	private:
		Transform* mParent;
		std::vector<Transform*> mChildren;
		Vector2 mLocalPos;
		Vector2 mLocalScale;
		Vector2 mWorldPos;
		Vector2 mWorldScale;
	};
}
