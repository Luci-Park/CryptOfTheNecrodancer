#pragma once
#include "LComponent.h"
#include "LAnimation.h"
#include "LImage.h"

namespace cl
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			
			std::function<void()> mEvent;
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name, Image* sheet,
			UINT coulmn, UINT row, 
			UINT sCol, UINT sRow, 
			UINT spriteLength, Vector2 offset, float duration);
		void CreateAnimation(const std::wstring& name,
			const std::wstring& sheetName,const std::wstring& path, 
			UINT coulmn, UINT row, UINT sCol, UINT sRow,
			UINT spriteLength, Vector2 offset, float duration);
		void CreateAnimations(const std::wstring& path, const std::wstring& key, Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop, bool reverse);

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		
		bool IsComplete() { return mActiveAnimation->IsComplete(); }
		bool IsAnimationPlaying(const std::wstring& name) { 
			return(mActiveAnimation != nullptr &&
			mActiveAnimation->GetName() == name); }

		void SetDuration(float dur);
		void Reset();

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;

		Animation* mActiveAnimation;
		Image* mSpriteSheet;
		bool mbLoop;
		float mAnimationDur;
	};
}
