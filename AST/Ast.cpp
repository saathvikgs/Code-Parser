//////////////////////////////////////////////////////////////////////////////
// Ast.cpp - Has helper functions for tree operations                         //
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
#include <string>
#include <vector>
#include <iostream>
#include "Ast.h"
//---------<  obtains the root node of AST >-----------------
element* Ast::getRoot()
{
	return root;
}
//---------<  Walks the tree and  displays it >-----------------
void Ast::showTree(element *pItem)
{
	static size_t indentLevel = 0;
	static int funccomplexity = 1;
	std::cout << "\n  " << std::string(2 * indentLevel, ' ') << pItem->show();
	auto iter = pItem->_children.begin();
	++indentLevel;
	++funccomplexity;
	while (iter != pItem->_children.end())// till iter is not pointing to last element
	{
		showTree(*iter);
		++iter;
	}
	--indentLevel;
	//std::cout << "\n----------------------------------------------------------\n";
}

//---------< Displays complexity of each function in a given file>------------
void Ast::funct(element* node) {
	if (count == 1) {
		std::cout << std::endl << "\n\n\n\t   Cyclometric complexities of each function" << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << " scopeType\t\t " << " " << "scopeName" << " \t\t " << "numberOfLinesInScope";
		std::cout << " \t\t" << "cyclometricComplexity" << std::endl; count++;
		std::cout << std::endl << std::endl;
	}
	std::string lineDisplay;
	std::string lineDisplay2;
	//if(node->name.size>)*/
	if (node->type == "function") {//
		lineDisplay = "\t\t";
		if (node->name.size()>7 && node->name.size() <= 12)lineDisplay2 = "\t\t\t";
		else if (node->name.size() >= 13)lineDisplay2 = "\t\t";
		else lineDisplay2 = "\t\t\t\t";
		//else lineDisplay2 = "\t\t\t";
		std::cout << node->type << lineDisplay << node->name << lineDisplay2 << (node->endLineCount - node->startLineCount + 1);
		std::cout << " \t\t\t " << findComplexity(node) << std::endl;
		auto iter = node->_children.begin();
		while (iter != node->_children.end())
		{
			funct(*iter);
			++iter;
		}
	}
	else {
		auto iter = node->_children.begin();
		while (iter != node->_children.end())
		{
			funct(*iter);
			++iter;
		}
	}
}

//---------< resets the complexity function  >------------
int Ast::findComplexity(element* node)
{
	return showCycloComplex(node, 0);
}
//---------<  Sets the root node >-----------------
void Ast::setRoot(element* node)
{
	root = node;
}
//----------< Shows the function complexity >--------
int Ast::showCycloComplex(element* node, int count)
{
	complexity = count;
	++complexity;
	auto iter = node->_children.begin();
	while (iter != node->_children.end())
	{
		showCycloComplex(*iter, complexity);
		++iter;
	}
	return complexity;
}
