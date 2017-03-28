///////////////////////////////////////////////////////////////////////////////
//  ConfigureParser.cpp - builds and configures parsers                        //
//  ver 2.2                                                                  //
//                                                                           //
// Language:    C++, Visual Studio 2015                                      //
// Application: Code Parser with Abstract Syntax Tree (AST), CSE687 - Object Oriented Design, SP16       //
//              Alienware R15, Core i5, Windows 10                           //
// Author:      Saathvik Shashidhar Gowrapura, SUID: 450734672               //
//              sgowrapu@syr.edu, (315)-751-1059                             //
// Original author: Jim Fawcett, CST 4-187, Syracuse University              // 
//              jfawcett@twcny.rr.com, (315)-443-3948                        //
//////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module builds and configures parsers.  It builds the parser
parts and configures them with application specific rules and actions.

Public Interface:
=================
ConfigParseToConsole conConfig;
conConfig.Build();- all the parts get assembled
conConfig.Attach(someFileName); - attach toker to a file stream or stringstream
treeWalk - calls the display tree function

Build Process:
==============
Required files
- ConfigureParser.h, ConfigureParser.cpp, Parser.h, Parser.cpp,
ActionsAndRules.h, ActionsAndRules.cpp,
SemiExpression.h, SemiExpression.cpp, tokenizer.h, tokenizer.cpp
Build commands (either one)
- devenv Project1HelpS06.sln
- cl /EHsc /DTEST_PARSER ConfigureParser.cpp parser.cpp \
ActionsAndRules.cpp \
semiexpression.cpp tokenizer.cpp /link setargv.obj

Maintenance History:
====================
ver 2.2 : 14 Mar 16
- Added treeWalk function and showComptable
ver 2.1 : 19 Feb 16
- Added PrintFunction action to FunctionDefinition rule
ver 2.0 : 01 Jun 11
- Major revisions to begin building a strong code analyzer
ver 1.1 : 01 Feb 06
- cosmetic changes to ConfigureParser.cpp
ver 1.0 : 12 Jan 06
- first release

*/

#include <fstream>
#include "Parser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "ActionsAndRules.h"
#include "ConfigureParser.h"

using namespace Scanner;

//----< destructor releases all parts >------------------------------

ConfigParseToConsole::~ConfigParseToConsole()
{
  // when Builder goes out of scope, everything must be deallocated

  delete pHandlePush;
  delete pBeginningOfScope;
  delete pHandlePop;
  delete pEndOfScope;
  delete pPrintFunction;
  delete pPushFunction;
  delete pFunctionDefinition;
  delete pDeclaration;
  delete pShowDeclaration;
  delete pExecutable;
  delete pShowExecutable;
  delete pRepo;
  delete pParser;
  delete pSemi;
  delete pToker;
  pIn->close();
  delete pIn;
}
//----< attach toker to a file stream or stringstream >------------

bool ConfigParseToConsole::Attach(const std::string& name, bool isFile)
{
  if(pToker == 0)
    return false;
  pIn = new std::ifstream(name);
  if (!pIn->good())
    return false;
  return pToker->attach(pIn);
}
//----< Here's where alll the parts get assembled >----------------

Parser* ConfigParseToConsole::Build()
{
  try
  {// add Parser's main parts
pToker = new Toker; pToker->returnComments(false); pSemi = new SemiExp(pToker);
    pParser = new Parser(pSemi); pRepo = new Repository(pToker);
	pRepo->addRoot();
    // configure to manage scope
    // these must come first - they return true on match
    // so rule checking continues
    pBeginningOfScope = new BeginningOfScope(); pHandlePush = new HandlePush(pRepo);
    pBeginningOfScope->addAction(pHandlePush); pParser->addRule(pBeginningOfScope);
    pEndOfScope = new EndOfScope(); pHandlePop = new HandlePop(pRepo);  pEndOfScope->addAction(pHandlePop);
    pParser->addRule(pEndOfScope);
    // configure to detect and act on function definitions these will stop further rule checking by returning false
 pFunctionDefinition = new FunctionDefinition; pPushFunction = new PushFunction(pRepo);  // no action
    pPrintFunction = new PrintFunction(pRepo); pFunctionDefinition->addAction(pPushFunction);
    pFunctionDefinition->addAction(pPrintFunction);    pParser->addRule(pFunctionDefinition);
// Configure to detect and act on for loop
	pLoop = new Loop;
	ppushLoop = new pushLoop(pRepo);	pPrintLoop = new PrintLoop(pRepo);
	pLoop->addAction(ppushLoop);	pLoop->addAction(pPrintLoop);	pParser->addRule(pLoop);
	//Configure to detect class or structure
	pClassStruct = new ClassStruct;	ppushClassStruct = new pushClassStruct(pRepo);
	pshowClassStruct = new showClassStruct(pRepo);	pClassStruct->addAction(ppushClassStruct);	pClassStruct->addAction(pshowClassStruct);
	pParser->addRule(pClassStruct);
	//Configure to detect and act on Preprocessor
	pPreprocStatement = new PreprocStatement;	pPrintPreproc = new PrintPreproc;	pPreprocStatement->addAction(pPrintPreproc);
	pParser->addRule(pPreprocStatement);
	// configure to handle  lambdas
	pLambda = new lambda;	pPushLambda = new PushLambda(pRepo);
	pShowLambda = new showLambda(pRepo);	pLambda->addAction(pPushLambda);
	pLambda->addAction(pShowLambda);	pParser->addRule(pLambda);
    // configure to detect and act on declarations and Executables
    pDeclaration = new Declaration;
    pShowDeclaration = new ShowDeclaration;
    pDeclaration->addAction(pShowDeclaration);
    pParser->addRule(pDeclaration);
    pExecutable = new Executable;
    pShowExecutable = new ShowExecutable;
    pExecutable->addAction(pShowExecutable);
    pParser->addRule(pExecutable);
    return pParser;
  }
  catch(std::exception& ex)
  {
    std::cout << "\n\n  " << ex.what() << "\n\n";
    return 0;
  }
}

