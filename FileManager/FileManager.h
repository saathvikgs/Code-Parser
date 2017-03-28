#ifndef FILEMANAGER_H
#define FILEMANAGER_H
////////////////////////////////////////////////////////////////////////////////
// FileManager.h - find files matching specified patterns                   //
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
#include "FileSystem.h"
#include "DataStore.h"
#include <iostream>

class FileMgr
{
public:
	using iterator = DataStore::iterator;
	using patterns = std::vector<std::string>;
	//-------<  initializes the variables >---------------------
	FileMgr(const std::string& path, DataStore& ds) : path_(path), store_(ds)
	{
		patterns_.push_back("*.*");
	}
	//---------< adds the pattern to the vecor >----------------
	void addPattern(const std::string& patt)
	{
		if (patterns_.size() == 1 && patterns_[0] == "*.*")
			patterns_.pop_back();
		patterns_.push_back(patt);
	}
	//----------< calls find function >-------------------------
	void search()
	{
		find(path_);
	}
	//-------------< finds the files in that path >------------
	void find(const std::string& path)
	{
		std::string fpath = FileSystem::Path::getFullFileSpec(path);
		//---------------------------------------------------------
		// The statement above is not necessary, but helps to
		// make the processing clearer.  To show that, comment
		// it out and uncomment the following line.
		//
		// std::string fpath = path;
		//
		// Remove the std::cout statements below after you're 
		// convinced that everything works as it should.
		//---------------------------------------------------------

		//std::cout << "\n  ++ " << fpath;
		for (auto patt : patterns_)  // the scope of this for loop was
		{                            // changed to improve efficiency
			std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
			for (auto f : files)
			{
				std::cout << "\n  --   " << f;
				store_.save(fpath+"\\"+f);
			}
		}
		std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
		for (auto d : dirs)
		{
			if (d == "." || d == "..")
				continue;
			std::string dpath = fpath + "\\" + d;  // here's the fix
			find(dpath);
		}
	}
private:
	std::string path_;
	DataStore& store_;
	patterns patterns_;
};

#endif
