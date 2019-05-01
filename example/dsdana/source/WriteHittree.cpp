/**
   @file WriteHittree.cpp
   @author                      
   @date                        
   @version 1.0                 
**/
#include "WriteHittree.hpp"

using namespace anlcross;
using namespace std;

WriteHittree::WriteHittree() :
    WriteTTree("WriteHittree", "1.0")
{
}
void WriteHittree::mod_ana(int &status)
{
    using namespace bnk;
    status = ANL_OK;

    m_livetime = bnk_get<unsigned int>("livetime");
    m_unixtime = bnk_get<unsigned int>("unixtime");
    m_ext2ti_lower = bnk_get<unsigned int>("ext2ti_lower");
    
    m_nhit_lv3 = bnk_get<int>("nhit_lv3");
    bnk_get("detid_lv3", &m_detid_lv3, 0, m_nhit_lv3);
    bnk_get("epi_lv3",   &m_epi_lv3,   0, m_nhit_lv3);
    bnk_get("epi_x_lv3", &m_epi_x_lv3, 0, m_nhit_lv3);
    bnk_get("epi_y_lv3", &m_epi_y_lv3, 0, m_nhit_lv3);
    bnk_get("pos_x_lv3", &m_pos_x_lv3, 0, m_nhit_lv3);
    bnk_get("pos_y_lv3", &m_pos_y_lv3, 0, m_nhit_lv3);
    bnk_get("pos_z_lv3", &m_pos_z_lv3, 0, m_nhit_lv3);
    
    //bnk_put("eventID", m_eventID);
    ++m_eventID;

    int ihit = 0; int nbytes;
    while( m_nhit_lv3 > ihit ){
        m_detid = m_detid_lv3[ihit];
        m_epi = m_epi_lv3[ihit];
        m_epi_x = m_epi_x_lv3[ihit];
        m_epi_y = m_epi_y_lv3[ihit];
        m_pos_x = m_pos_x_lv3[ihit];
        m_pos_y = m_pos_y_lv3[ihit];
        m_pos_z = m_pos_z_lv3[ihit];

        this->setEventStatus(&m_event_status);
        //bnk_put("event_status", m_event_status);

	m_tree->Fill();
	//if( status == ANL_OK ) nbytes = m_tree->Fill();
	//if( nbytes<0 ) status = ANL_NG;
        ihit++;
    }
}
int WriteHittree::set_write_branch()
{
    using namespace bnk;

    m_tree->Branch(             "eventID",             &m_eventID,
				"eventID/I");
    m_tree->Branch(            "livetime",            &m_livetime,
			       "livetime/i");
    m_tree->Branch(            "unixtime",            &m_unixtime,
                            "unixtime/i");
    m_tree->Branch(        "ext2ti_lower",        &m_ext2ti_lower,
                        "ext2ti_lower/i");
    m_tree->Branch(               "detid",               &m_detid,
                               "detid/I");
    m_tree->Branch(                 "epi",                 &m_epi,
                                 "epi/F");
    m_tree->Branch(               "epi_x",               &m_epi_x,
                               "epi_x/F");
    m_tree->Branch(               "epi_y",               &m_epi_y,
                               "epi_y/F");
    m_tree->Branch(               "pos_x",               &m_pos_x,
                               "pos_x/F");
    m_tree->Branch(               "pos_y",               &m_pos_y,
                               "pos_y/F");
    m_tree->Branch(               "pos_z",               &m_pos_z,
                               "pos_z/F");
    m_tree->Branch(        "event_status",        &m_event_status,
                        "event_status/I");

    //bnk_def<int>  ("detid",       1);
    //bnk_def<float>("epi",         1);
    //bnk_def<float>("epi_x",       1);
    //bnk_def<float>("epi_y",       1);
    //bnk_def<float>("pos_x",       1);
    //bnk_def<float>("pos_y",       1);
    //bnk_def<float>("pos_z",       1);
    //bnk_def<int>  ("event_status",1);

    /*
    define_branch(               "detid",               &m_detid,
                               "detid/I");
    define_branch(                 "epi",                 &m_epi,
                                 "epi/F");
    define_branch(               "epi_x",               &m_epi_x,
                               "epi_x/F");
    define_branch(               "epi_y",               &m_epi_y,
                               "epi_y/F");
    define_branch(               "pos_x",               &m_pos_x,
                               "pos_x/F");
    define_branch(               "pos_y",               &m_pos_y,
                               "pos_y/F");
    define_branch(               "pos_z",               &m_pos_z,
                               "pos_z/F");
    define_branch(        "event_status",        &m_event_status,
                        "event_status/I");
    */
    return ANL_OK;
}
int WriteHittree::get_branch_value()
{
    get_branch("livetime",&m_livetime);
    get_branch("unixtime",&m_unixtime);
    get_branch("ext2ti_lower",&m_ext2ti_lower);
    get_branch("detid",&m_detid);
    get_branch("epi",&m_epi);
    get_branch("epi_x",&m_epi_x);
    get_branch("epi_y",&m_epi_y);
    get_branch("pos_x",&m_pos_x);
    get_branch("pos_y",&m_pos_y);
    get_branch("pos_z",&m_pos_z);
    get_branch("event_status",&m_event_status);
    return ANL_OK;
}
int WriteHittree::setEventStatus(int *event_status)
{
    return 0;
}
