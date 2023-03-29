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
		GameCharacter(Scene* sc);
		virtual ~GameCharacter();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Move() = 0;
		virtual void OnBeatChanged();
	protected:
		CharacterSprite* mSprite;
		Vector2 mMoveTarget;
	};
}

