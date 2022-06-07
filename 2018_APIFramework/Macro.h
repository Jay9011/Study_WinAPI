#pragma once

#define SAFE_DELETE(ptr)        { if (ptr) { delete ptr; ptr = nullptr; } }
#define SAFE_DELETE_ARRAY(ptr)  { if (ptr) { delete[] ptr; ptr = nullptr; } }

#define DECLARE_SINGLE(type)			\
	private:							\
		static type* m_pInstance;		\
	public:								\
		static type* GetInst()			\
		{								\
			if (!m_pInstance)			\
				m_pInstance = new type;	\
			return m_pInstance;			\
		}								\
		static void DestroyInst()		\
		{								\
			SAFE_DELETE(m_pInstance);	\
		}								\
	private:							\
		type();							\
		~type();

#define DEFINITION_SINGLE(type)	type* type::m_pInstance = nullptr;
#define GET_SINGLE(type)		type::GetInst()
#define DESTROY_SINGLE(type)	type::DestroyInst()