/**
   @file GXTFileFunc.cpp
   @author Goro Yabu
   @date 2018/12/04
   @version 1.0
**/
#include "GXTFileFunc.hpp"
namespace gxroot
{
    std::map<std::string, int> gTFileIndexTable;
    std::vector<TFile*> gTFile;
    std::vector<std::string> gTFileMode;
    int gCurrentTFileIndex;
}
TFile * gxroot::TFileOpen(std::string name, std::string mode)
{
    int index;
    if( TFileIndex(name, &index) == GX_OK ){
        gCurrentTFileIndex = index;
        return gTFile[index];
    }
    
    TFile * temp = new TFile(name.c_str(), mode.c_str());
    if(!temp) return nullptr;
    
    gTFile.push_back(temp);
    gTFileMode.push_back(mode);
    //gTFileIsOpen.push_back(1);
    index = gTFile.size() - 1;
    gTFileIndexTable[name] = index;
    std::cout << "TFileOpen : name = " << gTFile[gCurrentTFileIndex]->GetName() << ", mode = " << mode << std::endl;
    
    gCurrentTFileIndex = index;
    return temp;
}
/*
int gxroot::TFileOpen(std::string name, std::string mode)
{
    int index;
    if( TFileIndex(name, &index) == GX_OK ){
        gCurrentTFileIndex = index;
        std::cout << "TFile : " << name << " is already opened" << std::endl;
        return GX_OK;
    }
    if( mode == "read" || mode == "recreate"){
        TFile * temp = new TFile(name.c_str(), mode.c_str());
        if(!temp){
            std::cout << "file open failure" << std::endl;
            return GX_NG;
        }
        gTFile.push_back(temp);
        gTFileMode.push_back(mode);
        int index = gTFile.size() - 1;
        gTFileIndexTable[name] = index;
        gCurrentTFileIndex = index;
        std::cout << "TFileOpen : name = " << gTFile[gCurrentTFileIndex]->GetName() << ", mode = " << mode << std::endl;
    }
    return GX_OK;
}
*/
int gxroot::TFileIndex(const std::string name, int* index)
{
    *index = gTFileIndexTable.find(name)->second;
    if( gTFileIndexTable.find(name) ==  gTFileIndexTable.end() ) return GX_NG;
    return GX_OK;
}
int gxroot::TFileName(const int index, std::string* name)
{
    if( gTFile.size() <= index ) return GX_NG;
    *name = gTFile[index]->GetName();
    return GX_OK;
}
int gxroot::TFileIsOpen(const std::string name)
{
    int index;
    if( TFileIndex(name, &index) == GX_NG ) return GX_NG;
    if( gTFile[index]->IsOpen() == false ) return GX_NG;    
    return GX_OK;
}
int gxroot::TFileClose(std::string name)
{
    int index;
    if( TFileIndex(name, &index) == GX_NG ) return GX_NG;
    if( gTFile[index]->IsOpen() == false ) return GX_NG;    

    gTFile[index]->Close();
    std::cout << "TFileClose : name = " << name << std::endl;
    return GX_OK;
}
int gxroot::TFileCd(std::string name)
{
    int index;
    if( TFileIndex(name, &index) == GX_NG ) return GX_NG;
    if( gTFile[index]->IsOpen() == false ) return GX_NG;

    gTFile[index]->cd();
    gCurrentTFileIndex = index;
    return GX_OK;
}
TFile * gxroot::CurrentTFile()
{
    if( gTFile.size() == 0 ) return nullptr;
    return gTFile[gCurrentTFileIndex];
}
/*
int gxroot::TFileAdd(TObject * obj)
{
    gTFile[gCurrentTFileIndex]->Append(obj);
    return GX_OK;
}
TFile* gxroot::GetTFile(std::string name)
{
    int index;
    TFileIndex(name, &index);
    return gTFile[index];
}
*/










