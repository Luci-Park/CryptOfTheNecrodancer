#pragma once
#include "LGameObject.h"
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

		void SetBPM(int bpm);
		int BPM() { return mBPM; }
		float Displacement() { return mDistPerTile; }
		float MoveSpeed() { return mSpeedPerTile; }
		float BeatDuration() { return mBeatDuration; }
	private:
		int mBPM;
		float mDistPerTile;
		float mSpeedPerTile;
		float mBeatDuration;
	};
}

