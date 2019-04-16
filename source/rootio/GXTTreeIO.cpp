/**
   @file GXTTreeIO.cpp
   @author Goro Yabu
   @date 2018/12/04
   @version 1.0
**/
#include "GXTTreeIO.hpp"
namespace gxroot
{    
    std::map<std::string, int> gTTreeIndexTable;
    std::vector<TTree*> gTTree;
    std::vector<std::string> gTTreeMode;
    std::vector<int> gTTreeCurrentEntry;
    std::vector<int> gTFileIndexOfTTree;
    std::vector<std::string> gTFileNameOfTTree;
    std::vector<std::string> gTTreeStatus;
    std::vector<std::vector<std::string>> gTTreeOwners;
    int gCurrentTTreeIndex;

    std::map<std::string, int> gTBranchIndexTable;
    std::vector<TTreeIOBase*> gTBranchList;
    std::vector<std::string> gTBranchMode;
    
    std::map<int, TTreeReader*> gTTreeReader;
}
/**
   @brief TTreeを作る関数
   @param name
   @param mode "read"でカレントファイル内のTTreeを開く. "write"でカレントファイル内に新規のTTreeを作る.
**/
TTree * gxroot::TTreeDef(std::string name, std::string mode, std::string owner)
{
    int index;
    if( TTreeIndex(name, &index) == GX_OK ){
	gCurrentTTreeIndex = index;
	gTTreeOwners[index].push_back(owner);
	return gTTree[index];
    }

    //std::cout << name << "," << mode << "," << owner << "," << CurrentTFile()->GetName() << std::endl;
    std::string fname;
    if( mode == "read" ){
	TTree * temp = (TTree*)( CurrentTFile()->Get( name.c_str() ) );
	if(!temp) return nullptr;
	
	gTTree.push_back(temp);
	gTTreeMode.push_back("read");
	gTTreeCurrentEntry.push_back(0);
	index = gTTree.size() - 1;
	gTTreeIndexTable[name] = index;
	gCurrentTTreeIndex = index;

	TFileName(gCurrentTFileIndex, &fname);
	gTFileIndexOfTTree.push_back(gCurrentTFileIndex);
	gTFileNameOfTTree.push_back(fname);
	gTTreeStatus.push_back("open");
	std::vector<std::string> vectemp;
	vectemp.push_back(owner);
	gTTreeOwners.push_back(vectemp);
	
	std::cout << "TTreeDef  : name     = " << gTTree[index]->GetName() << std::endl;
	std::cout << "          : mode     = read" << std::endl;
	std::cout << "          : in TFile = " << gTFile[gCurrentTFileIndex]->GetName() << std::endl;

	//if( mode == "read" ) gTTreeReader[index] = new TTreeReader(name.c_str(), gTFile[gCurrentTTreeIndex]);
	return temp;
    }
    if( mode == "write" ){
	TTree * temp = new TTree( name.c_str(), name.c_str() );
	if(!temp) return nullptr;

	gTTree.push_back(temp);
	gTTreeMode.push_back("write");
	gTTreeCurrentEntry.push_back(0);
	index = gTTree.size() - 1;
	gTTreeIndexTable[name] = index;
	gCurrentTTreeIndex = index;

	TFileName(gCurrentTFileIndex, &fname);
	gTFileIndexOfTTree.push_back(gCurrentTFileIndex);
	gTFileNameOfTTree.push_back(fname);
	gTTreeStatus.push_back("open");
	std::vector<std::string> vectemp;
	vectemp.push_back(owner);
	gTTreeOwners.push_back(vectemp);

	std::cout << "TTreeDef  : name     = " << gTTree[index]->GetName() << std::endl;
	std::cout << "          : mode     = write" << std::endl;
	std::cout << "          : in TFile = " << gTFile[gCurrentTFileIndex]->GetName() << std::endl;

	return temp;
    }
    
    return nullptr;
}
/*
int gxroot::TTreeDef(std::string name, std::string mode)
{
    if( TTreeIsDef(name) == GX_OK ) return GX_NG;
    if( mode != "read" && mode != "write" && mode != "clone") return GX_NG;

    TTree* temp = (TTree*)gDirectory->Get( name.c_str() );
    if(!temp){
	temp = new TTree( name.c_str(), name.c_str() );
    }

    gTTree.push_back(temp);
    gTTreeMode.push_back(mode);
    gTTreeCurrentEntry.push_back(0);
    int index = gTTree.size() - 1;
    gTTreeIndexTable[name] = index;
    gCurrentTTreeIndex = index;
    gTFileIndexOfTTree.push_back(gCurrentTFileIndex);

    if( mode == "read" ) gTTreeReader[index] = new TTreeReader(name.c_str(), gTFile[gCurrentTTreeIndex]);
    
    std::cout << "TTreeDef : name = " << gTTree[index]->GetName() << std::endl;
    std::cout << "     in TFile : name = " << gTFile[gCurrentTFileIndex]->GetName() << std::endl;
    
    return GX_OK;
}
*/
int gxroot::TTreeIndex(const std::string name, int* index)
{
    *index = gTTreeIndexTable.find(name)->second;
    if( gTTreeIndexTable.find(name) ==  gTTreeIndexTable.end() ) return GX_NG;
    return GX_OK;
}
int gxroot::TTreeIsDef(const std::string name)
{
    if( gTTreeIndexTable.find(name) ==  gTTreeIndexTable.end() ) return GX_NG;
    return GX_OK;
}
/*
int gxroot::Ntree()
{
    return (int)gTTree.size();
}
*/
int gxroot::TTreeBegin(std::string name)
{
    int index;
    if( TTreeIndex(name, &index) == GX_NG ) return GX_NG;
    gTTree[index]->GetEntry(0);
    gTTreeCurrentEntry[index] = 0;
    return GX_OK;
}
int gxroot::TTreeNext(std::string name)
{
    int index;
    if( TTreeIndex(name, &index) == GX_NG ) return GX_NG;
    if( gTTree[index]->GetEntries() <= gTTreeCurrentEntry[index] ) return GX_NG;
    gTTree[index]->GetEntry(gTTreeCurrentEntry[index]);
    gTTreeCurrentEntry[index]++;
    return GX_OK;
}
int gxroot::TTreeFill(std::string name)
{
    int index;
    if( TTreeIndex(name, &index) == GX_NG ) return GX_NG;
    gCurrentTTreeIndex = index;
    gTTree[index]->Fill();
    gTTreeCurrentEntry[index]++;
    return GX_OK;
}
int gxroot::TTreeWrite(std::string name)
{
    int index;
    if( TTreeIndex(name, &index) == GX_NG ) return GX_NG;
    if( gTTreeStatus[index] == "close" ) return GX_NG;
    if( TFileIsOpen( gTFileNameOfTTree[index] ) == GX_NG ){
	gTTreeStatus[index] = "close";
	std::cout << "TFile " << name << " is already closed" << std::endl;
	return GX_NG;
    }
    TFileCd( gTFileNameOfTTree[index] );
    gTTree[index]->Write();
    gTTreeStatus[index] = "close";
    
    std::cout << "TTreeWrite : name     = " << name << std::endl;
    std::cout << "           : in TFile = " << gTFile[ gTFileIndexOfTTree[index] ]->GetName() << std::endl;
    return GX_OK;
}
int gxroot::TTreeFirstOwn(std::string name, std::string owner)
{
    int index;
    if( TTreeIndex(name, &index) == GX_NG ) return GX_NG;
    if( gTTreeOwners[index][0] != owner ) return GX_NG;
    return GX_OK;
}
int gxroot::TTreeLastOwn(std::string name, std::string owner)
{
    int index;
    if( TTreeIndex(name, &index) == GX_NG ) return GX_NG;
    if( gTTreeOwners[index][ gTTreeOwners[index].size()-1 ] != owner ) return GX_NG;
    return GX_OK;
}
    
