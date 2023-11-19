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


#pragma once

#include <string>

enum progType { WIN32_PROG, CONSOLE_PROG };

typedef std::basic_string<TCHAR> generic_string;
typedef std::basic_stringstream<TCHAR> generic_stringstream;

class Process
{
public:
	Process(const TCHAR* cmd, const TCHAR* args, const TCHAR* cDir)
		:m_command(cmd), m_args(args), m_curDir(cDir) {}

	void run() const;

protected:
	generic_string m_command;
	generic_string m_args;
	generic_string m_curDir;
};
