/**
   @file WriteHittreeAll.cpp
   @author                      
   @date                        
   @version 1.0                 
**/
#include "WriteHittreeAll.hpp"

using namespace anlcross;
using namespace std;

WriteHittreeAll::WriteHittreeAll() :
    WriteTTree("WriteHittreeAll", "1.0")
{
}
int WriteHittreeAll::set_write_branch()
{
    define_branch<unsigned int>(            "livetime",            &m_livetime,
					    "livetime/i");
    define_branch<unsigned int>(            "unixtime",            &m_unixtime,
					    "unixtime/i");
    define_branch<unsigned int>(            "ti_upper",            &m_ti_upper,
					    "ti_upper/i");
    define_branch<unsigned int>(            "ti_lower",            &m_ti_lower,
					    "ti_lower/i");
    define_branch<unsigned int>(        "ext1ti_upper",        &m_ext1ti_upper,
					"ext1ti_upper/i");
    define_branch<unsigned int>(        "ext1ti_lower",        &m_ext1ti_lower,
					"ext1ti_lower/i");
    define_branch<unsigned int>(        "ext2ti_upper",        &m_ext2ti_upper,
					"ext2ti_upper/i");
    define_branch<unsigned int>(        "ext2ti_lower",        &m_ext2ti_lower,
					"ext2ti_lower/i");
    define_branch<int>(       "nsignal_x_lv1",       &m_nsignal_x_lv1,
			      "nsignal_x_lv1/I");
    define_branch<int>(       "nsignal_y_lv1",       &m_nsignal_y_lv1,
			      "nsignal_y_lv1/I");
    define_branch<int>(         "detid_x_lv1",         &m_detid_x_lv1,
				"detid_x_lv1[nsignal_x_lv1]/I",  128);
    define_branch<int>(         "detid_y_lv1",         &m_detid_y_lv1,
				"detid_y_lv1[nsignal_y_lv1]/I",  128);
    define_branch<int>(       "stripid_x_lv1",       &m_stripid_x_lv1,
			      "stripid_x_lv1[nsignal_x_lv1]/I",  128);
    define_branch<int>(       "stripid_y_lv1",       &m_stripid_y_lv1,
			      "stripid_y_lv1[nsignal_y_lv1]/I",  128);
    define_branch<float>(           "epi_x_lv1",           &m_epi_x_lv1,
				    "epi_x_lv1[nsignal_x_lv1]/F",  128);
    define_branch<float>(           "epi_y_lv1",           &m_epi_y_lv1,
                  "epi_y_lv1[nsignal_y_lv1]/F",  128);
    define_branch<int>(       "nsignal_x_lv2",       &m_nsignal_x_lv2,
                       "nsignal_x_lv2/I");
    define_branch<int>(       "nsignal_y_lv2",       &m_nsignal_y_lv2,
                       "nsignal_y_lv2/I");
    define_branch<int>(         "detid_x_lv2",         &m_detid_x_lv2,
                  "detid_x_lv2[nsignal_x_lv2]/I",  128);
    define_branch<int>(         "detid_y_lv2",         &m_detid_y_lv2,
                  "detid_y_lv2[nsignal_y_lv2]/I",  128);
    define_branch<float>(           "epi_x_lv2",           &m_epi_x_lv2,
                  "epi_x_lv2[nsignal_x_lv2]/F",  128);
    define_branch<float>(           "epi_y_lv2",           &m_epi_y_lv2,
                  "epi_y_lv2[nsignal_y_lv2]/F",  128);
    define_branch<float>(           "pos_x_lv2",           &m_pos_x_lv2,
                  "pos_x_lv2[nsignal_x_lv2]/F",  128);
    define_branch<float>(           "pos_y_lv2",           &m_pos_y_lv2,
                  "pos_y_lv2[nsignal_y_lv2]/F",  128);
    define_branch<float>(         "width_x_lv2",         &m_width_x_lv2,
                  "width_x_lv2[nsignal_x_lv2]/F",  128);
    define_branch<float>(         "width_y_lv2",         &m_width_y_lv2,
                  "width_y_lv2[nsignal_y_lv2]/F",  128);
    define_branch("n_merged_strips_x_lv2",&m_n_merged_strips_x_lv2,
                  "n_merged_strips_x_lv2[nsignal_x_lv2]/I",  128);
    define_branch("n_merged_strips_y_lv2",&m_n_merged_strips_y_lv2,
                  "n_merged_strips_y_lv2[nsignal_y_lv2]/I",  128);
    define_branch(   "n_lv1signal_x_lv2",   &m_n_lv1signal_x_lv2,
                   "n_lv1signal_x_lv2/I");
    define_branch(   "n_lv1signal_y_lv2",   &m_n_lv1signal_y_lv2,
                   "n_lv1signal_y_lv2/I");
    define_branch(  "lv1signal_id_x_lv2",  &m_lv1signal_id_x_lv2,
                  "lv1signal_id_x_lv2[n_lv1signal_x_lv2]/I",  128);
    define_branch(  "lv1signal_id_y_lv2",  &m_lv1signal_id_y_lv2,
                  "lv1signal_id_y_lv2[n_lv1signal_y_lv2]/I",  128);
    define_branch(            "nhit_lv3",            &m_nhit_lv3,
                            "nhit_lv3/I");
    define_branch(           "detid_lv3",           &m_detid_lv3,
                  "detid_lv3[nhit_lv3]/I",  128);
    define_branch(             "epi_lv3",             &m_epi_lv3,
                  "epi_lv3[nhit_lv3]/F",  128);
    define_branch(           "epi_x_lv3",           &m_epi_x_lv3,
                  "epi_x_lv3[nhit_lv3]/F",  128);
    define_branch(           "epi_y_lv3",           &m_epi_y_lv3,
                  "epi_y_lv3[nhit_lv3]/F",  128);
    define_branch(           "pos_x_lv3",           &m_pos_x_lv3,
                  "pos_x_lv3[nhit_lv3]/F",  128);
    define_branch(           "pos_y_lv3",           &m_pos_y_lv3,
                  "pos_y_lv3[nhit_lv3]/F",  128);
    define_branch(           "pos_z_lv3",           &m_pos_z_lv3,
                  "pos_z_lv3[nhit_lv3]/F",  128);
    define_branch(         "width_x_lv3",         &m_width_x_lv3,
                  "width_x_lv3[nhit_lv3]/F",  128);
    define_branch(         "width_y_lv3",         &m_width_y_lv3,
                  "width_y_lv3[nhit_lv3]/F",  128);
    define_branch(         "width_z_lv3",         &m_width_z_lv3,
                  "width_z_lv3[nhit_lv3]/F",  128);
    define_branch(   "n_lv2signal_x_lv3",   &m_n_lv2signal_x_lv3,
                   "n_lv2signal_x_lv3/I");
    define_branch(   "n_lv2signal_y_lv3",   &m_n_lv2signal_y_lv3,
                   "n_lv2signal_y_lv3/I");
    define_branch(  "lv2signal_id_x_lv3",  &m_lv2signal_id_x_lv3,
                  "lv2signal_id_x_lv3[n_lv2signal_x_lv3]/I",  128);
    define_branch(  "lv2signal_id_y_lv3",  &m_lv2signal_id_y_lv3,
                  "lv2signal_id_y_lv3[n_lv2signal_y_lv3]/I",  128);
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
    return ANL_OK;
}
int WriteHittreeAll::get_branch_value()
{
    get_branch("livetime",&m_livetime);
    get_branch("unixtime",&m_unixtime);
    get_branch("ti_upper",&m_ti_upper);
    get_branch("ti_lower",&m_ti_lower);
    get_branch("ext1ti_upper",&m_ext1ti_upper);
    get_branch("ext1ti_lower",&m_ext1ti_lower);
    get_branch("ext2ti_upper",&m_ext2ti_upper);
    get_branch("ext2ti_lower",&m_ext2ti_lower);
    get_branch("nsignal_x_lv1",&m_nsignal_x_lv1);
    get_branch("nsignal_y_lv1",&m_nsignal_y_lv1);
    get_branch("detid_x_lv1",&m_detid_x_lv1);
    get_branch("detid_y_lv1",&m_detid_y_lv1);
    get_branch("stripid_x_lv1",&m_stripid_x_lv1);
    get_branch("stripid_y_lv1",&m_stripid_y_lv1);
    get_branch("epi_x_lv1",&m_epi_x_lv1);
    get_branch("epi_y_lv1",&m_epi_y_lv1);
    get_branch("nsignal_x_lv2",&m_nsignal_x_lv2);
    get_branch("nsignal_y_lv2",&m_nsignal_y_lv2);
    get_branch("detid_x_lv2",&m_detid_x_lv2);
    get_branch("detid_y_lv2",&m_detid_y_lv2);
    get_branch("epi_x_lv2",&m_epi_x_lv2);
    get_branch("epi_y_lv2",&m_epi_y_lv2);
    get_branch("pos_x_lv2",&m_pos_x_lv2);
    get_branch("pos_y_lv2",&m_pos_y_lv2);
    get_branch("width_x_lv2",&m_width_x_lv2);
    get_branch("width_y_lv2",&m_width_y_lv2);
    get_branch("n_merged_strips_x_lv2",&m_n_merged_strips_x_lv2);
    get_branch("n_merged_strips_y_lv2",&m_n_merged_strips_y_lv2);
    get_branch("n_lv1signal_x_lv2",&m_n_lv1signal_x_lv2);
    get_branch("n_lv1signal_y_lv2",&m_n_lv1signal_y_lv2);
    get_branch("lv1signal_id_x_lv2",&m_lv1signal_id_x_lv2);
    get_branch("lv1signal_id_y_lv2",&m_lv1signal_id_y_lv2);
    get_branch("nhit_lv3",&m_nhit_lv3);
    get_branch("detid_lv3",&m_detid_lv3);
    get_branch("epi_lv3",&m_epi_lv3);
    get_branch("epi_x_lv3",&m_epi_x_lv3);
    get_branch("epi_y_lv3",&m_epi_y_lv3);
    get_branch("pos_x_lv3",&m_pos_x_lv3);
    get_branch("pos_y_lv3",&m_pos_y_lv3);
    get_branch("pos_z_lv3",&m_pos_z_lv3);
    get_branch("width_x_lv3",&m_width_x_lv3);
    get_branch("width_y_lv3",&m_width_y_lv3);
    get_branch("width_z_lv3",&m_width_z_lv3);
    get_branch("n_lv2signal_x_lv3",&m_n_lv2signal_x_lv3);
    get_branch("n_lv2signal_y_lv3",&m_n_lv2signal_y_lv3);
    get_branch("lv2signal_id_x_lv3",&m_lv2signal_id_x_lv3);
    get_branch("lv2signal_id_y_lv3",&m_lv2signal_id_y_lv3);
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

