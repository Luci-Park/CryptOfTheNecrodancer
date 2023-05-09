#include "LBeatJudge.h"
#include "LObject.h"
#include "LConductor.h"
#include "LBeatingHeartUI.h"
#include "LBeatBar.h"
#include "LApplication.h"
#include "LGrooveChain.h"
#include "LMapManager.h"
#include "LCadence.h"

extern::cl::Application application;
namespace cl
{
	BeatJudge::BeatJudge(Scene* sc)
		: GameObject(sc, true)
		, mBeatsShownInAdvance(4)
		, mNextBeatToShow(1)
	{
		mTransform->SetScale(Vector2::One * UNITSCALE);
		mTransform->SetPos(Vector2(application.GetCenter().x, application.GetCenter().y * 1.7));
		//mTransform->SetPos(Vector2(application.GetCenter().x, 0.0));
		mDespawnPoint = mTransform->GetPos();
		int percent = application.GetWidth() / 10;
		mRightSpawn = Vector2(application.GetWidth() - percent, mTransform->GetPos().y);
		mLeftSpawn = Vector2((int)percent, (int)mTransform->GetPos().y);		
	}
	BeatJudge::~BeatJudge()
	{
	}
	void BeatJudge::Initialize()
	{
		GameObject::Initialize();
		object::Instantiate<BeatingHeartUI>(mTransform, mTransform->GetPos(), eLayerType::UI);
		for (int i = 0; i <= mBeatsShownInAdvance; i++)
		{
			BeatBar* left = object::Instantiate<BeatBar>(mTransform, eLayerType::Effects);
			left->SetBar(this, mLeftSpawn, mDespawnPoint, Vector2::Left, mNextBeatToShow, mBeatsShownInAdvance);
			BeatBar* right = object::Instantiate<BeatBar>(mTransform, eLayerType::Effects);
			right->SetBar(this, mRightSpawn, mDespawnPoint, Vector2::Right, mNextBeatToShow, mBeatsShownInAdvance);
			mNextBeatToShow++;
		}
	}
	void BeatJudge::Update()
	{
		if (!Conductor::Instance().IsPlaying()) return;
		if (mNextBeatToShow < Conductor::Instance().SongPositionBeats() + mBeatsShownInAdvance)
		{
			BeatBar* left = object::Instantiate<BeatBar>(mTransform, eLayerType::Effects);
			left->SetBar(this, mLeftSpawn, mDespawnPoint, Vector2::Left, mNextBeatToShow, mBeatsShownInAdvance);
			BeatBar* right = object::Instantiate<BeatBar>(mTransform, eLayerType::Effects);
			right->SetBar(this, mRightSpawn, mDespawnPoint, Vector2::Right, mNextBeatToShow, mBeatsShownInAdvance);
			mNextBeatToShow++;
		}
	}
	void BeatJudge::LeftBeatEnter(BeatBar* bar)
	{
		if (mCurrentLeftBeat != bar)
			mCurrentLeftBeat = bar;
	}
	void BeatJudge::RightBeatEnter(BeatBar* bar)
	{
		if (mCurrentRightBeat != bar)
			mCurrentRightBeat = bar;
	}
	void BeatJudge::LeftBeatExit(BeatBar* bar)
	{
		if (mCurrentLeftBeat == bar)
		{
			if (MapManager::GetPlayer()->HasMoved())
			{
				GrooveChainManager::Instance().LooseGroove();
				Conductor::Instance().OnPlayerMove();
			}
			mCurrentLeftBeat = nullptr;
		}
	}
	void BeatJudge::RightBeatExit(BeatBar* bar)
	{
		if (mCurrentRightBeat == bar)
		{
			mCurrentRightBeat = nullptr;
		}
	}
	void BeatJudge::OnValidInput()
	{
		if (mCurrentLeftBeat != nullptr)
		{
			mCurrentLeftBeat->Destroy();
			mCurrentLeftBeat = nullptr;
		}
		
		if (mCurrentRightBeat != nullptr)
		{
			mCurrentRightBeat->Destroy();
			mCurrentRightBeat = nullptr;
		}
	}
	bool BeatJudge::IsInBeat()
	{
		return (mCurrentLeftBeat && mCurrentRightBeat);
	}
}