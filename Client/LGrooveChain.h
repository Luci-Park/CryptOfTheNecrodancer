#pragma once
#define MAXGROOVE 3
#define MINGROOVE 1
namespace cl
{
	class AudioClip;
	class GrooveChainManager
	{
	public:
		static GrooveChainManager& Instance()
		{
			static GrooveChainManager instance;
			return instance;
		}
		void Initialize();
		void Reset();
		int GrooveChain() { return _GrooveChain; }
		void LooseGroove();
		void IncreaseGroove();
		void SetGroove(int groove);
		void IncreaseKillCount();
	private:
		int _GrooveChain;
		AudioClip* _ChainStartSound;
		AudioClip* _ChainLooseSound;

		int _KillCount;
	};
}

