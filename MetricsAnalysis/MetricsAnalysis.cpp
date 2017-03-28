//////////////////////////////////////////////////////////////////////////////
// MetricsAnalysis.cpp - Support file and directory operations              //
// ver 1.0                                                                  //                                                                //
// Language:    C++, Visual Studio 2015                                     //
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
This file provides metric analysis for files that match a pattern


Required Files:
===============
Parser.h
FileMgr.h
ConfigureParser.h

Build Command:
==============
devenv ScopeStack.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 03/15/15
- first release
*/
#include <iostream>
#include <string>
#include "MetricsAnalysis.h"
#ifdef TEST_METRICSANALYSIS

void main()
{
	DataStore ds;
	FileMgr fm("../ScopeStack", ds);
	//	fm.addPattern("*.h");
	fm.addPattern("*.cpp");
	//fm.addPattern("*.partial");
	fm.search();
	std::cout << "\n\n  contents of DataStore";
	std::cout << "\n -----------------------";
	for (auto fs : ds)
	{
		std::string fileSpec = FileSystem::Path::getFullFileSpec(fs);
		std::string msg = "Processing file ->" + fileSpec;
		ConfigParseToConsole configure;
		//Ast showComplexities;
		Parser* pParser = configure.Build();
		try {
			if (pParser)
			{
				if (!configure.Attach(fs))
				{
					std::cout << "\n  could not open file " << fileSpec << std::endl;
				}
			}
			else   std::cout << "\n\n  Parser not built\n\n";

			while (pParser->next())
				pParser->parse();
			std::cout << "\n";
		}
		catch (std::exception& ex) { std::cout << "\n\n    " << ex.what() << "\n\n"; }

		configure.treeWalk();//

		std::cout << "\n\n";
	
	}
	std::cout << "\n\n";
}

#endif

//////////////////////////////////////////////////////////////////