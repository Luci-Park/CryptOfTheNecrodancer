#include "LKing.h"
namespace cl
{
	King::King(Scene* sc)
		:Monster(sc, false)
		, mbStartAttack(false)
	{
	}
	void King::Initialize()
	{
	}
	void King::StartAttack()
	{
	}
	Vector2 King::GetNextDir()
	{
		return Vector2();
	}
	void King::SetStats()
	{
	}
	void King::PlayOnAttackSound()
	{
	}
	void King::PlayOnHitSound()
	{
	}
	void King::PlayOnDeathSound()
	{
	}
	void King::OnBeat()
	{
	}
}