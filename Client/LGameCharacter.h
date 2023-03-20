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
		void SetManager(GameManager* m);
		void OnBeatChanged();
	protected:
		CharacterSprite* mSprite;
		GameManager* mGameManager;
		Vector2 mMoveTarget;
	};
}

