#pragma once
#define MAXGROOVE 3
#define MINGROOVE 1
namespace cl
{
	class AudioClip;
	class GrooveChainManager
	{
	public:
		static void Initialize();
		static int GrooveChain() { return _GrooveChain; }
		static void LooseGroove();
		static void IncreaseGroove();
		static void SetGroove(int groove);
		static void IncreaseKillCount();
	private:
		static int _GrooveChain;
		static AudioClip* _ChainStartSound;
		static AudioClip* _ChainLooseSound;

		static int _KillCount;
	};
}

