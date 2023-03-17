#include "LGameObject.h"

namespace cl
{
	class Animator;
	class Boyfriend : public GameObject
	{
	public:
		enum eBFState{
			Idle,
			Up, Down, Left, Right,
			UpBad, DownBad, LeftBad, RightBad,
			Size
		};
		Boyfriend();
		~Boyfriend();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetSingingState(eBFState state) { mState = state; }
	protected:
	private:
		void OnIdle();
		void OnKeyDown();
		void OnKeyUp();
		void Move();
		void BFWriteFile();
	private:
		const static std::wstring animation[];
		const static std::wstring animationPath[];

		Animator* mAnimator;
		eBFState mState;
	};
}
