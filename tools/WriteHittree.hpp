/**
   @file WriteHittree.hpp
   @author                      
   @date                        
   @version 1.0                 
**/
#ifndef WriteHittree_hpp
#define WriteHittree_hpp

#include <vector>
#include <string>
#include <iostream>

#include "WriteTTree.hpp"

class WriteHittree : public WriteTTree
{
protected:
    unsigned int                      m_livetime;
    unsigned int                      m_unixtime;
    int                               m_detid;
    float                             m_epi;
    float                             m_epi_x;
    float                             m_epi_y;
    float                             m_pos_x;
    float                             m_pos_y;
    float                             m_pos_z;
    int                               m_event_status;
    
public:
    WriteHittree();
    ~WriteHittree(){}
    virtual int set_write_branch();
    virtual int get_branch_value();
};
#endif

