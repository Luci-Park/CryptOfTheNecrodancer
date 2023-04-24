#include "LAnimator.h"
#include "LResources.h"

namespace cl
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mSpriteSheet(nullptr)
		, mPlaySettings(PlaySetting::Once)
		, mPercent(Vector2::One)
		, mbShow(true)
	{

	}

	Animator::~Animator()
	{
		for (auto animation : mAnimations)
		{
			delete animation.second;
			animation.second = nullptr;
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			if (mActiveAnimation->IsComplete())
			{
				if (mPlaySettings == PlaySetting::Loop)
					mActiveAnimation->Reset();
				else if(mPlaySettings == PlaySetting::Once)
					mActiveAnimation = nullptr;
			}
			
		}
	}
	
	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation && mbShow)
		{
			mActiveAnimation->Render(hdc);
		}
	}
	
	void Animator::CreateAnimation(const std::wstring& name
		, Image* sheet, UINT coulmn, UINT row, UINT sCol, UINT sRow, UINT spriteLength
		, Vector2 offset, float duration)
	{
		Animation* animation = FindAnimation(name);

		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(sheet,coulmn, row, sCol, sRow, spriteLength, offset, duration);
		animation->SetName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
	}

	void Animator::CreateAnimation(const std::wstring& animationName,
		const std::wstring& sheetName, const std::wstring& sheetPath
		, UINT coulmn, UINT row
		, UINT sCol, UINT sRow, UINT spriteLength
		, Vector2 offset, float duration)
	{
		Animation* animation = FindAnimation(animationName);
		if (animation != nullptr)
			return;

		Image* sheet = Resources::Load<Image>(sheetName, sheetPath);
		animation = new Animation();
		animation->Create(sheet, coulmn, row, sCol, sRow, spriteLength, offset, duration);
		animation->SetName(animationName);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(animationName, animation));
	}

	void Animator::CreateAnimation(const std::wstring& animationName, const std::wstring& sheetName, const std::wstring& sheetPath, Vector2 leftTop, Vector2 size, UINT spriteLength, float duration)
	{
		Animation* animation = FindAnimation(animationName);
		if (animation != nullptr)
			return;

		Image* sheet = Resources::Load<Image>(sheetName, sheetPath);
		animation = new Animation();
		animation->Create(sheet, leftTop, size, spriteLength, size * -0.5f, duration);
		animation->SetName(animationName);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(animationName, animation));

	}

	void Animator::CreateAnimations(const std::wstring& path, const std::wstring& key, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images = {};
		for (const auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = path + L"\\" + fileName;
			std::wstring imageKey = key + L"_" + fileName;
			const std::wstring ext = p.path().extension();
			if (ext == L".png")
				continue;

			Image* image = Resources::Load<Image>(imageKey, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
			{
				width = image->GetWidth();
			}
			if (height < image->GetHeight())
			{
				height = image->GetHeight();
			}
			fileCount++;
		}

		mSpriteSheet = Image::CreateEmptyImage(key, width * fileCount, height);

		//
		int index = 0;
		for (Image* image : images)
		{
			int centerX = (width - image->GetWidth()) / 2;
			int centerY = (height - image->GetHeight());

			BitBlt(mSpriteSheet->GetHdc()
				, width * index + centerX
				, 0 + centerY
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			index++;
		}

		CreateAnimation(key, mSpriteSheet, index, 1, 0, 0, index, offset, duration);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::Play(const std::wstring& name, PlaySetting loop, bool reverse)
	{
		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->SetReverse(reverse);
		mActiveAnimation->Reset();
		mPlaySettings = loop;

	}

	void Animator::PlayNoDuplication(const std::wstring& name, bool loop, bool reverse)
	{
		if (!IsAnimationPlaying(name))
			Play(name, mPlaySettings, reverse);
	}

	bool Animator::IsComplete()
	{
		if (mActiveAnimation != nullptr)
			return mActiveAnimation->IsComplete();
		return true;
	}

	void Animator::Reset()
	{
		if(mActiveAnimation != nullptr)
			mActiveAnimation->Reset();
	}

	void Animator::SetDuration(float dur)
	{
		mAnimationDur = dur;
		for (auto animation : mAnimations)
		{
			animation.second->SetDuration(mAnimationDur);
		}
	}
}