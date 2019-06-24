/**
   @file WriteTTree.hpp
   @author Goro Yabu
   @date 2019/04/18
   @version 1.0
**/
#ifndef WriteTTree_hpp
#define WriteTTree_hpp

#include <vector>
#include <string>
#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include <ANLModuleBase.hpp>
#include <ANLCross.hpp>

class WriteTTree : public anlcross::ANLModuleBase
{
protected:
    TFile * m_file;
    TTree * m_tree;
    std::string m_file_name;
    std::string m_tree_name;

    unsigned int m_livetime;
    std::vector<unsigned short> m_adc7;
    
public:
    WriteTTree();
    WriteTTree(std::string name, std::string version);
    ~WriteTTree(){}
    void mod_init(int &status);
    void mod_com(int &status);
    //void mod_bgnrun(int &status);
    void mod_ana(int &status);
    //void mod_endrun(int &status);
    void mod_exit(int &status);

    virtual int set_write_branch();
    virtual int get_branch_value();
    
    static TFile * OpenTFile(std::string name, std::string option);

    template<typename T>
    int define_branch(std::string key, std::string leaflist);
    //int define_branch(std::string key, T* value, std::string leaflist);
    template<typename T>
    int define_branch(std::string key,
		      //int define_branch(std::string key, std::vector<T>* array,
		      std::string leaflist, int maxsize);

    template<typename T>
    int get_branch(std::string key, T* value);
    template<typename T>
    int get_branch(std::string key, std::vector<T>* array);
};

template<typename T>
int WriteTTree::define_branch(std::string key, //T* value,
			      std::string leaflist)
{
    if( bnk::bnk_is_def(key)==bnk::BNK_NG ) return anlcross::ANL_NG;
    //if( !m_tree->Branch(key.c_str(), value, leaflist.c_str()) ) return anlcross::ANL_NG;
    if( !m_tree->Branch(key.c_str(), bnk::bnk_ptr<T>(key), leaflist.c_str()) ) return anlcross::ANL_NG;
    return anlcross::ANL_OK;
}
template<typename T>
int WriteTTree::define_branch(std::string key, //std::vector<T>* array,
			     std::string leaflist, int maxsize)
{
    if( bnk::bnk_is_def(key)==bnk::BNK_NG ) return anlcross::ANL_NG;
    //array->resize(maxsize);
    //if( !m_tree->Branch(key.c_str(), array->data(), leaflist.c_str()) ) return anlcross::ANL_NG;
    if( !m_tree->Branch(key.c_str(), bnk::bnk_ptr<T>(key), leaflist.c_str()) ) return anlcross::ANL_NG;
    return anlcross::ANL_OK;
}
template<typename T>
int WriteTTree::get_branch(std::string key, T* value)
{
    if( bnk::bnk_is_def(key)==bnk::BNK_NG ) return anlcross::ANL_NG;
    *value = bnk::bnk_get<T>(key);
    return anlcross::ANL_OK;
}
template<typename T>
int WriteTTree::get_branch(std::string key, std::vector<T>* array)
{
    //array->clear();
    if( bnk::bnk_is_def(key)==bnk::BNK_NG ) return anlcross::ANL_NG;
    bnk::bnk_get<T>(key, array, 0, -1);
    return anlcross::ANL_OK;
}

#endif










    
