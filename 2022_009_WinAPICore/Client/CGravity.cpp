#include "pch.h"
#include "CGravity.h"

CGravity::CGravity()
	: m_pOwner(nullptr)
{
}

CGravity::~CGravity()
{
}

void CGravity::finalupdate()
{
	if (m_pOwner == nullptr)
		return;
}
