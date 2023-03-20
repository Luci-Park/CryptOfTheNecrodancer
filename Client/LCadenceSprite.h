#pragma once
#include "LCharacterSprite.h"
#include "LInput.h"
namespace cl
{
	class CadenceHead;
	class CadenceBody;
	class CadenceSprite : public CharacterSprite
	{
	public:
		CadenceSprite(Scene* sc);
		~CadenceSprite();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void Turn(Vector2 dir) override;
		
		virtual void OnBeatChanged() override;
	private:
		CadenceHead* mHead;
		CadenceBody* mBody;		
	};
}

