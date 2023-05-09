#pragma once
namespace cl
{
	class AudioClip;
	class Conductor
	{
	public:
		static Conductor& Instance()
		{
			static Conductor instance;
			return instance;
		}
		void SetSong(AudioClip* clip, int bpm);

		void Play(bool loop = true);
		void Stop();
		void Update();

		float SongPosition() { return mSongPosition; }
		float SongPositionBeats() { return mSongPositionBeats; }
		bool IsPlaying() { return mIsPlaying; }

	private:
		Conductor() {}
		Conductor(const Conductor&) = delete; //disable operator
		Conductor* operator =(const Conductor&) = delete; // disable operator

		int mBpm;
		float mSecPerBeat;
		float mSongPosition; //in seconds
		float mSongPositionBeats; //in beats
		float mElapsedTime;
		bool mIsPlaying;
		AudioClip* mClip;
	};
}

