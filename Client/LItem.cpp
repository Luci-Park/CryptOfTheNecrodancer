#include "LItem.h"
#include "LCadence.h"
#include "LAudioClip.h"
namespace cl
{
	Item::Item(Scene* sc, eItemTypes type)
		: GameObject(sc, false)
		, mType(type)
		, mbIsSetDown(false)
		, mSpriteRenderer(nullptr)
	{
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{
		mSpriteRenderer->SetActive(mbIsSetDown);
		GameObject::Initialize();
	}

	void Item::Update()
	{
		GameObject::Update();
	}

	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Item::PickUpItem(Cadence* player)
	{
		mbIsSetDown = false;
		mSpriteRenderer->SetActive(false);
		mTransform->SetParent(player->mTransform);
		mTransform->SetLocalPos(Vector2::Zero);
		mTransform->SetLocalScale(Vector2::One);
		player->SwitchItem(this, mType);
		mGetItemClip->Play(false);
	}

	void Item::SetItem(Vector2 pos)
	{
		mbIsSetDown = true;
		mSpriteRenderer->SetActive(true);
		mTransform->SetParent(mTransform);
		mTransform->SetPos(pos);
		mTransform->SetLocalScale(Vector2::One * UNITSCALE);
	}

}