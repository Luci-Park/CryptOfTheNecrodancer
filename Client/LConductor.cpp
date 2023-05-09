#include "LConductor.h"
#include "LTime.h"
#include "LAudioClip.h"
namespace cl
{
	void Conductor::SetSong(AudioClip* clip, int bpm)
	{
		mClip = clip;
		mBpm = bpm;
		mSecPerBeat = 60.0f / bpm;
		mSongPosition = 0;
		mSongPositionBeats = 0;
		mElapsedTime = 0;
		mIsPlaying = false;
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
}
