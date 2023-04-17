#pragma once
#include "LCharacterSprite.h"
namespace cl
{
	class ZombieSprite : public CharacterSprite
	{
	public:
		ZombieSprite(Scene* sc);
		virtual ~ZombieSprite();

		virtual void Initialize() override;
		virtual void Turn(Vector2 dir) override;

		void Idle();
		void OnBeat();
	private:
		int GetIndex(Vector2 dir);
	protected:
		Vector2 mLookDir;
		std::wstring mIdleAnim[4];
		std::wstring mBeatAnim[4];
		std::wstring mIdleShadowAnim[4];
		std::wstring mBeatShadowAnim[4];
		bool isBeat;
	};
}

