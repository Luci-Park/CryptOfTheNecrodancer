#pragma once
#include "LuciEngine.h"
namespace cl
{
	class GameObject;
	class Image;
	class Camera
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render(HDC hdc);
		static void Clear();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Vector2 CaluatePos(Vector2 pos) { return pos - mDistance; }

		static void StartFadeIn();
		static void StartFadeOut();
	private:
		static void FadeIn(HDC hdc);
		static void FadeOut(HDC hdc);
	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;
		static Image* mFilm;
		
		static enum eFilmState {FadingIn, FadingOut, Idle};
		static eFilmState meFilmState;
		static float mFilmAlpha;
	};
}
