#pragma once
#include "CommonInclude.h"
namespace cl
{
	class AudioClip;
	class CadenceSound
	{
	public:
		CadenceSound();
		~CadenceSound();
		void PlayOnDigSound();
		void PlayMeleeSound(int hits);
		void PlayRangedSound();
		void PlayOnHitSound();
		void PlayOnDeathSound();
		void PlayVictorySound();

		void SetAudioClip();
		void SetDigSound();
		void SetAttackSound();
		void SetDeathSound();
		void SetOnHitSound();
		void SetVictorySound();
	private:
		std::vector<AudioClip*> mDigVoices;
		std::vector<std::vector<AudioClip*>>mMeleeHitVoices;
		std::vector<AudioClip*>mRangedHitVoices;
		std::vector<AudioClip*>mDeathVoices;
		std::vector<AudioClip*>mOnAttackedVoices;
		std::vector<AudioClip*>mVictoryVoices;
		AudioClip* mHitSFX;
		AudioClip* mDeathSFX;
	};
}

