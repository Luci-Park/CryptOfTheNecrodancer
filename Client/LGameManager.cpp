#include "LGameManager.h"

namespace cl
{
	GameManager::GameManager(Scene* sc)
		: GameObject(sc, false)
		, mBPM(1), mDistPerTile(50.0f), mSpeedPerTile(0.0f), mBeatDuration(0.0f)
	{
	}

	GameManager::~GameManager()
	{
	}

	void GameManager::Initialize()
	{
		SetBPM(150);
	}

	void GameManager::Update()
	{
	}

	void GameManager::Render(HDC hdc)
	{
	}

	void GameManager::SetBPM(int bpm)
	{
		mBPM = bpm;
		float bps = bpm / 60.0f;
		mBeatDuration = 1 / bps;
		mSpeedPerTile = mDistPerTile / mBeatDuration * 2;
	}
}