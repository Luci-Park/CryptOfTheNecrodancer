#include "LItem.h"
#include "LCadence.h"
#include "LAudioClip.h"
namespace cl
{
	Item::Item(Scene* sc, eItemTypes type)
		: GameObject(sc, false)
		, mType(type)
		, mbIsSetDown(false)
	{
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{
		GameObject::Initialize();
		SetSprite();
	}

	void Item::Update()
	{
		if(mSpriteRenderer != nullptr)
			mSpriteRenderer->SetActive(mbIsSetDown);
		GameObject::Update();
	}

	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Item::PickUpItem(Cadence* player)
	{
		mbIsSetDown = false;
		mSpriteRenderer->SetActive(mbIsSetDown);
		mTransform->SetParent(player->mTransform);
		mTransform->SetLocalPos(Vector2::Zero);
		player->SwitchItem(this, mType);
		mGetItemClip->Play(false);
	}

	void Item::SetItem(Vector2 pos)
	{
		mbIsSetDown = true;
		mSpriteRenderer->SetActive(mbIsSetDown);
		mTransform->SetParent(mTransform);
		mTransform->SetPos(pos);
	}

}