/*
TTree* gxroot::GetTTree(std::string name)
{
    int index;
    TTreeIndex(name, &index);
    return gTTree[index];
}
TTree* gxroot::TTreeGet(std::string name)
{
    int index;
    if( TTreeIndex(name, &index) == GX_NG ){
	TTreeDef(name, "read");
	TTreeIndex(name, &index);
    }
    return gTTree[index];
}
*/
int gxroot::FindBranch(std::string key, int* index)
{
    *index = gTBranchIndexTable.find(key)->second;
    if( gTBranchIndexTable.find(key) == gTBranchIndexTable.end() ) return GX_NG;
    return GX_OK;
}
/*
int gxroot::DefBranch(std::string key, std::string type, int maxsize, std::string keyofsize, bool save)
{
    int index;
    if( FindBranch(key, &index) == GX_NG ) return MakeBranch(key, type, maxsize, keyofsize, save);
    return ReadBranch(key, type, maxsize, keyofsize, save);
}
*/

/**
   @brief カレントツリーに新しくBranchを作成する関数. 
   @param key
   @param type int = "I", float = "F"
   @param maxsize 配列の最大サイズ. if maxsize = 1, branch is not an array.
   @param keyofsize 可変長配列の場合に参照するBranchのkey. if keyofsize = "", array は固定長.
**/
int gxroot::MakeBranch(std::string key, std::string type, int maxsize, std::string keyofsize, bool save)
{
    int index;
    if( FindBranch(key, &index) == GX_OK ){
	if( gTBranchMode[index] != "write" ) return GX_NG;
	return GX_OK;
    }
    if( maxsize == 1) MakeBranchValue(key, type, save);
    else MakeBranchArray(key, type, maxsize, keyofsize, save);

    return GX_OK;
}
/**
   @brief カレントツリーから新たに読み出すBranchを設定する関数.
   @param key
   @param type int = "I", float = "F"
   @param maxsize 配列の最大サイズ. if maxsize = 1, branch is not an array.
   @param keyofsize 可変長配列の場合に参照するBranchのkey. if keyofsize = "", array は固定長.
**/
int gxroot::ReadBranch(std::string key, std::string type, int maxsize, std::string keyofsize, bool save)
{
    int index;
    if( FindBranch(key, &index) == GX_OK ){
	if( gTBranchMode[index] != "read" ) return GX_NG;
	return GX_OK;
    }
    if( maxsize == 1) ReadBranchValue(key, type);
    else ReadBranchArray(key, type, maxsize, keyofsize);

    return GX_OK;
}

