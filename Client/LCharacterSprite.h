#pragma once
#include "LGameObject.h"
#include "LGameManager.h"
namespace cl
{
	class GameManager;
	class CharacterSprite : public GameObject
	{
	public :
		CharacterSprite(Scene* sc);
		virtual ~CharacterSprite();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;
		virtual void Release() override;

		virtual void Turn(Vector2 dir) = 0;
		virtual void OnBeatChanged() = 0;

		void Jump();
		void SetManager(GameManager* m) { mGameManager = m; }
	protected:
		GameManager* mGameManager;

	};
}
