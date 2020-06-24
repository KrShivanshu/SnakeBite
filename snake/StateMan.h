#pragma once
#include <stack>
#include <memory>
#include "State.h"
#include <iostream>

using namespace std;
namespace Engine {
	class StateMan
	{
	private:
		stack<unique_ptr<State>>stateStack_s;
		unique_ptr<State>newState_s;
		bool add_s;
		bool replace_s;
		bool remove_s;

	public:
		StateMan();
		~StateMan();

		void Add(unique_ptr<State>toAdd, bool replace = false);
		void PopCurrent();
		void ProcessStateChange();
		
		unique_ptr<State> &GetCurrent();
	};
}