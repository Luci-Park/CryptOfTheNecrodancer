#include "LCadenceHead.h"
#include "LAnimator.h"
namespace cl
{
	CadenceHead::CadenceHead(Scene* scene)
		:GameObject(scene, false)
		, mAnimator(nullptr)
	{

	}
	CadenceHead::~CadenceHead()
	{
	}
	void CadenceHead::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		std::wstring path = L"..\\Assets\\Arts\\Player\\Cadence.bmp";
		mAnimator->CreateAnimation(L"CadenceHead", L"Cadence", path, 16, 16, 0, 0, 4, Vector2::Zero, 0.36f);
		mAnimator->Play(L"CadenceHead", true);
		GameObject::Initialize();
	}
	void CadenceHead::Update()
	{
		GameObject::Update();
	}
	void CadenceHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CadenceHead::Release()
	{
		GameObject::Release();
	}
}