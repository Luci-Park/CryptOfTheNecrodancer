#include "LBeatUI.h"
#include "LObject.h"
#include "LConductor.h"
#include "LBeatingHeartUI.h"
#include "LBeatBar.h"
#include "LApplication.h"

extern::cl::Application application;
namespace cl
{
	BeatUI::BeatUI(Scene* sc)
		: GameObject(sc, true)
		, mBeatsShownInAdvance(4)
		, mNextBeatToShow(1)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
		//mTransform->SetPos(Vector2(application.GetCenter().x, application.GetCenter().y * 1.7));
		mTransform->SetPos(Vector2(application.GetCenter().x, 0.0));
		mDespawnPoint = mTransform->GetPos();
		int percent = application.GetWidth() / 10;
		mRightSpawn = Vector2(application.GetWidth() - percent, mTransform->GetPos().y);
		mLeftSpawn = Vector2((int)percent, (int)mTransform->GetPos().y);		
	}
	BeatUI::~BeatUI()
	{
	}
	void BeatUI::Initialize()
	{
		GameObject::Initialize();
		object::Instantiate<BeatingHeartUI>(mTransform, mTransform->GetPos(), eLayerType::UI);
		for (int i = 0; i < mBeatsShownInAdvance; i++)
		{
			BeatBar* left = object::Instantiate<BeatBar>(mTransform, eLayerType::UI);
			left->SetBar(mLeftSpawn, mDespawnPoint, Vector2::Left, mNextBeatToShow, mBeatsShownInAdvance);
			BeatBar* right = object::Instantiate<BeatBar>(mTransform, eLayerType::UI);
			right->SetBar(mRightSpawn, mDespawnPoint, Vector2::Right, mNextBeatToShow, mBeatsShownInAdvance);
			mNextBeatToShow++;
		}
	}
	void BeatUI::Update()
	{
		if (!Conductor::Instance().IsPlaying()) return;
		if (mNextBeatToShow < Conductor::Instance().SongPositionBeats() + mBeatsShownInAdvance)
		{
			BeatBar* left = object::Instantiate<BeatBar>(mTransform, eLayerType::UI);
			left->SetBar(mLeftSpawn, mDespawnPoint, Vector2::Left, mNextBeatToShow, mBeatsShownInAdvance);
			BeatBar* right = object::Instantiate<BeatBar>(mTransform, eLayerType::UI);
			right->SetBar(mRightSpawn, mDespawnPoint, Vector2::Right, mNextBeatToShow, mBeatsShownInAdvance);
			mNextBeatToShow++;
		}
	}
}