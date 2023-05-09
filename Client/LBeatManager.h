#pragma once
#include "LGameObject.h"
namespace cl
{
	class BeatObject;
	class BeatManager
	{
	public:
		static void SetBPM(int bpm);
		static int BPM() { return _bpm; }
		static float MoveSpeed() { return _speedPerTile; }
		static float SecondsPerBeat() { return _spb; }
		static bool IsMovable() { return _movable; }

		static void Update();
		static void Reset();
		static void OnPlayerMove();
		static void AddCharacters(BeatObject* character);
		static void RemoveCharacters(BeatObject* character);
	private:
		static std::vector<BeatObject*> mCharacters;
		static float mGameTimer;
		
		static int _bpm;
		static float _speedPerTile;
		static float _spb;
		static bool _movable;
	};
}

