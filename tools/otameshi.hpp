/**                   
  @file ReadMyTree.hpp
  @author Goro Yabu   
  @date 2019/04/17    
  @version 1.0        
**/                   
#ifndef ReadMyTree_hpp
#define ReadMyTree_hpp

#include <string>       
#include <iostream>     
#include <ReadTTree.hpp>

class ReadMyTree : public ReadTTree
{                                  
    TTreeReaderValue<unsigned int>   m_unixtime;
    TTreeReaderArray<unsigned short> m_adc0;
    
public:
    ReadMyTree();
    ~ReadMyTree(){}
    
    virtual int set_read_branch();
    virtual int put_branch_value();
};
#endif

