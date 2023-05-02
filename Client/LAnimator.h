#pragma once
#include "LComponent.h"
#include "LAnimation.h"
#include "LImage.h"

namespace cl
{
	class Animator : public Component
	{
	public:
		enum class PlaySetting{Once, PauseAtEnd, Loop};
		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& animationName, Image* sheet,
			UINT coulmn, UINT row, 
			UINT sCol, UINT sRow, 
			UINT spriteLength, Vector2 offset, float duration);
		void CreateAnimation(const std::wstring& animationName,
			const std::wstring& sheetName, const std::wstring& sheetPath
			, UINT coulmn, UINT row
			, UINT sCol, UINT sRow, UINT spriteLength
			, Vector2 offset, float duration);
		void CreateAnimation(const std::wstring& animationName
			, const std::wstring& sheetName, const std::wstring& sheetPath
			, Vector2 leftTop, Vector2 size, UINT spriteLength, float duration);
		void CreateAnimations(const std::wstring& path, const std::wstring& key, Vector2 offset, float duration);


		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, PlaySetting loop, bool reverse);
		void PlayNoDuplication(const std::wstring& name, bool loop, bool reverse);
		void Stop();
		bool IsComplete();
		bool IsAnimationPlaying(const std::wstring& name) { 
			return(mActiveAnimation != nullptr &&
			mActiveAnimation->GetName() == name); }

		void SetDuration(float dur);
		void Reset();
		void SetPercent(Vector2 percent) { mPercent = percent; }
		Vector2 GetPercent() { return mPercent; }
		void SetShow(bool show) { mbShow = show; }
		void SwitchShow() { mbShow = !mbShow; }
	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;
		Image* mSpriteSheet;
		PlaySetting mPlaySettings;
		bool mbShow;

		float mAnimationDur;
		Vector2 mPercent;
	};
}
