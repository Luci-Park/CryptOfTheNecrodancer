#include "LGameManager.h"
#include "LGameCharacter.h"
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
		, mTimer(0.0f)
		, mPlayerTimer(0.0f)
		, mBPM(1)
	{
	}

	GameManager::~GameManager()
	{
	}

	void GameManager::Initialize()
	{
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

	void GameManager::AddCharacters(GameCharacter* character)
	{
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
		mTimer += Time::DeltaTime();
		if (_beatDuration <= mTimer)
		{
			mTimer -= mTimer;
			for (int i = 0; i < mCharacters.size(); ++i)
			{
				mCharacters[i]->OnBeat();
			}
		}
	}

	void GameManager::CheckIfMoveable()
	{
		if (_beatDuration * 0.5 <= mPlayerTimer &&
			mPlayerTimer < _beatDuration * 1.5)
		{
			_movable = true;
			mPlayerTimer = mTimer;
		}
		else
		{
			_movable = false;
		}
	}


	void GameManager::SetBPM(int bpm)
	{
		_bpm = bpm;
		float bps = bpm / 60.0f;
		_beatDuration = 1 / bps;
		_speedPerTile = _unitLength / _beatDuration;
	}

}