#pragma once

#include <memory>
#include <stack>
#include "State.h"

namespace Flappy {

	class StateMachine 
	{
	private:
		std::stack<std::unique_ptr<State>> m_states;
		std::unique_ptr<State> m_newState;

		bool m_isRemoving, m_isReplacing, m_isAdding;
	public:
		StateMachine() = default;
		~StateMachine() = default;

		void addState(std::unique_ptr<State> newState, bool isReplacing = true);
		void removeState();
		void processStateChanges();
		std::unique_ptr<State>& getActiveState();
	};
}