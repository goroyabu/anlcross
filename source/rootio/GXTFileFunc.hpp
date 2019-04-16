/**
   @file GXTFileFunc.hpp
   @author Goro Yabu
   @date 2018/12/03
   @version 1.0
   @brief TFile管理用のグローバル関数
**/
#ifndef GXTFileFunc_hpp
#define GXTFileFunc_hpp

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <array>

#include <TFile.h>

namespace gxroot
{
    const int GX_OK = 0;
    const int GX_NG = -1;
    const int GX_TRUE = 1;
    const int GX_FALSE = 0;

    extern std::map<std::string, int> gTFileIndexTable;
    extern std::vector<TFile*> gTFile;
    extern std::vector<std::string> gTFileMode;
    extern std::vector<int> gTFileIsOpen; 
    extern int gCurrentTFileIndex;

    TFile * TFileOpen(std::string name, std::string mode);
    //int TFileOpen(std::string name, std::string mode);
    int TFileIndex(std::string name, int* index);
    int TFileName(int index, std::string* name);
    int TFileIsOpen(std::string name);
    int TFileClose(std::string name);
    int TFileCd(std::string name);
    //int TFileAdd(TObject * obj);
    //TFile * GetTFile(std::string name);
    TFile * CurrentTFile();
}
#endif
