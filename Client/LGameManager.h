#pragma once
#include "LGameObject.h"
#define UNIT 26;
namespace cl
{
	class GameCharacter;
	class GameManager : public GameObject
	{
	public:
		GameManager(Scene* sc);
		virtual ~GameManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		void AddCharacters(GameCharacter* character);
	private:
		void CheckBeat();
		void CountBeat();
		void CheckIfMoveable();
	private:
		std::vector<GameCharacter*> mCharacters;
		float mTimer;
		float mPlayerTimer;
		int mBPM;


	public:
		static void SetBPM(int bpm);
		static int BPM() { return _bpm; }
		static float UnitLength() { return _unitLength; }
		static float UnitScale() { return _unitScale; }
		static float MoveSpeed() { return _speedPerTile; }
		static float BeatDuration() { return _beatDuration; }
		static bool IsMovable() { return _movable; }
	private:
		static int _bpm;
		static float _unitScale;
		static float _unitLength;
		static float _speedPerTile;
		static float _beatDuration;
		static bool _movable;
	};
}

