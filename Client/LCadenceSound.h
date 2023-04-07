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
		void SetAudioClip();
		void SetDigSound();
		void SetAttackSound();
		void SetDeathSound();
		void SetOnHitSound();
	private:
		std::vector<AudioClip*> mDigVoice;
		std::vector<std::vector<AudioClip*>>mMeleeHitVoice;
		std::vector<AudioClip*>mRangedHitVoice;
		std::vector<AudioClip*>mDeathVoice;
		std::vector<AudioClip*>mOnAttackedVoice;
		AudioClip* mHitSFX;
		AudioClip* mDeathSFX;
	};
}

