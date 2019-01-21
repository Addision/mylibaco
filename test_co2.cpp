#include "Coroutine.h"
#include <iostream>

void co_fp1() {
    aco_t* this_co = aco_get_co();
    int ct = 0;
    while(1){
    	sleep(1);
    	std::cout<<"co_fp1 excute...."<<std::endl;
    	gPtr_Coroutine->Yield();
    }
    printf(
        "co:%p save_stack:%p share_stack:%p co_exit()\n",
        this_co, this_co->save_stack.ptr,
        this_co->share_stack->ptr
    );

    gPtr_Coroutine->ExitCo();
}

void co_fp2() {
    aco_t* this_co = aco_get_co();
    while(1){
    	sleep(1);
    	std::cout<<"co_fp2 excute...."<<std::endl;
    	gPtr_Coroutine->Yield();
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
	std::string name1 = "test1";
	std::string name2 = "test2";
	gPtr_Coroutine->Create(name1, co_fp1, nullptr);
	gPtr_Coroutine->Create(name2, co_fp2, nullptr);
	while(1)
	{
		gPtr_Coroutine->Resume(name1);
		gPtr_Coroutine->Resume(name2);
		if(gPtr_Coroutine->Status(name1) && gPtr_Coroutine->Status(name2))
		{
			break;
		}
	}
	gPtr_Coroutine->DestroyAll();
	return 0;
}