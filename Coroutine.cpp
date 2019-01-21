
#include "Coroutine.h"

std::unique_ptr<Coroutine> gPtr_Coroutine = nullptr;

Coroutine::Coroutine()
{
	aco_thread_init(NULL);
    m_pMainCo = aco_create(NULL, NULL, 0, NULL, NULL);
}

Coroutine::~Coroutine()
{}


aco_t* Coroutine::Create(std::string& name, aco_func oCb, void * arg)
{
	if(m_mCo.find(name) != m_mCo.end())
	{
		return nullptr;
	}
	aco_share_stack_t* sstk = aco_share_stack_new(0);
	if(!sstk)
	{
		return nullptr;
	}
	aco_t* pco = aco_create( m_pMainCo, sstk, 0, oCb, arg);
	sCo sco(pco, sstk);
	m_mCo.emplace(name, sco);
	return pco;
}

void Coroutine::Resume(std::string& coname)
{
	auto it = m_mCo.find(coname);
	if(it != m_mCo.end())
	{
		aco_resume(it->second.co);
	}
}

void Coroutine::Resume(aco_t* pco)
{
	if(!pco)
	{
		return;
	}
	aco_resume(pco);
}

void Coroutine::Yield()
{
	aco_yield();
}

aco_t* Coroutine::GetCo(std::string& coname)
{
	auto it = m_mCo.find(coname);
	if(it != m_mCo.end())
	{
		return it->second.co;
	}
	return nullptr;
}

int Coroutine::Status(std::string& coname)
{
	aco_t* pco = GetCo(coname);
	if(pco)
	{
		return pco->is_end;
	}
	return 0;
}

int Coroutine::Status(aco_t* pco)
{
	return pco->is_end; //1 end 0 running
}

void Coroutine::ExitCo()
{
	aco_exit();
}

void Coroutine::DestroyCo(std::string& coname)
{
	auto it = m_mCo.find(coname);
	if(it != m_mCo.end())
	{
		aco_destroy(it->second.co);
		aco_share_stack_destroy(it->second.sstk);
		m_mCo.erase(it);
	}
}

void Coroutine::DestroyAll()
{
	for(auto it = m_mCo.begin(); it != m_mCo.end();)
	{
		aco_destroy(it->second.co);
		aco_share_stack_destroy(it->second.sstk);
		it = m_mCo.erase(it);
	}
    aco_destroy(m_pMainCo);
    m_pMainCo = nullptr;
}




