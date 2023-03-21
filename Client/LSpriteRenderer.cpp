#include "LSpriteRenderer.h"
#include "LResources.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LCamera.h"
#include "LImage.h"
namespace cl
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mImage(nullptr)
		, mAlpha(255)
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::Render(HDC hdc)
	{ 
		Transform* tr
			=GetOwner()->GetComponent<Transform>();
		Vector2 scale = tr->GetScale();

		Vector2 pos = tr->GetPos();
		pos += Vector2(mSprite.offset.x * scale.x, mSprite.offset.y * scale.y);
		if (GetOwner()->IsUI())
			pos = Camera::CaluatePos(pos);

		if (mAlpha == 255)
		{
			TransparentBlt(hdc, pos.x, pos.y, mSprite.size.x * scale.x, mSprite.size.y * scale.y,
				mImage->GetHdc(), 0, 0, mSprite.size.x, mSprite.size.y, RGB(255, 0, 255));
		}
		else
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (BYTE)mAlpha;

			AlphaBlend(hdc, pos.x, pos.y, mSprite.size.x * scale.x, mSprite.size.y * scale.y,
				mImage->GetHdc(), 0, 0, mSprite.size.x, mSprite.size.y, func);
		}
	}
	void SpriteRenderer::SetImage(Image* image, Sprite sp)
	{
		mImage = image;
		mSprite = sp;
	}

	void SpriteRenderer::SetImage(const std::wstring& key, const std::wstring& path)
	{
		mImage = Resources::Load<Image>(key, path);
		mSprite = mImage->GetFullImageSprite();
	}

}