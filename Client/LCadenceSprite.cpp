#include "LCadenceSprite.h"
#include "LCadenceHead.h"
#include "LCadenceBody.h"
#include "LObject.h"
#include "LConductor.h"
namespace cl
{
	CadenceSprite::CadenceSprite(Scene* sc)
		: CharacterSprite(sc)
		, mHead(nullptr), mBody(nullptr)
	{
	}
	CadenceSprite::~CadenceSprite()
	{
	}
	void CadenceSprite::Initialize()
	{
		CharacterSprite::Initialize();
		mBody = object::Instantiate<CadenceBody>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
		mHead = object::Instantiate<CadenceHead>(GameObject::GetScene(), GameObject::mTransform, GameObject::mTransform->GetPos(), eLayerType::Player);
	}
	void CadenceSprite::Update()
	{
		CharacterSprite::Update();
	}
	void CadenceSprite::Render(HDC hdc)
	{
		CharacterSprite::Render(hdc);
		mBody->Render(hdc);
		mHead->Render(hdc);
	}
	void CadenceSprite::Turn(Vector2 dir)
	{
		mHead->Flip(dir);
		mBody->Flip(dir);
	}
	void CadenceSprite::OnBeatChanged()
	{
		float dur = Conductor::Instance().SecondsPerBeat();
		mHead->SetDuration(dur);
		mBody->SetDuration(dur);
	}
	void CadenceSprite::Sink()
	{
		mTransform->SetLocalPos(Vector2::Down * UNITLENGTH * 0.25);
		mBody->Sink();
	}
	void CadenceSprite::UnSink()
	{
		Jump();
		mBody->UnSink();
	}
}