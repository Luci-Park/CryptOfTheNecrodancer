#include "LBeatBar.h"
#include "LBeatUI.h"
#include "LSpriteRenderer.h"
#include "LConductor.h"
#include "LTime.h"
namespace cl
{
	BeatBar::BeatBar(Scene* sc)
		:GameObject(sc, true)
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetImage(L"HUD", L"..\\Assets\\Arts\\Effects\\HUD.bmp");
		mNormalBeat = Sprite(Vector2(200, 10), Vector2(6, 30), -Vector2(3, 15));
		mUrgentBeat = Sprite(Vector2(218, 10), Vector2(6, 30), -Vector2(3, 15));
		mSpriteRenderer->SetSprite(mNormalBeat);
	}
	BeatBar::~BeatBar()
	{
	}
	void BeatBar::SetBar(BeatUI* ui, Vector2 spawnPos, Vector2 despawnPos, Vector2 direction, int beat, int prevBeat)
	{
		mMaster = ui;
		mSpawnPos = spawnPos;
		mDespawnPos = despawnPos;
		mDirection = direction;
		mMyBeat = beat;
		mBeatsInAdvance = prevBeat;
		mTransform->SetPos(spawnPos);
	}
	void BeatBar::SetToUrgent()
	{
		mSpriteRenderer->SetSprite(mUrgentBeat);
	}
	void BeatBar::Update()
	{
		if (!Conductor::Instance().IsPlaying())return;
		if (IsOnBeat())
			mMaster->SetCurrentBar(this);
		if (CheckIfDespawn())
		{
			mMaster->UnsetCurrentBar(this);
			Destroy();
			return;
		}
		Move();
	}
	bool BeatBar::CheckIfDespawn()
	{
		if (mDirection == Vector2::Right
			&& mTransform->GetPos().x < mDespawnPos.x)
			return true;
		else if (mDirection == Vector2::Left
			&& mTransform->GetPos().x > mDespawnPos.x)
			return true;
		return false;
	}

	bool BeatBar::IsOnBeat()
	{
		float currBeat = Conductor::Instance().SongPositionBeats();
		if (mMyBeat - 0.25 <= currBeat
			&& currBeat <= mMyBeat + 0.5)
			return true;
		return false;
	}

	void BeatBar::Move()
	{
		float t = (mBeatsInAdvance - (mMyBeat + .25 - Conductor::Instance().SongPositionBeats())) / mBeatsInAdvance;
		Vector2 pos = Vector2::Lerp(mSpawnPos, mDespawnPos, t);
		mTransform->SetPos(pos);
	}
}