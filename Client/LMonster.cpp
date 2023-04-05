#include "LMonster.h"
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
	void Monster::OnBeatChanged()
	{
		GameCharacter::OnBeatChanged();
	}
}