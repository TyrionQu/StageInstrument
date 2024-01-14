#pragma once

#include "stdafx.h"

#include <string>

class CryptoppVikey
{
public:
	CryptoppVikey();

	DWORD verifyVikey(const std::string& file);
};

