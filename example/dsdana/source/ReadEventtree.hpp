/**                   
  @file ReadEventtree.hpp
  @author 
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
    unsigned int   m_livetime;           
    unsigned int   m_unixtime;           
    unsigned int   m_ti_upper;           
    unsigned int   m_ti_lower;           
    unsigned int   m_ext1ti_upper;       
    unsigned int   m_ext1ti_lower;       
    unsigned int   m_ext2ti_upper;       
    unsigned int   m_ext2ti_lower;       
    unsigned short int m_hitnum0;            
    unsigned short int m_cmn0;               
    unsigned short int m_index0;             
    unsigned short int m_adc0;               
    unsigned short int m_hitnum1;            
    unsigned short int m_cmn1;               
    unsigned short int m_index1;             
    unsigned short int m_adc1;               
    unsigned short int m_hitnum2;            
    unsigned short int m_cmn2;               
    unsigned short int m_index2;             
    unsigned short int m_adc2;               
    unsigned short int m_hitnum3;            
    unsigned short int m_cmn3;               
    unsigned short int m_index3;             
    unsigned short int m_adc3;               
    unsigned short int m_hitnum4;            
    unsigned short int m_cmn4;               
    unsigned short int m_index4;             
    unsigned short int m_adc4;               
    unsigned short int m_hitnum5;            
    unsigned short int m_cmn5;               
    unsigned short int m_index5;             
    unsigned short int m_adc5;               
    unsigned short int m_hitnum6;            
    unsigned short int m_cmn6;               
    unsigned short int m_index6;             
    unsigned short int m_adc6;               
    unsigned short int m_hitnum7;            
    unsigned short int m_cmn7;               
    unsigned short int m_index7;             
    unsigned short int m_adc7;               

public:
    ReadEventtree();
    ~ReadEventtree(){}

    virtual int set_read_branch();
    virtual int put_branch_value();
};
#endif

