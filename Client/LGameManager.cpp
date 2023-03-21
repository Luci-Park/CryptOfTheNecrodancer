#include "LGameManager.h"
#include "LBeatObject.h"
#include "LTime.h"

namespace cl
{
	int GameManager::_bpm(1);
	float GameManager::_unitScale(2.0f);
	float GameManager::_unitLength(52.0f);
	float GameManager::_speedPerTile(0.0f);
	float GameManager::_beatDuration(0.0f);

	GameManager::GameManager(Scene* sc)
		: GameObject(sc, false)
		, mGameTimer(0.0f)
		, mBPM(1)
		, mNextBeat(0)
	{
	}

	GameManager::~GameManager()
	{
	}

	void GameManager::Initialize()
	{
		mBPM = _bpm;
		mNextBeat = _beatDuration;
	}

	void GameManager::Update()
	{
		CheckBeat();
		CountBeat();
		CheckIfMoveable();
	}

	void GameManager::Render(HDC hdc)
	{
	}

	void GameManager::AddCharacters(BeatObject* character)
	{
		mCharacters.push_back(character);
	}

	void GameManager::CheckBeat()
	{
		if (mBPM != _bpm)
		{
			mBPM = _bpm;
			for (int i = 0; i < mCharacters.size(); ++i)
			{
				mCharacters[i]->OnBeatChanged();
			}
		}
	}

	void GameManager::CountBeat()
	{
		mGameTimer += Time::DeltaTime();
		if (mNextBeat <= mGameTimer)
		{
			mGameTimer -= mGameTimer;
			for (int i = 0; i < mCharacters.size(); ++i)
			{
				mCharacters[i]->OnBeat();
			}
			//mNextBeat += _beatDuration;
		}
	}

	void GameManager::CheckIfMoveable()
	{
	}


	void GameManager::SetBPM(int bpm)
	{
		_bpm = bpm;
		float bps = bpm / 60.0f;
		_beatDuration = 1 / bps;
		_speedPerTile = _unitLength / _beatDuration;
	}

}