// This file is part of Notepad++ project
// Copyright (C)2021 Don HO <don.h@free.fr>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "pch.h"
#include "Process.h"


bool Process::run() const
{
	const TCHAR* opVerb = TEXT("open");
	HINSTANCE result = ::ShellExecute(NULL, opVerb, m_command.c_str(), m_args.c_str(), m_curDir.c_str(), SW_SHOWNORMAL);
	if (result <= (HINSTANCE)32) {
		DWORD error = GetLastError();
		return false;
	}
	return true;
}