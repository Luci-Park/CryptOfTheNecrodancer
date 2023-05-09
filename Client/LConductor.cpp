#include "LConductor.h"
#include "LTime.h"
#include "LAudioClip.h"
#include "LBeatObject.h"
namespace cl
{
	void Conductor::SetSong(AudioClip* clip, int bpm)
	{
		mClip = clip;
		mBpm = bpm;
		mSecPerBeat = 60.0f / bpm;
		mSpeedPerTile = UNITLENGTH / mSecPerBeat;
		Reset();
	}

	void Conductor::Play(bool loop)
	{
		mClip->Play(loop);
		mIsPlaying = true;
	}

	void Conductor::Stop()
	{
		mClip->Stop(true);
		mIsPlaying = false;
	}

	void Conductor::Update()
	{
		if (!mIsPlaying) return;
		mElapsedTime += Time::DeltaTime();
		mSongPosition += Time::DeltaTime();
		mSongPositionBeats = mSongPosition / mSecPerBeat;

	}
	void Conductor::OnPlayerMove()
	{
		for (int i = 0; i < mCharacters.size(); ++i)
		{
			if (mCharacters[i] != nullptr)
				mCharacters[i]->OnBeat();
		}
		for (int i = 0; i < mCharacters.size(); ++i)
		{
			if (mCharacters[i] != nullptr)
				mCharacters[i]->OnLateBeat();
		}
	}
	void Conductor::AddCharacters(BeatObject* character)
	{
		if (character != nullptr)
			mCharacters.push_back(character);
	}
	void Conductor::RemoveCharacters(BeatObject* character)
	{
		auto it = std::find(mCharacters.begin(), mCharacters.end(), character);
		if (it != mCharacters.end())
			mCharacters.erase(it);
	}
	void Conductor::Reset()
	{
		mSongPosition = 0;
		mSongPositionBeats = 0;
		mElapsedTime = 0;
		mIsPlaying = false;
		mCharacters = std::vector<BeatObject*>();
	}
}
