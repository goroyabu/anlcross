/**
  @file ReadEventtree.cpp
  @author 
  @date               
  @version 1.1
**/
#include "ReadEventtree.hpp"

using namespace anlcross;
using namespace std;

ReadEventtree::ReadEventtree() :
    ReadTTree("ReadEventtree", "1.1", "eventtree")
    /*
    m_livetime            (m_tree_reader,         "livetime"),
    m_unixtime            (m_tree_reader,         "unixtime"),
    m_ti_upper            (m_tree_reader,         "ti_upper"),
    m_ti_lower            (m_tree_reader,         "ti_lower"),
    m_ext1ti_upper        (m_tree_reader,     "ext1ti_upper"),
    m_ext1ti_lower        (m_tree_reader,     "ext1ti_lower"),
    m_ext2ti_upper        (m_tree_reader,     "ext2ti_upper"),
    m_ext2ti_lower        (m_tree_reader,     "ext2ti_lower"),
    m_hitnum0             (m_tree_reader,          "hitnum0"),
    m_cmn0                (m_tree_reader,             "cmn0"),
    m_index0              (m_tree_reader,           "index0"),
    m_adc0                (m_tree_reader,             "adc0"),
    m_hitnum1             (m_tree_reader,          "hitnum1"),
    m_cmn1                (m_tree_reader,             "cmn1"),
    m_index1              (m_tree_reader,           "index1"),
    m_adc1                (m_tree_reader,             "adc1"),
    m_hitnum2             (m_tree_reader,          "hitnum2"),
    m_cmn2                (m_tree_reader,             "cmn2"),
    m_index2              (m_tree_reader,           "index2"),
    m_adc2                (m_tree_reader,             "adc2"),
    m_hitnum3             (m_tree_reader,          "hitnum3"),
    m_cmn3                (m_tree_reader,             "cmn3"),
    m_index3              (m_tree_reader,           "index3"),
    m_adc3                (m_tree_reader,             "adc3"),
    m_hitnum4             (m_tree_reader,          "hitnum4"),
    m_cmn4                (m_tree_reader,             "cmn4"),
    m_index4              (m_tree_reader,           "index4"),
    m_adc4                (m_tree_reader,             "adc4"),
    m_hitnum5             (m_tree_reader,          "hitnum5"),
    m_cmn5                (m_tree_reader,             "cmn5"),
    m_index5              (m_tree_reader,           "index5"),
    m_adc5                (m_tree_reader,             "adc5"),
    m_hitnum6             (m_tree_reader,          "hitnum6"),
    m_cmn6                (m_tree_reader,             "cmn6"),
    m_index6              (m_tree_reader,           "index6"),
    m_adc6                (m_tree_reader,             "adc6"),
    m_hitnum7             (m_tree_reader,          "hitnum7"),
    m_cmn7                (m_tree_reader,             "cmn7"),
    m_index7              (m_tree_reader,           "index7"),
    m_adc7                (m_tree_reader,             "adc7")
    */
{
}
int ReadEventtree::set_read_branch()
{
    read_branch<unsigned int>(                  "livetime");
    read_branch<unsigned int>(                  "unixtime");
    read_branch<unsigned int>(                  "ti_upper");
    read_branch<unsigned int>(                  "ti_lower");
    read_branch<unsigned int>(              "ext1ti_upper");
    read_branch<unsigned int>(              "ext1ti_lower");
    read_branch<unsigned int>(              "ext2ti_upper");
    read_branch<unsigned int>(              "ext2ti_lower");
    read_branch<unsigned short int>(                   "hitnum0");
    read_branch<unsigned short int>(                      "cmn0");
    read_branch_array<unsigned short int>(              "index0",   64);
    read_branch_array<unsigned short int>(                "adc0",   64);
    read_branch<unsigned short int>(                   "hitnum1");
    read_branch<unsigned short int>(                      "cmn1");
    read_branch_array<unsigned short int>(              "index1",   64);
    read_branch_array<unsigned short int>(                "adc1",   64);
    read_branch<unsigned short int>(                   "hitnum2");
    read_branch<unsigned short int>(                      "cmn2");
    read_branch_array<unsigned short int>(              "index2",   64);
    read_branch_array<unsigned short int>(                "adc2",   64);
    read_branch<unsigned short int>(                   "hitnum3");
    read_branch<unsigned short int>(                      "cmn3");
    read_branch_array<unsigned short int>(              "index3",   64);
    read_branch_array<unsigned short int>(                "adc3",   64);
    read_branch<unsigned short int>(                   "hitnum4");
    read_branch<unsigned short int>(                      "cmn4");
    read_branch_array<unsigned short int>(              "index4",   64);
    read_branch_array<unsigned short int>(                "adc4",   64);
    read_branch<unsigned short int>(                   "hitnum5");
    read_branch<unsigned short int>(                      "cmn5");
    read_branch_array<unsigned short int>(              "index5",   64);
    read_branch_array<unsigned short int>(                "adc5",   64);
    read_branch<unsigned short int>(                   "hitnum6");
    read_branch<unsigned short int>(                      "cmn6");
    read_branch_array<unsigned short int>(              "index6",   64);
    read_branch_array<unsigned short int>(                "adc6",   64);
    read_branch<unsigned short int>(                   "hitnum7");
    read_branch<unsigned short int>(                      "cmn7");
    read_branch_array<unsigned short int>(              "index7",   64);
    read_branch_array<unsigned short int>(                "adc7",   64);

    return ANL_OK;
}
int ReadEventtree::put_branch_value()
{
    /*
    put_branch(                 m_livetime);
    put_branch(                 m_unixtime);
    put_branch(                 m_ti_upper);
    put_branch(                 m_ti_lower);
    put_branch(             m_ext1ti_upper);
    put_branch(             m_ext1ti_lower);
    put_branch(             m_ext2ti_upper);
    put_branch(             m_ext2ti_lower);
    put_branch(                  m_hitnum0);
    put_branch(                     m_cmn0);
    put_branch_array(              m_index0,             *m_hitnum0);
    put_branch_array(                m_adc0,             *m_hitnum0);
    put_branch(                  m_hitnum1);
    put_branch(                     m_cmn1);
    put_branch_array(              m_index1,             *m_hitnum1);
    put_branch_array(                m_adc1,             *m_hitnum1);
    put_branch(                  m_hitnum2);
    put_branch(                     m_cmn2);
    put_branch_array(              m_index2,             *m_hitnum2);
    put_branch_array(                m_adc2,             *m_hitnum2);
    put_branch(                  m_hitnum3);
    put_branch(                     m_cmn3);
    put_branch_array(              m_index3,             *m_hitnum3);
    put_branch_array(                m_adc3,             *m_hitnum3);
    put_branch(                  m_hitnum4);
    put_branch(                     m_cmn4);
    put_branch_array(              m_index4,             *m_hitnum4);
    put_branch_array(                m_adc4,             *m_hitnum4);
    put_branch(                  m_hitnum5);
    put_branch(                     m_cmn5);
    put_branch_array(              m_index5,             *m_hitnum5);
    put_branch_array(                m_adc5,             *m_hitnum5);
    put_branch(                  m_hitnum6);
    put_branch(                     m_cmn6);
    put_branch_array(              m_index6,             *m_hitnum6);
    put_branch_array(                m_adc6,             *m_hitnum6);
    put_branch(                  m_hitnum7);
    put_branch(                     m_cmn7);
    put_branch_array(              m_index7,             *m_hitnum7);
    put_branch_array(                m_adc7,             *m_hitnum7);
    */
    return ANL_OK;
}

