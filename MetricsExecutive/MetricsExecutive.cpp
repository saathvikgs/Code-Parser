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

#include <iostream>
#include <string>
#include "MetricsExecutive.h"
#ifdef TEST_METRICSEXECUTIVE
void TestExe::testRequirement1()      //to display requirement 1
{
	std::cout << "\n ===============================================================================\n";
	std::cout << "\n Demonstrating requirement 1\n";
	std::cout << " I have used Visual Studio 2015 and its C++ Windows Console Projects for this project\n";
}

void TestExe::testRequirement2()      //to display requirement 2
{
	std::cout << "\n ===============================================================================\n";
	std::cout << "\n Demonstrating requirement 2\n";
	std::cout << " I have used the C++ standard library's streams for all I/O and new and delete for all heap-based memory management for this project\n";
}

void TestExe::testRequirement3()		 //to display requirement 3
{
	std::cout << "\n ===============================================================================\n";
	std::cout << "\n Demonstrating requirement 3\n";
	std::cout << " I have provided C++ packages for analyzing function size and complexity metrics for a set of specified packages. These packages will use the Tokenizer and SemiExpression packages.\n";
}

void TestExe::testRequirement4()		 //to display requirement 4
{
	std::cout << "\n ===============================================================================\n";
	std::cout << "\n Demonstrating requirement 4\n";
	std::cout << " I have provided provide a Parser package with a Parser class that is a container for Rules and that provides the interfaces IRule and IAction for rules contained in the Parser and actions contained in each rule.\n";
}
void TestExe::testRequirement5_6()		 //to display requirement 5 and 6
{
	std::cout << "\n ===============================================================================\n";
	std::cout << "\n Demonstrating requirement 5 and 6\n";
	std::cout << "\n I am demonstrating requirement 5 and 6 in a single demonstration.\n";
	std::string fileSpec = FileSystem::Path::getFullFileSpec("../Testfile/test.txt");
	std::string msg = "Processing file" + fileSpec;
	std::cout << "\n " << msg << "\n";
	//Util::title(msg);
	//putline();

	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	try
	{
		if (pParser)
		{
			if (!configure.Attach("../Testfile/test.txt"))
			{
				std::cout << "\n  could not open file " << fileSpec << std::endl;
				//continue;
			}
		}
		else
		{
			std::cout << "\n\n  Parser not built\n\n";
			//return 1;
		}
		// now that parser is built, use it

		while (pParser->next())
			pParser->parse();
		std::cout << "\n";
		configure.treeWalk();
		configure.showComtable();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
}

void TestExe::testRequirement7()					 //to display requirement 7
{
	std::cout << "\n ===============================================================================\n";
	std::cout << "\n Demonstrating requirement 7\n";
	std::cout << "\n\n I have provided a FileMgr package that supports finding files and/or directories "
		<< " in a directory tree rooted at a specified path \n";
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
	//return 0;
	//std::cout << "I have provided provide a Parser package with a Parser class that is a container for Rules and that provides the interfaces IRule and IAction for rules contained in the Parser and actions contained in each rule.\n";
}

void TestExe::testRequirement8_9(std::string filename)			 //to display requirement 8 9 
{
	std::cout << "\n ===============================================================================\n";
	std::cout << "\n Demonstrating requirement 8, 9\n";
	DataStore ds;
	FileMgr fm(filename, ds);
	//fm.addPattern("*.h");
	fm.addPattern("*.cpp");
	//fm.addPattern("*.partial");
	fm.search();
	std::cout << "\n\n The directory is " << filename;
	std::cout << "\n\n  contents of DataStore";
	std::cout << "\n -----------------------";
	for (auto fs : ds)
	{
		//std::string fileSpec = FileSystem::Path::getFullFileSpec(fs);
		std::string fileSpec = fs;
		std::string msg = "Processing file ->" + fileSpec;
		std::cout << "\n\n --" << msg << "\n\n";
		ConfigParseToConsole configure;
		//Ast showComplexities;
		Parser* pParser = configure.Build2();
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

		//configure.treeWalk();//
		configure.showComtable();
		std::cout << "\n\n";

	}
	std::cout << "\n\n";


}

void TestExe::testRequirement10()					//to display requirement 10
{
	std::cout << "\n ===============================================================================\n";
	std::cout << "\n Demonstrating requirement 10\n";
	std::cout << " This package contains an automated unit test suite which is the metrics executive package that\n"
		<< " enables collecting metrics for all the packages containing  files that match\n"
		<< " a specified pattern in a directory tree rooted at a specified path and\n"
		<< " exercises all of the packages provided in your submission and \n"
		<< " demonstrates that you met all requirements\n\n\n\n";
}
int  main(int argc, char* argv[])
{
	//std::cout << "\n  Testing FileMgr";
	TestExe test;
	test.testRequirement1();
	test.testRequirement2();
	test.testRequirement3();
	test.testRequirement4();
	test.testRequirement5_6();
	test.testRequirement7();

	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}
	for (int i = 1; i < argc; ++i)
	{
		std::string fileSpec = FileSystem::Path::getFullFileSpec(argv[i]);
		test.testRequirement8_9(fileSpec);
	}

	test.testRequirement10();
	
	return 1;
}

#endif

//////////////////////////////////////////////////////////////////