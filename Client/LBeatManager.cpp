#include "LBeatManager.h"
#include "LBeatObject.h"
#include "LTime.h"
#include "LMapManager.h"

namespace cl
{
	std::vector<BeatObject*> BeatManager::mCharacters = std::vector<BeatObject*>();
	float BeatManager::mGameTimer = 0.0f;
	int BeatManager::_bpm = 1;
	float BeatManager::_speedPerTile = 0.0f;
	float BeatManager::_beatDuration = 0.0f;

	void BeatManager::SetBPM(int bpm)
	{
		_bpm = bpm;
		float bps = bpm / 60.0f;
		_beatDuration = 1 / bps;
		_speedPerTile = UNITLENGTH / _beatDuration;
		for (int i = 0; i < mCharacters.size(); ++i)
			mCharacters[i]->OnBeatChanged();
	}
	void BeatManager::Update()
	{/*
		mGameTimer += Time::DeltaTime();
		if (mGameTimer >= _beatDuration)
		{
			mGameTimer -= mGameTimer;
			for (int i = 0; i < mCharacters.size(); ++i)
				mCharacters[i]->OnBeat();
		}*/
	}

	void BeatManager::Reset()
	{
		mCharacters = std::vector<BeatObject*>();
		mGameTimer = 0.0f;
	}

	void BeatManager::OnPlayerMove()
	{
		for (int i = 0; i < mCharacters.size(); ++i)
			if(mCharacters[i] != nullptr)
				mCharacters[i]->OnBeat();
	}


	void BeatManager::AddCharacters(BeatObject* character)
	{
		mCharacters.push_back(character);
	}
	void BeatManager::RemoveCharacters(BeatObject* character)
	{
		auto it = std::find(mCharacters.begin(), mCharacters.end(), character);
		if (it != mCharacters.end())
			mCharacters.erase(it);
	}
}