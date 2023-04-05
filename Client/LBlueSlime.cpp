#include "LBlueSlime.h"
#include "LBlueSlimeSprite.h"
#include "LObject.h"
#include "LMapManager.h"
#include "LBeatManager.h"
namespace cl
{
	BlueSlime::BlueSlime(Scene* sc)
		: GameCharacter(sc, true)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
		nextPos.resize(4);
		nextPos[0] = Vector2::Up;
		nextPos[1] = Vector2::Zero;
		nextPos[2] = Vector2::Down;
		nextPos[3] = Vector2::Zero;
		mMovementIndex = 0;
	}
	BlueSlime::~BlueSlime()
	{
	}
	void BlueSlime::Initialize()
	{
		GameCharacter::Initialize();
		mSlimeSprite = object::Instantiate<BlueSlimeSprite>(GameObject::GetScene(), mTransform, mTransform->GetPos(), eLayerType::Monster);
		mSprite = mSlimeSprite;
		BeatManager::AddCharacters(this);
	}
	void BlueSlime::Update()
	{
		GameCharacter::Update();
	}
	void BlueSlime::Render(HDC hdc)
	{
		GameCharacter::Render(hdc);
	}
	void BlueSlime::Sink()
	{
		GameCharacter::Sink();
	}
	void BlueSlime::OnAttacked(float attackPower)
	{
	}
	void BlueSlime::OnDestroy()
	{
	}
	void BlueSlime::OnBeat()
	{
		mSprite->Reset();
		if (!UnSink())
		{
			Vector2 nextPos = GetNextPos();
			mMoveTarget += nextPos * UNITLENGTH;
			if (nextPos == Vector2::Zero)
				mSlimeSprite->Idle();
			else
			{
				mSlimeSprite->Jump();
				MapManager::Move(mIndex, mIndex + nextPos);
			}
			mIndex += nextPos;
		}
	}
	bool BlueSlime::TryAttack(Vector2 Direction)
	{
		return false;
	}
	bool BlueSlime::TryDig(Vector2 direction)
	{
		return false;
	}
	bool BlueSlime::TryMove(Vector2 direction)
	{
		return false;
	}
	Vector2 BlueSlime::GetNextPos()
	{
		Vector2 movement = nextPos[mMovementIndex];
		mMovementIndex = (mMovementIndex + 1) % nextPos.size();
		return movement;
	}
}
