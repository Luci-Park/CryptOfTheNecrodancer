#include "LWallTorch.h"
#include "LMapManager.h"
#include "LAnimator.h"
#include "LBeatManager.h"
namespace cl
{
	WallTorch::WallTorch(Scene* sc)
		:TileObject(sc)
	{
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
		mAnimator->CreateAnimation(L"Idle", L"WallTorch", path, 4, 1, 0, 0, 4, offset, BeatManager::BeatDuration());
		mAnimator->Play(L"Idle", true, false);
	}
	void WallTorch::Update()
	{
		TileObject::Update();
		if (MapManager::GetWall(mIndex) == nullptr)
			OnDestroy();
	}
	void WallTorch::Render(HDC hdc)
	{
		TileObject::Render(hdc);
	}
	void WallTorch::OnAttacked(float attackPower, Vector2 dir)
	{
	}
	void WallTorch::OnDestroy()
	{
		MapManager::DestroyTileObject(mIndex);
	}
	void WallTorch::SetBrightness()
	{
		mInnerRadius = 0.0;
		mOuterRadius = 4.25;
	}
}
