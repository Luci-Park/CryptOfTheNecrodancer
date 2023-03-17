#include "LArrowUI.h"
#include "LResources.h"
#include "LImage.h"
namespace cl
{
	ArrowUI::ArrowUI()
		:GameObject(true)
	{
	}
	ArrowUI::~ArrowUI()
	{
	}
	void ArrowUI::Initialize()
	{
		/*mImage = Resources::Load<Image>(L"Arrow",
			L"..\\FNFAssets\\Art\\24Bit\\UI\\Notes\\PressedEffect\\Down\\Down.bmp");*/
		mImage = Resources::Load<Image>(L"Arrow",
			L"C:\\Users\\user\\Documents\\_Quve17\\Luci\\Coding\\AssortRock\\AssortRockCpp\\WinAPI\\Resources\\Tile.bmp");
		GameObject::Initialize();
	}
	void ArrowUI::Update()
	{
		GameObject::Initialize();
	}
	void ArrowUI::Render(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(),
			mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(),
			func);
		GameObject::Initialize();
	}
	void ArrowUI::Release()
	{
		GameObject::Initialize();
	}
}