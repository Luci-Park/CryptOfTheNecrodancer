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
		void Reset();
		int GrooveChain() { return mGrooveChain; }
		void LooseGroove();
		void IncreaseGroove();
		void SetGroove(int groove);
		void IncreaseKillCount();
	private:
		GrooveChainManager();
		GrooveChainManager(const GrooveChainManager&) = delete; //disable operator
		GrooveChainManager* operator =(const GrooveChainManager&) = delete; // disable operator
		int mGrooveChain;
		AudioClip* mChainStartSound;
		AudioClip* mChainLooseSound;

		int mKillCount;
	};
}

