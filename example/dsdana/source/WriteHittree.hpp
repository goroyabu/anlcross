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
    int                               m_eventID;
    unsigned int                      m_livetime;
    unsigned int                      m_unixtime;
    unsigned int                      m_ext2ti_lower;
    int                               m_detid;
    float                             m_epi;
    float                             m_epi_x;
    float                             m_epi_y;
    float                             m_pos_x;
    float                             m_pos_y;
    float                             m_pos_z;
    int                               m_event_status;
    
    int m_nhit_lv3;
    std::vector<int> m_detid_lv3;
    std::vector<float> m_epi_lv3;
    std::vector<float> m_epi_x_lv3;
    std::vector<float> m_epi_y_lv3;
    std::vector<float> m_pos_x_lv3;
    std::vector<float> m_pos_y_lv3;
    std::vector<float> m_pos_z_lv3;
    std::vector<float> m_width_x_lv3;
    std::vector<float> m_width_y_lv3;
    std::vector<float> m_width_z_lv3;
    
public:
    WriteHittree();
    ~WriteHittree(){}
    void mod_ana(int &status);
    virtual int set_write_branch();
    virtual int get_branch_value();
private:
    int setEventStatus(int *event_status);
    
};
#endif