/** 
   @brief 普通のBranchを作成する
   @param key Name of TBranch
   @param type Type of variable e.g. int = "I"
   @param save falseならbufferのみ定義し、出力ツリーに書き込まない
   @return GX_NG if TBranch "key" is already defined with different params ( type, maxsize, ... ).
**/
int gxroot::MakeBranchValue(std::string key, std::string type, bool save)
{
    int index;
    if( FindBranch(key, &index) == GX_OK ){
	if( gTBranchMode[index] != "write" ) return GX_NG;
	return GX_OK;
    }
    if( type == "I" || type == "int" ){
	gTBranchList.push_back( new TTreeWriteValue<int>(key, save) );
    }else if( type == "s" ){
	gTBranchList.push_back( new TTreeWriteValue<unsigned short>(key, save) );
    }else if( type == "i" ){
	gTBranchList.push_back( new TTreeWriteValue<unsigned int>(key, save) );
    }else if( type == "F" ){
	gTBranchList.push_back( new TTreeWriteValue<float>(key, save) );
    }
    gTBranchIndexTable[key] = gTBranchList.size() - 1;
    gTBranchMode.push_back( "write" );

    std::cout << "DefBranch : key      = " << key << std::endl;
    std::cout << "          : size     = 1" << std::endl;
    std::cout << "          : mode     = write" << std::endl;
    std::cout << "          : in TTree = " << gTTree[gCurrentTTreeIndex]->GetName() << std::endl;
    std::cout << "********************************************" << std::endl;

    return GX_OK;
}
/**
   @brief 配列のBranchを作成する
   @param key Name of TBranch
   @param type Type of variable e.g. int = "I"
   @param save falseならbufferのみ定義し、出力ツリーに書き込まない
   @return GX_NG if TBranch "key" is already defined with different params ( type, maxsize, ... ).
**/
int gxroot::MakeBranchArray(std::string key, std::string type, int maxsize, std::string keyofsize, bool save)
{
    int index;
    if( FindBranch(key, &index) == GX_OK ){
	if( gTBranchMode[index] != "write" ) return GX_NG;
	return GX_OK;
    }
    if( type == "I" || type == "int" ){
	gTBranchList.push_back( new TTreeWriteArray<int>(key, maxsize, keyofsize, save) );
    }else if( type == "s" ){
	gTBranchList.push_back( new TTreeWriteArray<unsigned short>(key, maxsize, keyofsize, save) );
    }else if( type == "i" ){
	gTBranchList.push_back( new TTreeWriteArray<unsigned int>(key, maxsize, keyofsize, save) );
    }else if( type == "F" ){
	gTBranchList.push_back( new TTreeWriteArray<float>(key, maxsize, keyofsize, save) );
    }
    gTBranchIndexTable[key] = gTBranchList.size() - 1;
    gTBranchMode.push_back( "write" );
    
    std::cout << "DefBranch : key      = " << key << std::endl;
    std::cout << "          : size     = " << maxsize << std::endl;
    std::cout << "          : mode     = write" << std::endl;
    std::cout << "          : in TTree = " << gTTree[gCurrentTTreeIndex]->GetName() << std::endl;
    std::cout << "********************************************" << std::endl;

    return GX_OK;
}
/**
   @brief 普通のBranchを読み出す
   @param key Name of TBranch
   @param type Type of variable e.g. int = "I"
   @return GX_NG if TBranch "key" is not found or already defined by MakeBranchValue.
**/
int gxroot::ReadBranchValue(std::string key, std::string type)
{
    int index;
    if( FindBranch(key, &index) == GX_OK ){
	if( gTBranchMode[index] != "read" ) return GX_NG;
	return GX_OK;
    }
    if( type == "I" || type == "int" ){
	gTBranchList.push_back( new TTreeReadValue<int>(key) );
    }else if( type == "s" ){
	gTBranchList.push_back( new TTreeReadValue<unsigned short>(key) );
    }else if( type == "i" ){
	gTBranchList.push_back( new TTreeReadValue<unsigned int>(key) );
    }else if( type == "F" ){
	gTBranchList.push_back( new TTreeReadValue<float>(key) );
    }
    gTBranchIndexTable[key] = gTBranchList.size() - 1;
    gTBranchMode.push_back( "read" );
    
    std::cout << "DefBranch : key      = " << key << std::endl;
    std::cout << "          : size     = 1" << std::endl;
    std::cout << "          : mode     = read" << std::endl;
    std::cout << "          : in TTree = " << gTTree[gCurrentTTreeIndex]->GetName() << std::endl;
    std::cout << "********************************************" << std::endl;

    return GX_OK;
}
/**
   @brief 配列のBranchを読み出す
   @param key Name of TBranch
   @param type Type of variable e.g. int = "I"
   @return GX_NG if TBranch "key" is not found or already defined by MakeBranchArray or different params.
**/
int gxroot::ReadBranchArray(std::string key, std::string type, int maxsize, std::string keyofsize)
{
    int index;
    if( FindBranch(key, &index) == GX_OK ){
	if( gTBranchMode[index] != "read" ) return GX_NG;
	return GX_OK;
    }
    if( type == "I" || type == "int" ){
	gTBranchList.push_back( new TTreeReadArray<int>(key, maxsize, keyofsize) );
    }else if( type == "s" ){
	gTBranchList.push_back( new TTreeReadArray<unsigned short>(key, maxsize, keyofsize) );
    }else if( type == "i" ){
	gTBranchList.push_back( new TTreeReadArray<unsigned int>(key, maxsize, keyofsize) );
    }else if( type == "F" ){
	gTBranchList.push_back( new TTreeReadArray<float>(key, maxsize, keyofsize) );
    }
    gTBranchIndexTable[key] = gTBranchList.size() - 1;
    gTBranchMode.push_back( "read" );
    
    std::cout << "DefBranch : key      = " << key << std::endl;
    std::cout << "          : size     = " << maxsize << std::endl;
    std::cout << "          : mode     = read" << std::endl;
    std::cout << "          : in TTree = " << gTTree[gCurrentTTreeIndex]->GetName() << std::endl;
    std::cout << "********************************************" << std::endl;

    return GX_OK;
}
/**
   @brief 普通のBranchをコピーする
   @param key
   @param type
   @param intree コピー元のツリーの名前
   @param outtree コピー先のツリーの名前
   @detail Put関数は使用できない.
   @return GX_NG for ツリーがnot found, Branchがnot found
**/
int gxroot::CloneBranchValue(std::string key, std::string type, std::string intree, std::string outtree)
{
    int index;
    if( FindBranch(key, &index) == GX_OK ){
	if( gTBranchMode[index] != "clone" ) return GX_NG;
	return GX_OK;
    }
    if( type == "I" || type == "int" ){
	gTBranchList.push_back( new TTreeCloneValue<int>(key, intree, outtree) );
    }else if( type == "s" ){
	gTBranchList.push_back( new TTreeCloneValue<unsigned short>(key, intree, outtree) );
    }else if( type == "i" ){
	gTBranchList.push_back( new TTreeCloneValue<unsigned int>(key, intree, outtree) );
    }else if( type == "F" ){
	gTBranchList.push_back( new TTreeCloneValue<float>(key, intree, outtree) );
    }
    gTBranchIndexTable[key] = gTBranchList.size() - 1;
    gTBranchMode.push_back( "clone" );
    
    std::cout << "DefBranch : key      = " << key << std::endl;
    std::cout << "          : size     = 1" << std::endl;
    std::cout << "          : mode     = clone" << std::endl;
    std::cout << "          : in TTree = " << gTTree[gCurrentTTreeIndex]->GetName() << std::endl;
    std::cout << "********************************************" << std::endl;

    return GX_OK;
}
template<> std::string gxroot::GetTypeChar<int>(int* ptr)
{
    return "I";
}
template<> std::string gxroot::GetTypeChar<unsigned int>(unsigned int* ptr)
{
    return "i";
}
template<> std::string gxroot::GetTypeChar<unsigned short>(unsigned short* ptr)
{
    return "s";
}
template<> std::string gxroot::GetTypeChar<short>(short* ptr)
{
    return "S";
}
template<> std::string gxroot::GetTypeChar<float>(float* ptr)
{
    return "F";
}
template<> std::string gxroot::GetTypeChar<double>(double* ptr)
{
    return "D";
}





























