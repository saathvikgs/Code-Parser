#ifndef AST_H
#define AST_H
//////////////////////////////////////////////////////////////////////////////
// Ast.h - Has helper functions for tree operations                         //
// ver 1.1                                                                  //
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
This package contains one class:AST.
It provides a facility for building an abstract syntax tree that provides an interface
for adding scope nodes to the tree and an methods to analyze the contents of the tree.

Public Interface:
=================
void showTree(element*)-Walks the tree and  displays it
int findComplexity(element*)- resets the complexity function
int showCycloComplex(element*,int)- Shows the function complexity
element* getRoot() - gets the rootnode
void setRootNode(element* node) - sets the root node
void funct(element*)-Displays details of each function
Required Files:
===============
StructElement.h

Build Command:
==============
devenv ScopeStack.sln /rebuild debug

Maintenance History:
====================
ver 1.1 : 03/16/15
- added methods to find complexity
ver 1.0 : 03/13/15
- first release
*/
#include<string>
#include<list>
#include "../StructElement/StructElement.h"

class Ast
{
public:
	element* root;
	void showTree(element*);
	int findComplexity(element*);
	int showCycloComplex(element*, int);
	element* getRoot();
	void setRoot(element* node);
	void funct(element* node);
	//int getComplexity(element*);
private:
	 int complexity;
	 int count = 1;
	std::list<element*> _tree;
};




#endif
