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
int WriteHittree::set_write_branch()
{
    define_branch(            "livetime",            &m_livetime,
                            "livetime/i");
    define_branch(            "unixtime",            &m_unixtime,
                            "unixtime/i");
    define_branch(        "ext2ti_lower",        &m_ext2ti_lower,
                        "ext2ti_lower/i");
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

