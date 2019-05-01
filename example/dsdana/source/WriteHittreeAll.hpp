/**
   @file WriteHittreeAll.hpp
   @author                      
   @date                        
   @version 1.0                 
**/
#ifndef WriteHittreeAll_hpp
#define WriteHittreeAll_hpp

#include <vector>
#include <string>
#include <iostream>

#include "WriteTTree.hpp"

class WriteHittreeAll : public WriteTTree
{
protected:
    unsigned int                      m_livetime;
    unsigned int                      m_unixtime;
    unsigned int                      m_ti_upper;
    unsigned int                      m_ti_lower;
    unsigned int                      m_ext1ti_upper;
    unsigned int                      m_ext1ti_lower;
    unsigned int                      m_ext2ti_upper;
    unsigned int                      m_ext2ti_lower;
    int                               m_nsignal_x_lv1;
    int                               m_nsignal_y_lv1;
    std::vector<int>                  m_detid_x_lv1;
    std::vector<int>                  m_detid_y_lv1;
    std::vector<int>                  m_stripid_x_lv1;
    std::vector<int>                  m_stripid_y_lv1;
    std::vector<float>                m_epi_x_lv1;
    std::vector<float>                m_epi_y_lv1;
    int                               m_nsignal_x_lv2;
    int                               m_nsignal_y_lv2;
    std::vector<int>                  m_detid_x_lv2;
    std::vector<int>                  m_detid_y_lv2;
    std::vector<float>                m_epi_x_lv2;
    std::vector<float>                m_epi_y_lv2;
    std::vector<float>                m_pos_x_lv2;
    std::vector<float>                m_pos_y_lv2;
    std::vector<float>                m_width_x_lv2;
    std::vector<float>                m_width_y_lv2;
    std::vector<int>                  m_n_merged_strips_x_lv2;
    std::vector<int>                  m_n_merged_strips_y_lv2;
    int                               m_n_lv1signal_x_lv2;
    int                               m_n_lv1signal_y_lv2;
    std::vector<int>                  m_lv1signal_id_x_lv2;
    std::vector<int>                  m_lv1signal_id_y_lv2;
    int                               m_nhit_lv3;
    std::vector<int>                  m_detid_lv3;
    std::vector<float>                m_epi_lv3;
    std::vector<float>                m_epi_x_lv3;
    std::vector<float>                m_epi_y_lv3;
    std::vector<float>                m_pos_x_lv3;
    std::vector<float>                m_pos_y_lv3;
    std::vector<float>                m_pos_z_lv3;
    std::vector<float>                m_width_x_lv3;
    std::vector<float>                m_width_y_lv3;
    std::vector<float>                m_width_z_lv3;
    int                               m_n_lv2signal_x_lv3;
    int                               m_n_lv2signal_y_lv3;
    std::vector<int>                  m_lv2signal_id_x_lv3;
    std::vector<int>                  m_lv2signal_id_y_lv3;
    int                               m_detid;
    float                             m_epi;
    float                             m_epi_x;
    float                             m_epi_y;
    float                             m_pos_x;
    float                             m_pos_y;
    float                             m_pos_z;
    int                               m_event_status;
    
public:
    WriteHittreeAll();
    ~WriteHittreeAll(){}
    virtual int set_write_branch();
    virtual int get_branch_value();
};
#endif