Parser* ConfigParseToConsole::Build2()
{
	try
	{// add Parser's main parts
	    pToker = new Toker;		pToker->returnComments(false);
		pSemi = new SemiExp(pToker);		pParser = new Parser(pSemi);
		pRepo = new Repository(pToker);		pRepo->addRoot();
        // configure to manage scope, these must come first - they return true on match so rule checking continues
     	pBeginningOfScope = new BeginningOfScope();		pHandlePush = new HandlePush(pRepo);
		pBeginningOfScope->addAction(pHandlePush);		pParser->addRule(pBeginningOfScope);
		pEndOfScope = new EndOfScope();		pHandlePop = new HandlePop(pRepo);
		pEndOfScope->addAction(pHandlePop);		pParser->addRule(pEndOfScope);
		// configure to detect and act on function definitions these will stop further rule checking by returning false
		pFunctionDefinition = new FunctionDefinition;		pPushFunction = new PushFunction(pRepo);  // no action
		pFunctionDefinition->addAction(pPushFunction);
		pParser->addRule(pFunctionDefinition);
		// Configure to detect and act on for loop
		pLoop = new Loop;		ppushLoop = new pushLoop(pRepo);
		pLoop->addAction(ppushLoop);		pParser->addRule(pLoop);
		//Configure to detect class or structure
		pClassStruct = new ClassStruct;		ppushClassStruct = new pushClassStruct(pRepo);
		pClassStruct->addAction(ppushClassStruct);
		pParser->addRule(pClassStruct);
		pPreprocStatement = new PreprocStatement;
		pParser->addRule(pPreprocStatement);
		// configure to handle  lambdas
		pLambda = new lambda;
		pPushLambda = new PushLambda(pRepo);
		pLambda->addAction(pPushLambda);		//pLambda->addAction(pShowLambda);
		pParser->addRule(pLambda);
		// configure to detect and act on declarations and Executables
		pDeclaration = new Declaration;
		//pShowDeclaration = new ShowDeclaration;
		//pDeclaration->addAction(pShowDeclaration);
		pParser->addRule(pDeclaration);
		pExecutable = new Executable;
		//pShowExecutable = new ShowExecutable;
		//pExecutable->addAction(pShowExecutable);
		pParser->addRule(pExecutable);

		return pParser;
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n  " << ex.what() << "\n\n";
		return 0;
	}
}

void ConfigParseToConsole::treeWalk()                       //walks the tree and displays through rootnode 
{
	pRepo->astRoot->showTree(pRepo->astRoot->getRoot());
    pRepo->astRoot->findComplexity(pRepo->astRoot->getRoot());
	std::cout << "\nComplexity is = "<< pRepo->astRoot->findComplexity(pRepo->astRoot->getRoot()) << std::endl;

	//pRepo->astRoot->funct(pRepo->astRoot->getRoot());
}

void ConfigParseToConsole::showComtable()					// to display the complexity table for each function in the given file
{
	pRepo->astRoot->funct(pRepo->astRoot->getRoot());
}

#ifdef TEST_CONFIGUREPARSER

#include <queue>
#include <string>

int main(int argc, char* argv[])
{
  std::cout << "\n  Testing ConfigureParser module\n "
            << std::string(32,'=') << std::endl;

  // collecting tokens from files, named on the command line

  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::cout << "\n  Processing file " << argv[i];
    std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-');

    ConfigParseToConsole configure;
    Parser* pParser = configure.Build();
    try
    {
      if(pParser)
      {
        if(!configure.Attach(argv[i]))
        {
          std::cout << "\n  could not open file " << argv[i] << std::endl;
          continue;
        }
      }
      else
      {
        std::cout << "\n\n  Parser not built\n\n";
        return 1;
      }
      // now that parser is built, use it

      while(pParser->next())
        pParser->parse();
      std::cout << "\n\n";
    }
    catch(std::exception& ex)
    {
      std::cout << "\n\n    " << ex.what() << "\n\n";
    }
    std::cout << "\n\n";
  }
}

#endif
