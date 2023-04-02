#include "LEntity.h"


namespace cl
{
	Entity::Entity()
		: mName(L"")
		, mID((UINT64)this)
		, mbIsactive(true)
	{

	}

	Entity::~Entity()
	{
	}

}
