/**
   @file ReadTTree.cpp
   @author Goro Yabu
   @date 2019/04/17
   @version 1.0
**/
#include "ReadTTree.hpp"

using namespace anlcross;
using namespace std;

ReadTTree::ReadTTree() :
    ANLModuleBase("ReadTTree", "1.0"),
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
    if( !m_tree_reader.Next() ) status = ANL_QUIT;
    else status = put_branch_value();
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
int ReadTTree::put_branch_value()
{
    return ANL_OK;
}
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
int ReadTTree::IsValidValue(ROOT::Internal::TTreeReaderValueBase& value)
{
   if(value.GetSetupStatus() < 0) {
       cerr << "Error " << value.GetSetupStatus()
	    << "setting up reader for " << value.GetBranchName() << endl;
       return ANL_NG;
   }
   return ANL_OK;
}
