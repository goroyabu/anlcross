/**
   @file GXTTreeIO.hpp
   @author Goro Yabu
   @date 2018/11/29
   @version 1.0
   @brief TTree読み書き用の、BNKとは独立したグローバルなしくみ
**/
#ifndef GXTTreeIO_hpp
#define GXTTreeIO_hpp

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <array>

#include <TFile.h>
#include <TTree.h>
#include <TObject.h>
#include <TBranch.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include "GXTFileFunc.hpp"

namespace gxroot
{
    class TTreeIOBase;
    
    extern std::map<std::string, int> gTTreeIndexTable;
    extern std::vector<TTree*> gTTree;
    extern std::vector<std::string> gTTreeMode;
    extern std::vector<int> gTTreeCurrentEntry;
    extern std::vector<int> gTFileIndexOfTTree;
    extern std::vector<std::string> gTFileNameOfTTree;
    extern std::vector<std::string> gTTreeStatus;
    extern std::vector<std::vector<std::string>> gTTreeOwners;
    extern int gCurrentTTreeIndex;

    extern std::map<std::string, int> gTBranchIndexTable;
    extern std::vector<TTreeIOBase*> gTBranchList;
    extern std::vector<std::string> gTBranchMode;
    
    extern std::map<int, TTreeReader*> gTTreeReader;
    
    /** User Method 1 for TFile **/
    TTree * TTreeDef(std::string name, std::string mode, std::string owner);    
    //int TTreeDef(std::string name, std::string mode);
    int TTreeIndex(std::string name, int* index);
    int TTreeIsDef(std::string name);
    //int Ntree();
    int TTreeBegin(std::string name);
    int TTreeNext(std::string name);
    int TTreeFill(std::string name);
    int TTreeWrite(std::string name);
    int TTreeFirstOwn(std::string name, std::string owner);
    int TTreeLastOwn(std::string name, std::string owner);

    /* User Method 2 for TBranch */
    int FindBranch(std::string key, int* index);
    //int DefBranch(std::string key, std::string type, int maxsize = 1, std::string keyofsize = "", bool save = true);
    
    int MakeBranch(std::string key, std::string type, int maxsize = 1, std::string keyofsize = "", bool save = true);
    int MakeBranchValue(std::string key, std::string type, bool save = true);
    int MakeBranchArray(std::string key, std::string type, int maxsize = 1, std::string keyofsize="", bool save = true);
    
    int ReadBranch(std::string key, std::string type, int maxsize = 1, std::string keyofsize = "", bool save = true);
    int ReadBranchValue(std::string key, std::string type);
    int ReadBranchArray(std::string key, std::string type, int maxsize = 1, std::string keyofsize="");
    
    int CloneBranchValue(std::string key, std::string type, std::string intree, std::string outtree);
    /* User Method END */

    
    template<typename T>
    std::string GetTypeChar(T* ptr);
    template<typename T>
    std::string BranchTitle(std::string key, T* ptr, int maxsize = 1, std::string keyofsize = "")
    {
	std::string typec = gxroot::GetTypeChar(ptr);
	if( maxsize <= 1 ) return key+"/"+typec;
	if( keyofsize == "" ) {
	    std::string title = key+"["+std::to_string(maxsize)+"]/"+typec;
	    return typec;
	}
	return key+"["+keyofsize+"]/"+typec;
    }
    
    class TTreeIOBase
    {
    protected:
	TTreeIOBase() : mKey(""), mTreeIndex(0), mAllocSize(0), mUsedSize(0) {}
	~TTreeIOBase() {}	
	std::string mKey;
	int mTreeIndex;
	int mAllocSize;
	int mUsedSize;
	
    public:
	virtual std::string Mode() { return ""; }
	virtual std::string Class() { return ""; }
	int Index() const { return mTreeIndex; }
	int AllocSize() const { return mAllocSize; }
	int UsedSize() const { return mUsedSize; }

	virtual void Get(int* ptr) const {}
	virtual void Get(std::vector<int>* ptr, int size) const {}
	virtual void Put(const int& ptr) {}
	virtual void Put(const std::vector<int>& ptr, int size) {}
	
