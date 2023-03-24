#pragma once
#include "LComponent.h"
#include "LSprite.h"
namespace cl
{
	class Image;
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetImage(Image* image);
		void SetImage(Image* image, Sprite sp);
		void SetImage(const std::wstring& key, const std::wstring& path);
		void SetSprite(Sprite sprite) { mSprite = sprite; }
		void AddAlpha(int alpha) { mAlpha = alpha; }
	private:
		Image* mImage;
		Sprite mSprite;
		int mAlpha;
		
	};
}

