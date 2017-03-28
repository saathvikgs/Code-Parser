//////////////////////////////////////////////////////////////////////////////
// StructElement.h -defines a struct element that can be used wherever needed     //
// ver 1.0                                                                  //                                                                //
// Language:    C++, Visual Studio 2015                                      //
// Application: Code Parser with Abstract Syntax Tree (AST), CSE687 - Object Oriented Design, SP16       //
//              Alienware R15, Core i5, Windows 10                           //
// Author:      Saathvik Shashidhar Gowrapura, SUID: 450734672               //
//              sgowrapu@syr.edu, (315)-751-1059                             //
// Original author: Jim Fawcett, CST 4-187, Syracuse University              // 
//              jfawcett@twcny.rr.com, (315)-443-3948                        //
//////////////////////////////////////////////////////////////////////////////
/*Package Operations :
== == == == == == == == == =
This file defines a struct element that can be used wherever needed

Public Interface :
== == == == == == == == =
void show() - // displays output in the format (name,type,startline,endline)
*/

#ifndef STRUCTELEMENT_H
#define STRUCTELEMENT_H
#include<vector>
#include<string>
#include<iostream>
#include<sstream>
struct element
{
	std::string type;
	std::string name;
	size_t startLineCount = 0;
	size_t endLineCount = 0;
	std::string show()
	{
		std::ostringstream temp;
		temp << "(";
		temp << type;
		temp << ", ";
		temp << name;
		temp << ", ";
		temp << startLineCount;
		temp << ", ";
		temp << endLineCount;
		temp << ")";
		return temp.str();                  // converts the format above to a string object to be displayed
	}
	std::vector<element*> _children;       //children is a vector of element pointers
};
#endif