	virtual void Get(unsigned int* ptr) const {}
	virtual void Get(std::vector<unsigned int>* ptr, int size) const {}
	virtual void Put(const unsigned int& ptr) {}
	virtual void Put(const std::vector<unsigned int>& ptr, int size) {}
	
	virtual void Get(unsigned short* ptr) const {};
	virtual void Get(std::vector<unsigned short>* ptr, int size) const {}
	virtual void Put(const unsigned short& ptr) {}
	virtual void Put(const std::vector<unsigned short>& ptr, int size) {}
	
	virtual void Get(float* ptr) const {}
	virtual void Get(std::vector<float>* ptr, int size) const {}
	virtual void Put(const float& ptr) {}
	virtual void Put(const std::vector<float>& ptr, int size) {}
    };
    
    template<typename T>
    class TTreeWriteValue : public gxroot::TTreeIOBase
    {
    private:
	T mValue;
	TBranch * mBranch;
    public:
	TTreeWriteValue(std::string key, bool save)
	    : mValue(0), mBranch(nullptr)
	{
	    mKey = key;
	    mTreeIndex = gCurrentTTreeIndex;
	    mAllocSize = 1;
	    mUsedSize = 1;
	    std::string title = gxroot::BranchTitle(key, &mValue);
	    if(save) mBranch = gTTree[mTreeIndex]->Branch(key.c_str(), &mValue, title.c_str());
	}
	~TTreeWriteValue() {}
	std::string Mode() override { return "write"; }
	std::string Class() override { return "value"; }
	void Get(T* ptr) const override { *ptr = mValue; }
	void Put(const T &ptr) override { mValue = ptr; }
    };

    template<typename T>
    class TTreeWriteArray : public gxroot::TTreeIOBase
    {
    private:
	T* mArray;
	TBranch * mBranch;
    public:
	TTreeWriteArray(std::string key, int maxsize, std::string keyofsize, bool save)
	    : mArray(nullptr), mBranch(nullptr)
	{
	    mKey = key;
	    mTreeIndex = gCurrentTTreeIndex;
	    mArray = new T[maxsize];
	    mAllocSize = maxsize;
	    mUsedSize = 0;
	    std::string title = BranchTitle(key, mArray, maxsize, keyofsize);
	    if(save) mBranch = gTTree[mTreeIndex]->Branch(key.c_str(), mArray, title.c_str());
	}
	~TTreeWriteArray() { /*delete mArray;*/ }
	std::string Mode() override { return "write"; }
	std::string Class() override { return "array"; }
	void Get(std::vector<T>* ptr, int size) const override
	{
	    if( size > mUsedSize ) size = mUsedSize;
	    ptr->clear();
	    ptr->resize(size);
	    for(int i = 0; i < size; ++i){ (*ptr)[i] = mArray[i]; }
	}
	void Put(const std::vector<T> &ptr, int size) override
	{
	    if( size < 0 ) size = ptr.size();
	    if( size > mAllocSize ) size = mAllocSize;
	    for(int i = 0; i < size; ++i){ mArray[i] = ptr[i];}
	    mUsedSize = size;
	}
    };
    
    template<typename T>
    class TTreeReadValue : public gxroot::TTreeIOBase
    {
    private:
	T mValue;
        //TTreeReaderValue<T>* mValue;
    public:
        TTreeReadValue(std::string key) : mValue(0)
	{
	    mKey = key;
            mTreeIndex = gCurrentTTreeIndex;
	    //mValue = new TTreeReaderValue<T>( *gTTreeReader[mTreeIndex], key.c_str() );
	    gTTree[mTreeIndex]->SetBranchAddress(key.c_str(), &mValue);
	    mAllocSize = 1;//mValue.GetSize();
            mUsedSize = 1;//mAllocSize;
	}
	~TTreeReadValue() {}
	std::string Mode() override { return "read"; }
	std::string Class() override { return "value"; }
        void Get(T* ptr) const override { *ptr = mValue; }
        void Put(const T &ptr) override {}
    };

