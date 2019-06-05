/**
   @file ReadTTree.hpp
   @author Goro Yabu
   @date 2019/04/17
   @date 2019/06/05 v2.0 Change how to read branch from using TTreeReader -> SetBranchAddress with bnk_ptr
   @version 2.0
**/
#ifndef ReadTTree_hpp
#define ReadTTree_hpp

#include <string>
#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include <ANLModuleBase.hpp>
#include <ANLCross.hpp>

class ReadTTree : public anlcross::ANLModuleBase
{
protected:
    TFile * m_file;
    TTreeReader m_tree_reader;
    std::string m_file_name;
    std::string m_tree_name;
    long int m_current_entry;
    long int m_max_entry;
    
public:
    ReadTTree();
    ReadTTree(std::string name, std::string version, std::string tree);
    ~ReadTTree(){}
    void mod_init(int &status);
    void mod_com(int &status);
    //void mod_bgnrun(int &status);
    void mod_ana(int &status);
    //void mod_endrun(int &status);
    void mod_exit(int &status);

    virtual int set_read_branch();
    virtual int put_branch_value();

    template<typename T>
    int put_branch(TTreeReaderValue<T>& value);
    template<typename T>
    int put_branch_array(TTreeReaderArray<T>& array, int size=-1);
    
    template<typename T>
    int read_branch(std::string key, TTreeReaderValue<T>& value);
    template<typename T>
    int read_branch_array(std::string key, TTreeReaderArray<T>& array, int maxsize=1);

    template<typename T>
    int read_branch(std::string key);
    template<typename T>
    int read_branch_array(std::string key, int maxsize);
    
    static TFile * OpenTFile(std::string name, std::string option);
    static int GetTTreeReader(std::string name, TFile * file, TTreeReader* reader);
    static int IsValidValue(ROOT::Internal::TTreeReaderValueBase& value);
};

template<typename T>
int ReadTTree::read_branch(std::string key, TTreeReaderValue<T>& value)
{
    value = TTreeReaderValue<T>(m_tree_reader, key.c_str());
    bnk::bnk_def<T>(key);
    if( value.IsValid()==anlcross::ANL_NG ){
	return anlcross::ANL_NG;
    }
    return anlcross::ANL_OK;
}
template<typename T>
int ReadTTree::read_branch_array(std::string key, TTreeReaderArray<T>& array, int maxsize)
{
    array = TTreeReaderArray<T>(m_tree_reader, key.c_str());
    bnk::bnk_def<T>(key, maxsize);
    if( array.IsValid()==anlcross::ANL_NG ) return anlcross::ANL_NG;
    return anlcross::ANL_OK;
}
template<typename T>
int ReadTTree::put_branch(TTreeReaderValue<T>& value)
{
    if( bnk::BNK_NG == bnk::bnk_put<T>(value.GetBranchName(), *value) )
	return anlcross::ANL_NG;
    return anlcross::ANL_OK;
}
template<typename T>
int ReadTTree::put_branch_array(TTreeReaderArray<T>& array, int size)
{
    if(size==-1) size = array.GetSize();
    std::vector<T> vec;
    //for(int i=0; i<size; ++i) vec.push_back(array.At(i));
    for(int i=0; i<size; ++i) vec.emplace_back(array.At(i));
    if( bnk::BNK_NG == bnk::bnk_put<T>(array.GetBranchName(), vec, 0, size) ){
     return anlcross::ANL_NG;}
    return anlcross::ANL_OK;
}
template<typename T>
int ReadTTree::read_branch(std::string key)
{
    bnk::bnk_def<T>(key);
    bnk::bnk_resize<T>(key, 1);
    if( !(m_tree_reader.GetTree())->FindBranch(key.c_str()) ){
	return anlcross::ANL_NG;
    }
    m_tree_reader.GetTree()->SetBranchAddress(key.c_str(), bnk::bnk_ptr<T>(key));
    return anlcross::ANL_OK;
}
template<typename T>
int ReadTTree::read_branch_array(std::string key, int maxsize)
{
    bnk::bnk_def<T>(key, maxsize);
    bnk::bnk_resize<T>(key, maxsize);
    if( !(m_tree_reader.GetTree())->FindBranch(key.c_str()) ){
	return anlcross::ANL_NG;
    }
    m_tree_reader.GetTree()->SetBranchAddress(key.c_str(), bnk::bnk_ptr<T>(key));
    return anlcross::ANL_OK;
}

#endif
