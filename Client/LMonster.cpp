#include "LMonster.h"
#include "LCharacterSprite.h"
namespace cl
{
	Monster::Monster(Scene* sc, bool isTouchingGround)
		: GameCharacter(sc, isTouchingGround)
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		GameCharacter::Initialize();
		SetStats();
	}
	void Monster::Update()
	{
		GameCharacter::Update();
	}
	void Monster::Render(HDC hdc)
	{
		GameCharacter::Render(hdc);
	}
	void Monster::Sink()
	{
		GameCharacter::Sink();
	}
	void Monster::OnBeat()
	{
		mSprite->Reset();
		if (!UnSink())
		{
			Vector2 nextDir = GetNextDir();
			if (!TryAttack(nextDir) && !TryDig(nextDir))
			{
				TryMove(nextDir);
			}
		}
	}
	void Monster::OnBeatChanged()
	{
		GameCharacter::OnBeatChanged();
	}
}