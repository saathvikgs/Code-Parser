#ifndef TEST_EXECUTIVE
#define TEST_EXECUTIVE
///////////////////////////////////////////////////////////////////////
// MetricsExecutive.cpp - Test package to test requirements			  //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Code Parser with Abstract Syntax Tree (AST), CSE687 - Object Oriented Design, SP16       //
//              Alienware R15, Core i5, Windows 10                           //
// Author:      Saathvik Shashidhar Gowrapura, SUID: 450734672               //
//              sgowrapu@syr.edu, (315)-751-1059                             //
// Original author: Jim Fawcett, CST 4-187, Syracuse University              // 
//              jfawcett@twcny.rr.com, (315)-443-3948                        //
//////////////////////////////////////////////////////////////////////////////

/*
Maintenance History:
====================
ver 1 : 10 Feb 16
- added a functions to test all the requirements
*/
/*
* Package Operations:
* -------------------
* This is a test executive package that shows all the requirements
*
* Build Process:
* --------------
*
* Build Command: devenv Project1.sln /rebuild debug
*
*/


#include "../Parser/Parser.h"
#include "../FileManager/FileManager.h"
#include "../Parser/ConfigureParser.h"
#include <iostream>
#include <string>
#include "../AST/Ast.h"
#include "../Parser/ActionsAndRules.h"

class TestExe {
public:
	void testRequirement1();
	void testRequirement2();
	void testRequirement3();
	void testRequirement4();
	void testRequirement5_6();
	void testRequirement7();
	void testRequirement8_9(std::string);
	void testRequirement10();
};

#endif