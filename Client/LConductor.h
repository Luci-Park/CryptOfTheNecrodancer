#pragma once
namespace cl
{
	class AudioClip;
	class BeatObject;
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

		float MoveSpeed() { return mSpeedPerTile; }
		float SecondsPerBeat() { return mSecPerBeat; }
		float SongPosition() { return mSongPosition; }
		float SongPositionBeats() { return mSongPositionBeats; }
		bool IsPlaying() { return mIsPlaying; }

		void OnPlayerMove();
		void AddCharacters(BeatObject* character);
		void RemoveCharacters(BeatObject* character);

	private:
		Conductor() {}
		Conductor(const Conductor&) = delete; //disable operator
		Conductor* operator =(const Conductor&) = delete; // disable operator
		void Reset();

		std::vector<BeatObject*> mCharacters;
		int mBpm;
		float mSecPerBeat;
		float mSpeedPerTile;
		float mSongPosition; //in seconds
		float mSongPositionBeats; //in beats
		float mElapsedTime;
		bool mIsPlaying;
		AudioClip* mClip;
	};
}

