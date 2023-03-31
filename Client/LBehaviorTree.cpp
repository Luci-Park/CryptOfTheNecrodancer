#include "LBehaviorTree.h"
namespace cl
{

	Action::Action(std::function<bool()> actionFunc)
		:action(actionFunc)
	{
	}
	bool Action::Run()
	{
		return action();
	}

	Selector::~Selector()
	{
		for (int i = 0; i < children.size(); ++i)
		{
			if (children[i] != nullptr)
			{
				delete children[i];
				children[i] = nullptr;
			}
		}

	}
	void Selector::AddChild(Node* node)
	{
		children.push_back(node);
	}
	bool Selector::Run()
	{
		for (Node* child : children) {
			if (child->Run()) {
				return true;
			}
		}
		return false;
	}
	Sequence::~Sequence()
	{
		for (int i = 0; i < children.size(); ++i)
		{
			if (children[i] != nullptr)
			{
				delete children[i];
				children[i] = nullptr;
			}
		}
	}
	bool Sequence::Run()
	{
		for (Node* child : children) {
			if (!child->Run()) {
				return false;
			}
		}
		return true;
	}
	Conditional::Conditional(std::function<bool()> condition, Node* child) : condition(condition), child(child) {}
	Conditional::~Conditional()
	{
		if (child != nullptr)
		{
			delete child;
			child = nullptr;
		}
	}
	bool Conditional::Run()
	{
		if (condition()) {
			return child->Run();
		}
		else {
			return false;
		}
	}
}
