#pragma once
#include "LuciEngine.h"

namespace cl
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
		void SetID(UINT64 id) { mID = id; }
		UINT64 GetID() { return mID; }

		bool IsActive() { return mbIsactive; }
		void SetActive(bool active) { mbIsactive = active; }
	private:
		std::wstring mName;
		UINT64 mID;
		bool mbIsactive;
	};
}
