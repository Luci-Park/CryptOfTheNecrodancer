#include "LWallTorch.h"
#include "LMapManager.h"
#include "LAnimator.h"
#include "LBeatManager.h"
#include "LLightSource.h"
#include "LTileLight.h";
namespace cl
{
	WallTorch::WallTorch(Scene* sc)
		:TileObject(sc)
	{
		mLightSource = new LightSource(mTransform, 0.0, 4.25);
	}
	WallTorch::~WallTorch()
	{
		if (mLightSource != nullptr)
		{
			delete mLightSource;
			mLightSource = nullptr;
		}
	}
	void WallTorch::Initialize()
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
		std::wstring path = L"..\\Assets\\Arts\\Stage Elements\\Torches.bmp";
		mAnimator = AddComponent<Animator>();
		TileObject::Initialize();
		Vector2 offset;
		offset.x = -6;
		offset.y = -19 - 15;
		mAnimator->CreateAnimation(L"Idle", L"WallTorch", path, 4, 1, 0, 0, 4, offset, BeatManager::SecondsPerBeat());
		mAnimator->Play(L"Idle", Animator::PlaySetting::Loop, false);
	}
	void WallTorch::Update()
	{
		TileObject::Update();
		
		if (!MapManager::GetLight(mIndex)->IsInSight())
			mAnimator->SetShow(false);
		else
			mAnimator->SetShow(true);
		if (MapManager::GetWall(mIndex) == nullptr)
			OnDestroy();
	}
	void WallTorch::Render(HDC hdc)
	{
		TileObject::Render(hdc);
	}
	bool WallTorch::OnAttacked(float attackPower, Vector2 dir)
	{
		return false;
	}
}
