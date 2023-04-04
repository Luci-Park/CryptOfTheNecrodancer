#pragma once
#include "LTileObject.h"
#include "LBeatObject.h"
namespace cl
{
	class BeatManager;
	class CharacterSprite;
	class GameCharacter : public TileObject, public BeatObject
	{
	public:
		GameCharacter(Scene* sc, bool isFlying);
		virtual ~GameCharacter();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void TryDig() = 0;
		virtual void TryAttack() = 0;
		virtual void Sink() override;
		virtual void OnDestroy() = 0;

		virtual void OnBeat() = 0;
		virtual void OnBeatChanged();
		virtual void OnAttacked() = 0;
	protected:
		CharacterSprite* mSprite;
		Vector2 mMoveTarget;
		bool mbIsMoving;
		bool mbIsFlying;
		bool mbIsSinked;
	private:
	};
}

