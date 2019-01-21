#include "Coroutine.h"
#include <iostream>

void co_fp0() {
    int* t = (int *)aco_get_arg();
    aco_t* this_co = aco_get_co();
    int ct = 0;
    while(ct < 500000000){
        (*t)++;
        ct++;
    }
    printf(
        "co:%p save_stack:%p share_stack:%p co_exit()\n",
        this_co, this_co->save_stack.ptr,
        this_co->share_stack->ptr
    );

    gPtr_Coroutine->ExitCo();
}

int main(int argc, char const *argv[])
{
	gPtr_Coroutine.reset(new Coroutine);
	int n = 0;
	std::string name = "test";
	gPtr_Coroutine->Create(name, co_fp0, &n);
	gPtr_Coroutine->Resume(name);
	while(1)
	{
		if(gPtr_Coroutine->Status(name))
		{
			break;
		}
	}
	gPtr_Coroutine->DestroyAll();
	return 0;
}