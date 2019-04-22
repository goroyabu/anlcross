/**                   
  @file ReadEventtree.hpp
  @author G.Yabu
  @date               
  @version 1.0        
**/                   
#ifndef ReadEventtree_hpp
#define ReadEventtree_hpp

#include <string>       
#include <iostream>     
#include <ReadTTree.hpp>

class ReadEventtree : public ReadTTree
{                                  
    TTreeReaderValue<unsigned int>   m_livetime;           
    TTreeReaderValue<unsigned int>   m_unixtime;           
    TTreeReaderValue<unsigned short> m_hitnum0;            
    TTreeReaderValue<unsigned short> m_cmn0;               
    TTreeReaderArray<unsigned short> m_index0;             
    TTreeReaderArray<unsigned short> m_adc0;               
    TTreeReaderValue<unsigned short> m_hitnum1;            
    TTreeReaderValue<unsigned short> m_cmn1;               
    TTreeReaderArray<unsigned short> m_index1;             
    TTreeReaderArray<unsigned short> m_adc1;               
    TTreeReaderValue<unsigned short> m_hitnum2;            
    TTreeReaderValue<unsigned short> m_cmn2;               
    TTreeReaderArray<unsigned short> m_index2;             
    TTreeReaderArray<unsigned short> m_adc2;               
    TTreeReaderValue<unsigned short> m_hitnum3;            
    TTreeReaderValue<unsigned short> m_cmn3;               
    TTreeReaderArray<unsigned short> m_index3;             
    TTreeReaderArray<unsigned short> m_adc3;               
    TTreeReaderValue<unsigned short> m_hitnum4;            
    TTreeReaderValue<unsigned short> m_cmn4;               
    TTreeReaderArray<unsigned short> m_index4;             
    TTreeReaderArray<unsigned short> m_adc4;               
    TTreeReaderValue<unsigned short> m_hitnum5;            
    TTreeReaderValue<unsigned short> m_cmn5;               
    TTreeReaderArray<unsigned short> m_index5;             
    TTreeReaderArray<unsigned short> m_adc5;               
    TTreeReaderValue<unsigned short> m_hitnum6;            
    TTreeReaderValue<unsigned short> m_cmn6;               
    TTreeReaderArray<unsigned short> m_index6;             
    TTreeReaderArray<unsigned short> m_adc6;               
    TTreeReaderValue<unsigned short> m_hitnum7;            
    TTreeReaderValue<unsigned short> m_cmn7;               
    TTreeReaderArray<unsigned short> m_index7;             
    TTreeReaderArray<unsigned short> m_adc7;               

public:
    ReadEventtree();
    ~ReadEventtree(){}

    virtual int set_read_branch();
    virtual int put_branch_value();
};
#endif

