////////////////////////////////////////////////////////////////////////////////
// FileManager.cpp - find files matching specified patterns                   //
//               on a specified path                                          //
// ver 2.0                                                                    //
// Language:    C++, Visual Studio 2015                                      //
// Application: Code Parser with Abstract Syntax Tree (AST), CSE687 - Object Oriented Design, SP16       //
//              Alienware R15, Core i5, Windows 10                           //
// Author:      Saathvik Shashidhar Gowrapura, SUID: 450734672               //
//              sgowrapu@syr.edu, (315)-751-1059                             //
// Original author: Jim Fawcett, CST 4-187, Syracuse University              // 
//              jfawcett@twcny.rr.com, (315)-443-3948                        //
//////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
===================
This file  finds files matching specified patterns on a specified path

Public Interface:
=================
FileMgr(const std::string& path, DataStore& ds) - construcotr
void addPattern(const std::string& patt) - adds the specified pattern
void search() - calls find
void find(const std::string& path) - find all files in the path

Required Files:
===============
StructElement.h

Build Command:
==============
devenv ScopeStack.sln /rebuild debug

Maintenance History:
====================
/*
* ver 2.0 : 12 Mar 2016
* - fixes bug in directory recursion in find(path)
* - reduces scope of for loop in find for efficiency
* ver 1.0 : 19 Feb 2016
* - first release
*/

#include "FileManager.h"
#include "DataStore.h"
#include <iostream>

#ifdef TEST_FILEMANAGER

int main()
{
	std::cout << "\n  Testing FileMgr";
	std::cout << "\n =================";

	DataStore ds;
	FileMgr fm("..", ds);
	//fm.addPattern("*.h");
	fm.addPattern("*.cpp");
	//fm.addPattern("*.partial");
	fm.search();

	std::cout << "\n\n  contents of DataStore";
	std::cout << "\n -----------------------";
	for (auto fs : ds)
	{
		std::cout << "\n  " << fs;
	}
	std::cout << "\n\n";
	return 0;
}
#endif