    template<typename T>
    class TTreeReadArray : public gxroot::TTreeIOBase
    {
    private:
	T* mArray;//T mArray[64];
        //TTreeReaderArray<T>* mArray;
    public:
        TTreeReadArray(std::string key, int maxsize, std::string keyofsize)
	    : mArray(nullptr)
	{
	    mKey = key;
            mTreeIndex = gCurrentTTreeIndex;	    
            //mArray = new TTreeReaderArray<T>( *gTTreeReader[mTreeIndex], key.c_str() );
	    mArray = new T[maxsize];
	    gTTree[mTreeIndex]->SetBranchAddress(key.c_str(), mArray);
	    //mAllocSize = mArray->GetSize();
	    mAllocSize = maxsize;
	    mUsedSize = maxsize;
	}
	~TTreeReadArray() { delete mArray; }
        std::string Mode() override { return "read"; }
	std::string Class() override { return "array"; }
        void Get(std::vector<T>* ptr, int size) const override
	{
            ptr->clear();
            for(int i = 0; i < size; ++i){
                //(*ptr)[i] = mArray->At(i);
		ptr->push_back(mArray[i]);
            }
	}
        void Put(const std::vector<T> &ptr, int size) override {}
    };

    /**
       @class TTreeCloneValue<T>
       @brief 
    **/
    template<typename T>
    class TTreeCloneValue : public gxroot::TTreeIOBase
    {
    private:
	T mValue;
	TBranch * mBranch;
	int mInTreeIndex;
    public:
	TTreeCloneValue(std::string key, std::string intree, std::string outtree)
	    : mValue(0), mInTreeIndex(0), mBranch(nullptr)
	{
	    mKey = key;
	    int index;
	    if( TTreeIndex(outtree, &index) == GX_OK ) mTreeIndex = index;
	    else mTreeIndex = gCurrentTTreeIndex;
	    
	    TTreeIndex(intree, &index);
	    mInTreeIndex = index;
	    mAllocSize = 1;
	    mUsedSize = 1;
	    std::string title = gxroot::BranchTitle(key, &mValue);
	    gTTree[mInTreeIndex]->SetBranchAddress(key.c_str(), &mValue);
	    mBranch = gTTree[mTreeIndex]->Branch(key.c_str(), &mValue, title.c_str());
	}
	~TTreeCloneValue() {}
	std::string Mode() override { return "clone"; }
	std::string Class() override { return "value"; }
	void Get(T* ptr) const override { *ptr = mValue; }
	void Put(const T &ptr) override {}
    };
    
    template<typename T>
    int GetValue(std::string key, T* ptr)
    {
	//if( TypeCheck(key, ptr) == GX_NG ) return GX_NG;	
	int index;
	if( FindBranch(key, &index) == GX_NG ) return GX_NG;	
	gTBranchList[index]->Get(ptr);
	return GX_OK;
    }    
    template<typename T>
    int GetArray(std::string key, std::vector<T>* ptr, int size = -1)
    {
	//if( TypeCheck(key, ptr) == GX_NG ) return GX_NG;
        int index;
        if( FindBranch(key, &index) == GX_NG ) return GX_NG;
	gTBranchList[index]->Get(ptr, size);
	return GX_OK;
    }
    template<typename T>
    int PutValue(std::string key, const T &ptr)
    {
	//if( TypeCheck(key, ptr) == GX_NG ) return GX_NG;
        int index;
        if( FindBranch(key, &index) == GX_NG ) return GX_NG;
        gTBranchList[index]->Put(ptr);
        return GX_OK;
    }
    template<typename T>
    int PutArray(std::string key, const std::vector<T> &ptr, int size = -1)
    {
	//if( TypeCheck(key, ptr) == GX_NG ) return GX_NG;
        int index;
        if( FindBranch(key, &index) == GX_NG ) return GX_NG;
	gTBranchList[index]->Put(ptr, size);
	return GX_OK;
    }
}
#endif
