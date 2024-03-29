#include "LZombieSprite.h"
#include "LAnimator.h"
#include "LResources.h"
namespace cl
{
	ZombieSprite::ZombieSprite(Scene* sc)
		: CharacterSprite(sc)
		, isBeat(true)
	{
		mIdleAnim[GetIndex(Vector2::Right)] = L"RightIdle";
		mIdleAnim[GetIndex(Vector2::Left)] = L"LeftIdle";
		mIdleAnim[GetIndex(Vector2::Up)] = L"UpIdle";
		mIdleAnim[GetIndex(Vector2::Down)] = L"DownIdle";

		mBeatAnim[GetIndex(Vector2::Right)] = L"RightBeat";
		mBeatAnim[GetIndex(Vector2::Left)] = L"LeftBeat";
		mBeatAnim[GetIndex(Vector2::Up)] = L"UpBeat";
		mBeatAnim[GetIndex(Vector2::Down)] = L"DownBeat";

		for (int i = 0; i < 4; ++i)
		{
			mIdleShadowAnim[i] = mIdleAnim[i] + L"Shadow";
			mBeatShadowAnim[i] = mBeatAnim[i] + L"Shadow";
		}
	}
	ZombieSprite::~ZombieSprite()
	{
	}
	void ZombieSprite::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		CharacterSprite::Initialize();
		std::wstring path = L"..\\Assets\\Arts\\Monsters\\Zombie\\zombie.bmp";
		mAnimator->CreateAnimation(mBeatAnim[GetIndex(Vector2::Up)], L"zombie", path, 32, 2, 0, 0, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mIdleAnim[GetIndex(Vector2::Up)], L"zombie", path, 32, 2, 4, 0, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mBeatAnim[GetIndex(Vector2::Left)], L"zombie", path, 32, 2, 8, 0, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mIdleAnim[GetIndex(Vector2::Left)], L"zombie", path, 32, 2, 12, 0, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mBeatAnim[GetIndex(Vector2::Down)], L"zombie", path, 32, 2, 16, 0, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mIdleAnim[GetIndex(Vector2::Down)], L"zombie", path, 32, 2, 20, 0, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mIdleAnim[GetIndex(Vector2::Right)], L"zombie", path, 32, 2, 24, 0, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mBeatAnim[GetIndex(Vector2::Right)], L"zombie", path, 32, 2, 28, 0, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());

		mAnimator->CreateAnimation(mBeatShadowAnim[GetIndex(Vector2::Up)], L"zombie", path, 32, 2, 0, 1, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mIdleShadowAnim[GetIndex(Vector2::Up)], L"zombie", path, 32, 2, 4, 1, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mBeatShadowAnim[GetIndex(Vector2::Left)], L"zombie", path, 32, 2, 8, 1, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mIdleShadowAnim[GetIndex(Vector2::Left)], L"zombie", path, 32, 2, 12, 1, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mBeatShadowAnim[GetIndex(Vector2::Down)], L"zombie", path, 32, 2, 16, 1, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mIdleShadowAnim[GetIndex(Vector2::Down)], L"zombie", path, 32, 2, 20, 1, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mIdleShadowAnim[GetIndex(Vector2::Right)], L"zombie", path, 32, 2, 24, 1, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
		mAnimator->CreateAnimation(mBeatShadowAnim[GetIndex(Vector2::Right)], L"zombie", path, 32, 2, 28, 1, 4, -Vector2(12, 25), Conductor::Instance().SecondsPerBeat());
	}
	void ZombieSprite::Turn(Vector2 dir)
	{
		if (Vector2::IsCardinal(dir))
		{
			mLookDir = dir;
			if (isBeat)
				OnBeat();
			else
				Idle();
		}
	}

	void ZombieSprite::Idle()
	{
		isBeat = false;
		int idx = GetIndex(mLookDir);
		bool rev = mLookDir == Vector2::Right;
		if (!mbInShadows)
			mAnimator->Play(mIdleAnim[idx], Animator::PlaySetting::Loop, rev);
		else
			mAnimator->Play(mIdleShadowAnim[idx], Animator::PlaySetting::Loop, rev);
	}

	void ZombieSprite::OnBeat()
	{
		isBeat = true;
		int idx = GetIndex(mLookDir);
		bool rev = mLookDir == Vector2::Right;
		if (!mbInShadows)
			mAnimator->Play(mBeatAnim[idx], Animator::PlaySetting::Loop, rev);
		else
			mAnimator->Play(mBeatShadowAnim[idx], Animator::PlaySetting::Loop, rev);
	}

	int ZombieSprite::GetIndex(Vector2 dir)
	{
		if (dir == Vector2::Left) return 0;
		if (dir == Vector2::Right) return 1;
		if (dir == Vector2::Up) return 2;
		if (dir == Vector2::Down) return 3;
		return -1;
	}
	
}
