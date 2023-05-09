#include "LGrooveChain.h"
#include "CommonInclude.h"
#include "LAudioClip.h"
#include "LResources.h"
namespace cl
{
	int GrooveChainManager::_GrooveChain = MINGROOVE;
	AudioClip* GrooveChainManager::_ChainStartSound = nullptr;
	AudioClip* GrooveChainManager::_ChainLooseSound = nullptr;
	int GrooveChainManager::_KillCount = 0;

	void GrooveChainManager::Initialize()
	{		
		_ChainStartSound = Resources::Load<AudioClip>(L"sfx_chain_groove_ST", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_chain_groove_ST.wav");
		_ChainLooseSound = Resources::Load<AudioClip>(L"sfx_chain_break_ST", L"..\\Assets\\Audio\\SoundEffects\\SFX\\sfx_chain_break_ST.wav");
	}
	void GrooveChainManager::Reset()
	{
		_GrooveChain = MINGROOVE;
		_KillCount = 0;
	}
	void GrooveChainManager::LooseGroove()
	{
		if (_GrooveChain > MINGROOVE)
			_ChainLooseSound->Play(false);
		_GrooveChain = MINGROOVE;
		_KillCount = 0;
	}
	void GrooveChainManager::IncreaseGroove()
	{
		if (_GrooveChain == MINGROOVE)
			_ChainStartSound->Play(false);
		_GrooveChain = std::clamp(_GrooveChain + 1, MINGROOVE, MAXGROOVE);
	}
	void GrooveChainManager::SetGroove(int groove)
	{
		if (_GrooveChain == MINGROOVE)
			_ChainStartSound->Play(false);
		_GrooveChain = std::clamp(groove, MINGROOVE, MAXGROOVE);
	}
	void GrooveChainManager::IncreaseKillCount()
	{
		if (_GrooveChain == MAXGROOVE)
			return;
		_KillCount++;
		if (_GrooveChain == MINGROOVE)
			IncreaseGroove();
		if (_GrooveChain > MINGROOVE && _KillCount >= 5)
			IncreaseGroove();
	}
}