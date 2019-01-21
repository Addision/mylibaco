#pragma once


#include <functional>
#include <memory>
#include <string>
#include <map>
#include "libaco/libaco.h"

typedef void (*aco_func)(void);

class sCo
{
public:
	sCo(aco_t* pco, aco_share_stack_t* psstk):co(pco), sstk(psstk){}
	aco_t* co;
	aco_share_stack_t* sstk;
};

class Coroutine
{
	typedef std::map<std::string, sCo> co_type;
public:
	Coroutine();
	~Coroutine();

	aco_t* Create(std::string& coname, aco_func oCb, void * arg);
	aco_t* GetCo(std::string& coname);
	void Resume(aco_t* pco);
	void Resume(std::string& coname);
	int Status(aco_t* pco);
	int Status(std::string& coname);
	void Yield();
	void DestroyCo(std::string& coname);
	void DestroyAll();
	void ExitCo(); //must call this function, when return from coroutine function
private:
	aco_t* m_pMainCo;
	co_type m_mCo;
};

extern std::unique_ptr<Coroutine> gPtr_Coroutine;


