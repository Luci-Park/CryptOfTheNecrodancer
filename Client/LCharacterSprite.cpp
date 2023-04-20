#include "LCharacterSprite.h"
#include "LTime.h"
#include "LMapManager.h"
#include "LAnimator.h"
namespace cl
{
	CharacterSprite::CharacterSprite(Scene* sc)
		: GameObject(sc, false)
		, mbDirIsUp(true)
		, mbIsJumping(false)
		, mAnimator(nullptr)
		, mbIsFlashing(false)
		, mbInShadows(true)
	{
	}
	CharacterSprite::~CharacterSprite()
	{
	}
	void CharacterSprite::Initialize()
	{
		GameObject::Initialize();
	}
	void CharacterSprite::Update()
	{
		if (mbIsJumping)
			Jump();
		if (mbIsFlashing)
			Flash();
		GameObject::Update();
	}
	void CharacterSprite::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CharacterSprite::Reset()
	{
		mTransform->SetLocalPos(Vector2::Zero);
		mbIsJumping = false;
	}
	void CharacterSprite::OnBeatChanged()
	{
		mAnimator->SetDuration(BeatManager::BeatDuration());
	}
	void CharacterSprite::Jump()
	{
		if (!mbIsJumping)
		{
			mbIsJumping = true;
			mbDirIsUp = true;
			return;
		}
		Vector2 target = mbDirIsUp ? Vector2::Up * UNITLENGTH * 0.5 : Vector2::Zero;
		if (Vector2::Distance(mTransform->GetLocalPos(), target) < 0.01f)
		{
			mbDirIsUp = !mbDirIsUp;
			if (mbDirIsUp) mbIsJumping = false;
		}
		mTransform->SetLocalPos(Vector2::MoveTowards(mTransform->GetLocalPos(), target, BeatManager::MoveSpeed() * 2 * Time::DeltaTime()));
	}
	void CharacterSprite::Sink()
	{
		mTransform->SetLocalPos(Vector2::Down * UNITLENGTH * 0.25);
		mAnimator->SetPercent({ 1.0f, 0.72f });
	}
	void CharacterSprite::UnSink()
	{
		Jump();
		mAnimator->SetPercent(Vector2::One);
	}
	void CharacterSprite::Flash()
	{
		if (!mbIsFlashing)
		{
			mbIsFlashing = true;
			mFlashDuration = BeatManager::BeatDuration()/4.0f;
			mFlashTimer = 0.0f;
			mAnimator->SwitchShow();
			return;
		}
		mFlashTimer += Time::DeltaTime();
		if (mFlashDuration <= mFlashTimer)
		{
			mFlashDuration += mFlashDuration;
			mAnimator->SwitchShow();
		}
		if (BeatManager::BeatDuration() <= mFlashDuration)
		{
			mbIsFlashing = false;
			mAnimator->SetShow(true);
		}
	}
	void CharacterSprite::SetShadow(bool inShadow)
	{
		if (mbInShadows != inShadow)
		{
			mbInShadows = inShadow;
			Turn(Vector2::Zero);
		}
	}
}
