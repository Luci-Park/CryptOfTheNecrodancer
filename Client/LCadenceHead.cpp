#include "LCadenceHead.h"
#include "LAnimator.h"
namespace cl
{
	CadenceHead::CadenceHead()
		:GameObject(false)
	{

	}
	CadenceHead::~CadenceHead()
	{
	}
	void CadenceHead::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		std::wstring path = L"..\\Assets\\Arts\\Player\\Cadence.bmp";
		mAnimator->CreateAnimation(L"CadenceHead", L"CadenceHead", path, Vector2::Zero, 16, 17,4, Vector2::Zero, 0.1f);
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