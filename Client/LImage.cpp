#include "LImage.h"
#include "LApplication.h"
#include "LResources.h"

extern cl::Application application;

namespace cl
{
	Image* Image::CreateEmptyImage(const std::wstring& name, UINT width, UINT height, COLORREF rgb)
	{
		if (width == 0 || height == 0)
			return nullptr;

		Image* image = Resources::Find<Image>(name);
		if (image != nullptr)
			return image;

		image = new Image();
		HDC mainHdc = application.GetHdc();

		image->mBitmap = CreateCompatibleBitmap(mainHdc, width, height);
		
		image->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = width;
		image->mHeight = height;


		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), brush);
		Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldBrush);
		DeleteObject(brush);

		image->SetKey(name);
		Resources::Insert<Image>(name, image);
		return image;
	}
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{


	}

	Image::~Image()
	{

	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr
			, path.c_str(), IMAGE_BITMAP
			, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
			return E_FAIL;

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = application.GetHdc();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);

		return S_OK;
	}
	Sprite Image::GetFullImageSprite()
	{
		Sprite sp;
		sp.leftTop = Vector2::Zero;
		sp.size = Vector2((int)mWidth, mHeight);
		sp.offset -= sp.size / 2;
		return sp;
	}
}
