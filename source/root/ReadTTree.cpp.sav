/**
   @file ReadTTree.cpp
   @author Goro Yabu
   @date 2019/06/21 v2.1
   @version 2.1
**/
#include "ReadTTree.hpp"

using namespace anlcross;
using namespace std;

ReadTTree::ReadTTree() :
    ANLModuleBase("ReadTTree", "2.1"),
    m_file(nullptr), m_file_name("in.root"), m_tree_name("TTree")
{
}
ReadTTree::ReadTTree(std::string name, std::string version, std::string tree) :
    ANLModuleBase(name, version),
    m_file(nullptr), m_file_name("in.root"), m_tree_name(tree)
{
}
void ReadTTree::mod_init(int &status)
{
    status = ANL_OK;
    
    m_file = OpenTFile(m_file_name, "read");
    if( !m_file ) status = ANL_NG;

    if( status == ANL_OK )
	status = GetTTreeReader(m_tree_name, m_file, &m_tree_reader);

    m_current_entry = -1;
    m_max_entry = m_tree_reader.GetTree()->GetEntries();
    
    if( status == ANL_OK )
	status = set_read_branch();
}
void ReadTTree::mod_com(int &status)
{
    status = ANL_OK;
    com_cli::read_value<string>("Input ROOT TFile Name ?", &m_file_name);
    com_cli::read_value<string>("           TTree Name ?", &m_tree_name);
}
void ReadTTree::mod_ana(int &status)
{
    status = ANL_OK;
    ++m_current_entry;
    if(m_current_entry>=m_max_entry){
	status = ANL_QUIT;
    }else{
	m_tree_reader.GetTree()->GetEntry(m_current_entry);
	status = ANL_OK;
    }
}
void ReadTTree::mod_exit(int &status)
{
    status = ANL_OK;
    if( m_file!=nullptr ) m_file->Close();
}
int ReadTTree::set_read_branch()
{
    return ANL_OK;
}
/*
int ReadTTree::put_branch_value()
{
    return ANL_OK;
}
*/
TFile * ReadTTree::OpenTFile(std::string name, std::string option)
{
    TFile * file = new TFile(name.c_str(), option.c_str());
    if( !file || file->IsZombie() ) return nullptr;
    cout << "ReadTTree::OpenTFile ";
    cout << name << endl;
    return file;
}
int ReadTTree::GetTTreeReader(std::string name, TFile * file, TTreeReader* reader)
{
    reader->SetTree((TTree*)file->Get(name.c_str()));
    if( reader->IsZombie() ) return ANL_NG;
    cout << "ReadTTree::GetTTreeReader ";
    cout << name << endl;
    return ANL_OK;
}
/*
int ReadTTree::IsValidValue(ROOT::Internal::TTreeReaderValueBase& value)
{
   if(value.GetSetupStatus() < 0) {
       cerr << "Error " << value.GetSetupStatus()
	    << "setting up reader for " << value.GetBranchName() << endl;
       return ANL_NG;
   }
   return ANL_OK;
}
*/
