#include "StateMan.h"
using namespace Engine;

Engine::StateMan::StateMan():add_s(false),replace_s(false),remove_s(false)
{
}

Engine::StateMan::~StateMan()
{
}

void Engine::StateMan::Add(unique_ptr<State> toAdd, bool replace)
{
	add_s = true;
	newState_s = move(toAdd);
	replace_s = replace;
}

void Engine::StateMan::PopCurrent()
{
	remove_s = true;
}

void Engine::StateMan::ProcessStateChange()
{
	if (remove_s && (!stateStack_s.empty()))
	{
		stateStack_s.pop();
		if (!stateStack_s.empty())
		{
			stateStack_s.top()->Start();
		}
		remove_s = false;
	}
	if(add_s)
	{
		if (replace_s && (!stateStack_s.empty()))
		{
			stateStack_s.pop();
			replace_s = false;
		}
		if (!stateStack_s.empty())
		{
			stateStack_s.top()->Pause();
		}
		stateStack_s.push(move(newState_s));
		stateStack_s.top()->Init();
		stateStack_s.top()->Start();
		add_s = false;
	}
}

unique_ptr<State>& Engine::StateMan::GetCurrent()
{
	return stateStack_s.top();
}


