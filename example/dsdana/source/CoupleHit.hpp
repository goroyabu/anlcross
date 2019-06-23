/**
   @file CoupleHit.hpp
   @author Goro Yabu
   @date 2018/11/27
   @date 2019/06/20 v2.0
   @version 2.0
**/
#ifndef CoupleHit_hpp
#define CoupleHit_hpp

#include <vector>
#include <string>
#include <algorithm>

#include <TH1D.h>
#include <TH2D.h>

#include <ANLModuleBase.hpp>
#include <ANLCross.hpp>

#include "ReadDatabase.hpp"

class CoupleHit : public anlcross::ANLModuleBase
{
private:
    std::vector<int> m_sorted_index_x;
    std::vector<int> m_sorted_index_y;
    ReadDatabase * mDatabase;
    std::vector<int> m_detid_list;
    TH1D * m_spect;
    TH2D * m_image;
        
    /* input */
    int m_nsignal_x_lv2;
    int m_nsignal_y_lv2;
    std::vector<int> m_detid_x_lv2;
    std::vector<int> m_detid_y_lv2;
    std::vector<float> m_epi_x_lv2;
    std::vector<float> m_epi_y_lv2;
    std::vector<float> m_pos_x_lv2;
    std::vector<float> m_pos_y_lv2;
    std::vector<float> m_width_x_lv2;
    std::vector<float> m_width_y_lv2;
    std::vector<int> m_n_merged_strips_x_lv2;
    std::vector<int> m_n_merged_strips_y_lv2;
    int m_n_lv1signal_x_lv2, m_n_lv1signal_y_lv2;
    std::vector<int> m_lv1signal_id_x_lv2;
    std::vector<int> m_lv1signal_id_y_lv2;
    std::vector<int> m_lv2index_x, m_lv2index_y;
    
    /* temp */
    int m_nsignal_x, m_nsignal_y;
    //std::vector<int> m_detid_x, m_detid_y;
    std::vector<float> m_epi_x, m_epi_y;
    std::vector<float> m_pos_x, m_pos_y;
    std::vector<float> m_width_x, m_width_y;
    std::vector<int> m_n_merged_x, m_n_merged_y;
    std::vector<int> m_index_x, m_index_y;
    
    /* output */
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
    int m_n_lv2signal_x_lv3, m_n_lv2signal_y_lv3;
    std::vector<int> m_lv2signal_id_x_lv3;
    std::vector<int> m_lv2signal_id_y_lv3;

    int bnkDefAll();
    int bnkGetAll();
    int bnkPutAll();
    int clearVectorAll();
    int reconstructLv2toLv3(int detid);
    void extractOneDetector(int detid);
    void sortIndex(int nsignal, std::vector<float> &epi_list, std::vector<int>* sorted_list);
    void case1and1(int detid);
    void case1and2(int detid);
    void case2and1(int detid);
    void case2and2(int detid);
    void case3over(int detid);

public:
    CoupleHit();
    ~CoupleHit(){}

    void mod_init(int &status);
    void mod_his(int &status);
    void mod_com(int &status);
    void mod_ana(int &status);
    void mod_endrun(int &status);
    void mod_exit(int &status);
};
#endif
