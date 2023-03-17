#include "LCadenceBody.h"
#include "LAnimator.h"
namespace cl
{
	CadenceBody::CadenceBody(Scene* scene)
		:GameObject(scene, false)
	{

	}
	CadenceBody::~CadenceBody()
	{
	}
	void CadenceBody::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		std::wstring path = L"..\\Assets\\Arts\\Player\\Cadence.bmp";
		mAnimator->CreateAnimation(L"CadenceBody", L"Cadence", path, 16, 16, 0, 2, 4, Vector2::Zero, 0.36f);
		mAnimator->Play(L"CadenceBody", true);
		GameObject::Initialize();
	}
	void CadenceBody::Update()
	{
		GameObject::Update();
	}
	void CadenceBody::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CadenceBody::Release()
	{
		GameObject::Release();
	}
}