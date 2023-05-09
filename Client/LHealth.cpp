#include "LHealth.h"
#include "LCadence.h"
#include "LObject.h"
#include "LHeartUI.h"
namespace cl
{
	float Health::_defaultMaxHealth = 5;
	float Health::_currentMaxHealth = 5;
	float Health::_currentHealth = 5;
	void Health::Reset()
	{
		_currentMaxHealth = _defaultMaxHealth;
		_currentHealth = _defaultMaxHealth;
	}

	Health::Health(Cadence* player)
		: mPlayer(player)
		, startPosition(Vector2(1250, 50))
		, unitLength(80)
	{
		mMaxHealth = _currentMaxHealth;
		mHealth = _currentHealth;
		SetHeart();
	}
	Health::~Health()
	{
		_currentMaxHealth = mMaxHealth;
		_currentHealth = mHealth;
	}
	void Health::OnDamage(float damage)
	{
		mHealth -= damage;
		if (mHealth <= 0)
			OnHealthIsZero();
		SetHeart();
	}
	void Health::OnHeal(float heal)
	{
		mHealth = std::clamp(mHealth + heal, 0.0f, mMaxHealth);
		SetHeart();
	}
	void Health::SetHeart()
	{
		for (int i = 0; i < mMaxHealth; i++)
		{
			if (mHeartUI.size() <= i || mHeartUI[i] == nullptr)
			{
				HeartUI* heart = object::Instantiate<HeartContainerUI>(startPosition - Vector2(UNITLENGTH * i ,0), eLayerType::UI);
				mHeartUI.push_back(heart);
			}
			if (mMaxHealth - i > mHealth)
			{
				if (mMaxHealth - i - 1 >= mHealth)
					mHeartUI[i]->SetHeart(HeartUI::State::Empty);
				else
					mHeartUI[i]->SetHeart(HeartUI::State::Half);
			}
			else {
				mHeartUI[i]->SetHeart(HeartUI::State::Full);
			}		
		}
		if (mHeartUI.size() > mMaxHealth)
		{
			for (int i = mHeartUI.size(); i >= mMaxHealth; --i)
			{
				mHeartUI[i]->Destroy();
				mHeartUI[i] = nullptr;
			}
		}
	}
	void Health::OnHealthIsZero()
	{
		mPlayer->OnDestroy();
	}
}
