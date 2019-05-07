/**
   @file CoupleHit.cpp
   @author Goro Yabu
   @date 2018/12/03
   @version 1.0
**/
#include "CoupleHit.hpp"
using namespace anlcross;
CoupleHit::CoupleHit() : ANLModuleBase("CoupleHit", "1.0"), mDatabase(nullptr),
			 m_spect(nullptr), m_image(nullptr)
{
}
void CoupleHit::mod_init(int &status)
{
    status = ANL_OK;
    std::cout << "CoupleHit::mod_init" << std::endl;
    
    mDatabase = (ReadDatabase*)get_module("ReadDatabase");
    if( !mDatabase || mDatabase->mod_name()!="ReadDatabase") status = ANL_NG;
    mDatabase->GetDetIDList(&m_detid_list);
    
    status = this->bnkDefAll();

    //evs::EvsDef("1Pt-1Al Merged signals");
    //evs::EvsDef("1Pt-2Al Merged signals");
    //evs::EvsDef("2Pt-1Al Merged signals");
    //evs::EvsDef("2Pt-2Al Merged signals");
    //evs::EvsDef("Over 3  Merged signals");
    evs::EvsDef("1     Hit Event");
    evs::EvsDef("2     Hit Event");
    evs::EvsDef("Over3 Hit Event");
    
    std::cout << std::endl;
}
void CoupleHit::mod_his(int &status)
{
    m_spect = new TH1D("spect_lv3", "spect;epi_lv3", 1000, -10.25, 489.25);
    m_image = new TH2D("image_lv3", "image;pos_x_lv3;pos_y_lv3", 128, -16, 16, 128, -16, 16);
    status = ANL_OK;
}
void CoupleHit::mod_com(int &status)
{
    status = ANL_OK;
}
void CoupleHit::mod_ana(int &status)
{
    using namespace gxroot;
    status = ANL_OK;

    this->clearVectorAll();
    this->bnkGetAll();

    for(auto detid : m_detid_list){
	this->reconstructLv2toLv3(detid);
    }

    this->bnkPutAll();
}
void CoupleHit::mod_endrun(int &status)
{
    if( gDirectory->InheritsFrom("TFile") && gDirectory->GetFile()->IsOpen() ){
	m_spect->Write();
	m_image->Write();
    }
    status = ANL_OK;
}
void CoupleHit::mod_exit(int &status)
{
    status = ANL_OK;
    //std::cout << std::endl;
}
int CoupleHit::bnkDefAll()
{
    using namespace std;
    using namespace bnk;

    int n_ng = 0;
    if( bnk_is_def("nsignal_x_lv2")==BNK_NG )         ++n_ng;
    if( bnk_is_def("nsignal_y_lv2")==BNK_NG )         ++n_ng;
    if( bnk_is_def("detid_x_lv2")==BNK_NG )           ++n_ng;
    if( bnk_is_def("detid_y_lv2")==BNK_NG )           ++n_ng;
    if( bnk_is_def("epi_x_lv2")==BNK_NG )             ++n_ng;
    if( bnk_is_def("epi_y_lv2")==BNK_NG )             ++n_ng;
    if( bnk_is_def("pos_x_lv2")==BNK_NG )             ++n_ng;
    if( bnk_is_def("pos_y_lv2")==BNK_NG )             ++n_ng;
    if( bnk_is_def("width_x_lv2")==BNK_NG )           ++n_ng;
    if( bnk_is_def("width_y_lv2")==BNK_NG )           ++n_ng;
    if( bnk_is_def("n_merged_strips_x_lv2")==BNK_NG ) ++n_ng;
    if( bnk_is_def("n_merged_strips_y_lv2")==BNK_NG ) ++n_ng;
    if( bnk_is_def("n_lv1signal_x_lv2")==BNK_NG )     ++n_ng;
    if( bnk_is_def("n_lv1signal_y_lv2")==BNK_NG )     ++n_ng;
    if( bnk_is_def("lv1signal_id_x_lv2")==BNK_NG )    ++n_ng;
    if( bnk_is_def("lv1signal_id_y_lv2")==BNK_NG )    ++n_ng;

    if(n_ng!=0){
	cout << "Error : All of Lv2 data must be defined in BNK" << endl;
	return ANL_NG;
    }
    
    bnk_def<int>  ("nhit_lv3",             1);
    bnk_def<int>  ("detid_lv3",          128);
    bnk_def<float>("epi_lv3",            128);
    bnk_def<float>("epi_x_lv3",          128);
    bnk_def<float>("epi_y_lv3",          128);
    bnk_def<float>("pos_x_lv3",          128);
    bnk_def<float>("pos_y_lv3",          128);
    bnk_def<float>("pos_z_lv3",          128);
    bnk_def<float>("width_x_lv3",        128);
    bnk_def<float>("width_y_lv3",        128);
    bnk_def<float>("width_z_lv3",        128);
    bnk_def<int>  ("n_lv2signal_x_lv3",    1);
    bnk_def<int>  ("n_lv2signal_y_lv3",    1);
    bnk_def<int>  ("lv2signal_id_x_lv3", 128);
    bnk_def<int>  ("lv2signal_id_y_lv3", 128);
    
    return ANL_OK;
}
int CoupleHit::bnkGetAll()
{
    using namespace bnk;
    m_nsignal_x_lv2 = bnk_get<int>("nsignal_x_lv2");
    m_nsignal_y_lv2 = bnk_get<int>("nsignal_y_lv2");
    bnk_get<int>  ("detid_x_lv2", &m_detid_x_lv2, 0, m_nsignal_x_lv2);
    bnk_get<int>  ("detid_y_lv2", &m_detid_y_lv2, 0, m_nsignal_y_lv2);
    bnk_get<float>("epi_x_lv2",   &m_epi_x_lv2,   0, m_nsignal_x_lv2);
    bnk_get<float>("epi_y_lv2",   &m_epi_y_lv2,   0, m_nsignal_y_lv2);
    bnk_get<float>("pos_x_lv2",   &m_pos_x_lv2,   0, m_nsignal_x_lv2);
    bnk_get<float>("pos_y_lv2",   &m_pos_y_lv2,   0, m_nsignal_y_lv2);
    bnk_get<float>("width_x_lv2", &m_width_x_lv2, 0, m_nsignal_x_lv2);
    bnk_get<float>("width_y_lv2", &m_width_y_lv2, 0, m_nsignal_y_lv2);
    bnk_get<int>  ("n_merged_strips_x_lv2", &m_n_merged_strips_x_lv2, 0, m_nsignal_x_lv2);
    bnk_get<int>  ("n_merged_strips_y_lv2", &m_n_merged_strips_y_lv2, 0, m_nsignal_x_lv2);
    m_n_lv1signal_x_lv2 = bnk_get<int>("n_lv1signal_x_lv2");
    m_n_lv1signal_y_lv2 = bnk_get<int>("n_lv1signal_y_lv2");
    bnk_get<int>  ("lv1signal_id_x_lv2", &m_lv1signal_id_x_lv2, 0, m_n_lv1signal_x_lv2);
    bnk_get<int>  ("lv1signal_id_y_lv2", &m_lv1signal_id_y_lv2, 0, m_n_lv1signal_y_lv2);
    m_lv2index_x.clear(); m_lv2index_y.clear();
    for(int i=0; i<m_nsignal_x_lv2; ++i) m_lv2index_x.emplace_back(i);
    for(int i=0; i<m_nsignal_y_lv2; ++i) m_lv2index_y.emplace_back(i);
    return ANL_OK;
}
int CoupleHit::bnkPutAll()
{
    using namespace bnk;
    bnk_put<int>  ("nhit_lv3",    m_nhit_lv3);
    bnk_put<int>  ("detid_lv3",   m_detid_lv3,   0, m_nhit_lv3);
    bnk_put<float>("epi_lv3",     m_epi_lv3,     0, m_nhit_lv3);
    bnk_put<float>("epi_x_lv3",   m_epi_x_lv3,   0, m_nhit_lv3);
    bnk_put<float>("epi_y_lv3",   m_epi_y_lv3,   0, m_nhit_lv3);
    bnk_put<float>("pos_x_lv3",   m_pos_x_lv3,   0, m_nhit_lv3);
    bnk_put<float>("pos_y_lv3",   m_pos_y_lv3,   0, m_nhit_lv3);
    bnk_put<float>("pos_z_lv3",   m_pos_z_lv3,   0, m_nhit_lv3);
    bnk_put<float>("width_x_lv3", m_width_x_lv3, 0, m_nhit_lv3);
    bnk_put<float>("width_y_lv3", m_width_y_lv3, 0, m_nhit_lv3);
    bnk_put<float>("width_z_lv3", m_width_z_lv3, 0, m_nhit_lv3);
    bnk_put<int>  ("n_lv2signal_x_lv3", m_n_lv2signal_x_lv3);
    bnk_put<int>  ("n_lv2signal_y_lv3", m_n_lv2signal_y_lv3);
    bnk_put<int>  ("lv2signal_id_x_lv3", m_lv2signal_id_x_lv3, 0, m_n_lv2signal_x_lv3);
    bnk_put<int>  ("lv2signal_id_y_lv3", m_lv2signal_id_y_lv3, 0, m_n_lv2signal_y_lv3);
    
    if(m_nhit_lv3==1)      evs::EvsSet("1     Hit Event");
    else if(m_nhit_lv3==2) evs::EvsSet("2     Hit Event");
    else if(m_nhit_lv3>=3) evs::EvsSet("Over3 Hit Event");
    
    for(int i=0; i<m_nhit_lv3; i++){
	m_image->Fill(m_pos_x_lv3[i], m_pos_y_lv3[i]);
	m_spect->Fill(m_epi_lv3[i]);
    }
    return ANL_OK;
}
int CoupleHit::clearVectorAll()
{
    m_nhit_lv3 = 0;
    m_detid_lv3.clear();
    m_epi_lv3.clear();
    m_epi_x_lv3.clear();
    m_epi_y_lv3.clear();
    m_pos_x_lv3.clear();
    m_pos_y_lv3.clear();
    m_pos_z_lv3.clear();
    m_width_x_lv3.clear();
    m_width_y_lv3.clear();
    m_width_z_lv3.clear();
    m_n_lv2signal_x_lv3 = 0;
    m_n_lv2signal_y_lv3 = 0;
    m_lv2signal_id_x_lv3.clear();
    m_lv2signal_id_y_lv3.clear();
    return ANL_OK;
}
int CoupleHit::reconstructLv2toLv3(int detid)
{
    this->extractOneDetector(detid);
    
    this->sortIndex(m_nsignal_x, m_epi_x, &m_sorted_index_x);
    this->sortIndex(m_nsignal_y, m_epi_y, &m_sorted_index_y);

    if(m_nsignal_x == 1 && m_nsignal_y == 1) this->case1and1(detid);
    else if(m_nsignal_x == 1 && m_nsignal_y == 2) this->case1and2(detid);
    else if(m_nsignal_x == 2 && m_nsignal_y == 1) this->case2and1(detid);
    else if(m_nsignal_x == 2 && m_nsignal_y == 2) this->case2and2(detid);
    else this->case3over(detid);
    
    return ANL_OK;
}
void CoupleHit::extractOneDetector(int detid)
{
    m_nsignal_x = 0;
    m_epi_x.clear();
    m_pos_x.clear();
    m_width_x.clear();
    m_n_merged_x.clear();
    m_index_x.clear();
    for(int ix=0; ix<m_nsignal_x_lv2; ++ix){
	if( m_detid_x_lv2[ix] != detid ) continue;
	++m_nsignal_x;
	m_epi_x.emplace_back( m_epi_x_lv2[ix] );
	m_pos_x.emplace_back( m_pos_x_lv2[ix] );
	m_width_x.emplace_back( m_width_x_lv2[ix] );
	m_n_merged_x.emplace_back( m_n_merged_strips_x_lv2[ix] );
	m_index_x.emplace_back( m_lv2index_x[ix] );
    }

    m_nsignal_y = 0;
    m_epi_y.clear();
    m_pos_y.clear();
    m_width_y.clear();
    m_n_merged_y.clear();
    m_index_y.clear();
    for(int iy=0; iy<m_nsignal_y_lv2; ++iy){
	if( m_detid_y_lv2[iy] != detid ) continue;
	++m_nsignal_y;
	m_epi_y.emplace_back( m_epi_y_lv2[iy] );
	m_pos_y.emplace_back( m_pos_y_lv2[iy] );
	m_width_y.emplace_back( m_width_y_lv2[iy] );
	m_n_merged_y.emplace_back( m_n_merged_strips_y_lv2[iy] );
	m_index_y.emplace_back( m_lv2index_y[iy] );
    }
}
void CoupleHit::sortIndex(int nsignal, std::vector<float> &epi_list, std::vector<int>* sorted_list)
{
    std::vector< std::pair<float, int> > pair_list;
    for(int index = 0; index < nsignal; index++){
	auto p = std::make_pair(epi_list[index], index);
	pair_list.emplace_back(p);
    }
    std::sort( pair_list.rbegin(), pair_list.rend() );//epi koujyun
    sorted_list->clear();
    for(int newindex = 0; newindex < nsignal; newindex++){
	sorted_list->emplace_back( pair_list[newindex].second );
    }
}
void CoupleHit::case1and1(int detid)
{
    float epi = ( m_epi_x[0] + m_epi_y[0] ) * 0.5;
    float epi_x = m_epi_x[0];
    float epi_y = m_epi_y[0];
    float pos_x = m_pos_x[0];
    float pos_y = m_pos_y[0];
    float width_x = m_width_x[0];
    float width_y = m_width_y[0];
    float pos_z, width_z;
    mDatabase->GetZ(detid, 0, &pos_z);
    mDatabase->GetWidthZ(detid, 0, &width_z);
    
    ++m_nhit_lv3;
    m_detid_lv3.emplace_back(detid);
    m_epi_lv3.emplace_back(epi);
    m_epi_x_lv3.emplace_back(epi_x);
    m_epi_y_lv3.emplace_back(epi_y);
    m_pos_x_lv3.emplace_back(pos_x);
    m_pos_y_lv3.emplace_back(pos_y);
    m_pos_z_lv3.emplace_back(pos_z);
    m_width_x_lv3.emplace_back(width_x);
    m_width_y_lv3.emplace_back(width_y);
    m_width_z_lv3.emplace_back(width_z);
    ++m_n_lv2signal_x_lv3;
    ++m_n_lv2signal_y_lv3;
    m_lv2signal_id_x_lv3.emplace_back(m_index_x[0]);
    m_lv2signal_id_y_lv3.emplace_back(m_index_y[0]);

    //evs::EvsSet("1Pt-1Al signal");
}
void CoupleHit::case1and2(int detid)
{
    //evs::EvsSet("1Pt-2Al signal");
}
void CoupleHit::case2and1(int detid)
{
    //evs::EvsSet("2Pt-1Al signal");
}
void CoupleHit::case2and2(int detid)
{
    //evs::EvsSet("2Pt-2Al signal");
}
void CoupleHit::case3over(int detid)
{
    float pos_z, width_z;
    mDatabase->GetZ(detid, 0, &pos_z);
    mDatabase->GetWidthZ(detid, 0, &width_z);
    
    if( m_nsignal_x == m_nsignal_y ){
	for(int i=0; i<m_nsignal_x; ++i){
	    int index_x = m_sorted_index_x[i];
	    int index_y = m_sorted_index_y[i];
	    float epi = ( m_epi_x[index_x] + m_epi_y[index_y] ) * 0.5;
	    float epi_x = m_epi_x[index_x];
	    float epi_y = m_epi_y[index_y];
	    float pos_x = m_pos_x[index_x];
	    float pos_y = m_pos_y[index_y];
	    float width_x = m_width_x[index_x];
	    float width_y = m_width_y[index_y];

	    ++m_nhit_lv3;
	    m_detid_lv3.emplace_back(detid);
	    m_epi_lv3.emplace_back(epi);
	    m_epi_x_lv3.emplace_back(epi_x);
	    m_epi_y_lv3.emplace_back(epi_y);
	    m_pos_x_lv3.emplace_back(pos_x);
	    m_pos_y_lv3.emplace_back(pos_y);
	    m_pos_z_lv3.emplace_back(pos_z);
	    m_width_x_lv3.emplace_back(width_x);
	    m_width_y_lv3.emplace_back(width_y);
	    m_width_z_lv3.emplace_back(width_z);
	}
    }
    //evs::EvsSet("over 3 signals on 1 side");
}
