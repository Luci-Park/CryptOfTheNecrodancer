#pragma once
#include "LGameObject.h"
#include "LGameManager.h"
namespace cl
{
	class GameManager;
	class CharacterSprite;
	class GameCharacter : public GameObject
	{
	public:
		GameCharacter(Scene* sc);
		virtual ~GameCharacter();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Move() = 0;
		virtual void OnBeatChanged();
		virtual void OnBeat() = 0;
	protected:
		CharacterSprite* mSprite;
		Vector2 mMoveTarget;
	};
}

