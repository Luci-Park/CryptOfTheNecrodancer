#include "LGrooveChain.h"
#include "CommonInclude.h"
#include "LAudioClip.h"
#include "LResources.h"
namespace cl
{
	GrooveChainManager::GrooveChainManager()
		: mGrooveChain(MINGROOVE)
		, mKillCount(0)
	{
		mChainStartSound = Resources::Load<AudioClip>(L"sfx_chain_groove_ST", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_chain_groove_ST.wav");
		mChainLooseSound = Resources::Load<AudioClip>(L"sfx_chain_break_ST", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_chain_break_ST.wav");
	}
	void GrooveChainManager::Reset()
	{
		mGrooveChain = MINGROOVE;
		mKillCount = 0;
	}
	void GrooveChainManager::LooseGroove()
	{
		if (mGrooveChain > MINGROOVE)
			mChainLooseSound->Play(false);
		mGrooveChain = MINGROOVE;
		mKillCount = 0;
	}
	void GrooveChainManager::IncreaseGroove()
	{
		if (mGrooveChain == MINGROOVE)
			mChainStartSound->Play(false);
		mGrooveChain = std::clamp(mGrooveChain + 1, MINGROOVE, MAXGROOVE);
	}
	void GrooveChainManager::SetGroove(int groove)
	{
		if (mGrooveChain == MINGROOVE)
			mChainStartSound->Play(false);
		mGrooveChain = std::clamp(groove, MINGROOVE, MAXGROOVE);
	}
	void GrooveChainManager::IncreaseKillCount()
	{
		if (mGrooveChain == MAXGROOVE)
			return;
		mKillCount++;
		if (mGrooveChain == MINGROOVE)
			IncreaseGroove();
		if (mGrooveChain > MINGROOVE && mKillCount >= 5)
			IncreaseGroove();
	}
}