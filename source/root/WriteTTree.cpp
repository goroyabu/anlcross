/**
   @file WriteTTree.cpp
   @author Goro Yabu
   @date 2019/04/18
   @version 1.0
**/
#include "WriteTTree.hpp"

using namespace anlcross;
using namespace std;

WriteTTree::WriteTTree() :
    ANLModuleBase("WriteTTree", "1.0"),
    m_file(nullptr), m_tree(nullptr),
    m_file_name("in.root"), m_tree_name("TTree"),
    
    m_livetime(0)
{
}
WriteTTree::WriteTTree(std::string name, std::string version) :
    ANLModuleBase(name, version),
    m_file(nullptr), m_tree(nullptr),
    m_file_name("in.root"), m_tree_name("TTree"),
    
    m_livetime(0)
{
}
void WriteTTree::mod_init(int &status)
{
    status = ANL_OK;
    
    m_file = OpenTFile(m_file_name, "recreate");
    if( !m_file ) status = ANL_NG;
    
    if( status == ANL_OK ){
	m_tree = new TTree(m_tree_name.c_str(), m_tree_name.c_str());
    }
    
    if( status == ANL_OK )
	status = set_write_branch();
}
void WriteTTree::mod_com(int &status)
{
    status = ANL_OK;
    com_cli::read_value<string>("Output ROOT TFile Name ?", &m_file_name);
    com_cli::read_value<string>("            TTree Name ?", &m_tree_name);
}
void WriteTTree::mod_ana(int &status)
{
    status = ANL_OK;
    //status = get_branch_value();
    int nbytes;
    if( status == ANL_OK ) nbytes = m_tree->Fill();
    if( nbytes<0 ) status = ANL_NG;
}
void WriteTTree::mod_exit(int &status)
{
    using namespace std;
    status = ANL_OK;
    if( m_file!=nullptr ){
	m_file->cd();
	m_tree->Write(); cout << " Write TTree " << m_tree->GetName() << endl;
	m_file->Close(); cout << " Close TFile " << m_file->GetName() << endl;
    }
}
int WriteTTree::set_write_branch()
{
    define_branch("livetime", &m_livetime, "livetime/i");
    define_branch("adc7", &m_adc7, "adc7[64]/s", 64);
    return ANL_OK;
}
int WriteTTree::get_branch_value()
{
    get_branch("livetime", &m_livetime);
    get_branch("adc7", &m_adc7);
    return ANL_OK;
}
TFile * WriteTTree::OpenTFile(std::string name, std::string option)
{
    TFile * file = new TFile(name.c_str(), option.c_str());
    if( !file || file->IsZombie() ) return nullptr;
    cout << "WriteTTree::OpenTFile ";
    cout << name << endl;
    return file;
}

    
