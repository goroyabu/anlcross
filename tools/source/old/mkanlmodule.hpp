/**
   @file mkanlmodule.hpp
   @author Goro Yabu
   @date 2018/12/20
   @version 1.0
**/
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <com_cli.hpp>
#include <cmdline.hpp>

std::string anlbase_def(std::string name, std::string author)
{
    using namespace std;
    //string outname = name + ".hpp";
    //ofstream ofs(outname);
    stringstream ss;

    ss << "/**" << endl;
    ss << "   @file " << name << ".hpp" << endl;
    ss << "   @author " << author << endl;
    ss << "   @date 2019/01/01" << endl;
    ss << "   @version 1.0" << endl;
    ss << "   @brief Write a brief description of this module here." << endl;
    ss << "**/" << endl;

    ss << "#ifndef " << name << "_hpp" << endl;
    ss << "#define " << name << "_hpp" << endl;
    ss << endl;
    ss << "#include \"ANLModuleBase.hpp\" " << endl;
    ss << "#include \"ANLCross.hpp\" " << endl;
    ss << endl;
    ss << "class " << name << " : public anlcross::ANLModuleBase" << endl;
    ss << "{" << endl;
    ss << "public:" << endl;
    ss << "    " << name << "();" << endl;
    ss << "    ~" << name << "();" << endl;
    ss << endl;
    ss << "    void mod_startup(int& status);" << endl;
    ss << "    void mod_init(int& status);" << endl;
    ss << "    void mod_his(int& status);" << endl;
    ss << "    void mod_com(int& status);" << endl;
    ss << "    void mod_bgnrun(int& status);" << endl;
    //ss << "    void mod_ana(int& nevent, int& eventid, int& status);" << endl;
    ss << "    void mod_ana(int& status);" << endl;
    ss << "    void mod_endrun(int& status);" << endl;
    ss << "    void mod_exit(int& status);" << endl;
    ss << "};" << endl;
    ss << "#endif" << endl;

    return ss.str();
}
std::string anlbase_impl(std::string name, std::string author)
{
    using namespace std;
    stringstream ss;

    ss << "/**" << endl;
    ss << "   @file " << name << ".cpp" << endl;
    ss << "   @author " << author << endl;
    ss << "   @date 2019/01/01" << endl;
    ss << "   @version 1.0" << endl;
    ss << "   @brief Write a brief description of this module here." << endl;
    ss << "**/" << endl;

    ss << "#include \"" << name << ".hpp\" " << endl;
    ss << "using namespace std;" << endl;
    ss << name << "::" << name << "() : ANLModuleBase(\"" << name << "\", \"1.0\")" << endl;
    ss << "{" << endl;
    ss << "}" << endl;
    ss << name << "::~" << name << "()" << endl;
    ss << "{" << endl;
    ss << "}" << endl;
    ss << "void " << name << "::mod_startup(int& status)" << endl;
    ss << "{" << endl;
    ss << "    status = anlcross::ANL_OK;" << endl;
    ss << "}" << endl;
    ss << "void " << name << "::mod_init(int& status)" << endl;
    ss << "{" << endl;
    ss << "    //e.g. Define Bnk, Branch" << endl;
    ss << "    status = anlcross::ANL_OK;" << endl;
    ss << "}" << endl;
    ss << "void " << name << "::mod_his(int& status)" << endl;
    ss << "{" << endl;
    ss << "    //e.g. Define Histogram" << endl;
    ss << "    status = anlcross::ANL_OK;" << endl;
    ss << "}" << endl;
    ss << "void " << name << "::mod_com(int& status)" << endl;
    ss << "{" << endl;
    ss << "    //e.g. Modify Parameters" << endl;
    ss << "    status = anlcross::ANL_OK;" << endl;
    ss << "}" << endl;
    ss << "void " << name << "::mod_bgnrun(int& status)" << endl;
    ss << "{" << endl;
    ss << "    status = anlcross::ANL_OK;" << endl;
    ss << "}" << endl;
    //ss << "void " << name << "::mod_ana(int& nevent, int& eventid, int& status)" << endl;
    //ss << "{" << endl;
    //ss << "}" << endl;
    ss << "void " << name << "::mod_ana(int& status)" << endl;
    ss << "{" << endl;
    ss << "    //Main Analysis" << endl;
    ss << "    status = anlcross::ANL_OK;" << endl;
    ss << "}" << endl;
    ss << "void " << name << "::mod_endrun(int& status)" << endl;
    ss << "{" << endl;
    ss << "    //e.g. TTree Write" << endl;
    ss << "    status = anlcross::ANL_OK;" << endl;
    ss << "}" << endl;
    ss << "void " << name << "::mod_exit(int& status)" << endl;
    ss << "{" << endl;
    ss << "    //e.g. TFile Close" << endl;
    ss << "    status = anlcross::ANL_OK;" << endl;
    ss << "}" << endl;

    return ss.str();
}
std::string read_tree()
{
    using namespace std;
    using namespace com_cli;
    stringstream ss;

    string tree= "MyTree";
    string author= "USER";
    read_value<string>("Tree Name ?", &tree);
    read_value<string>("Author Name ?", &author);

    struct branch_info
    {
	string name;
	string type;
	int size;
	bool isarray;
	bool isvariable;
	string sizerefbranch;
	
	branch_info(string _name, string _type)
	    : name(_name), type(_type), size(1),
	      isarray(false), isvariable(false), sizerefbranch("") {}
	branch_info(string _name, string _type, int _size)
	    : name(_name), type(_type), size(_size),
	      isarray(true), isvariable(false), sizerefbranch("") {}
	branch_info(string _name, string _type, int _size, string _sizerefbranch)
	    : name(_name), type(_type), size(_size),
	      isarray(true), isvariable(true), sizerefbranch(_sizerefbranch) {}
    };
    
    vector<branch_info> vbranch;
    while(true){
	string name;
	read_value<string>("New Branch Name ? (-1 to exit)", &name);
	if(name=="-1") break;
    }
    
    ss << "/**                   " << endl;
    ss << "  @file ReadMyTree.hpp" << endl;
    ss << "  @author Goro Yabu   " << endl;
    ss << "  @date 2019/04/17    " << endl;
    ss << "  @version 1.0        " << endl;
    ss << "**/                   " << endl;
    ss << "#ifndef ReadMyTree_hpp" << endl;
    ss << "#define ReadMyTree_hpp" << endl;
    ss << endl;
    ss << "#include <string>       " << endl;
    ss << "#include <iostream>     " << endl;
    ss << "#include <ReadTTree.hpp>" << endl;
    ss << endl;
    ss << "class ReadMyTree : public ReadTTree" << endl;
    ss << "{                                  " << endl;
    ss << "    TTreeReaderValue<unsigned int>   m_unixtime;" << endl;
    ss << "    TTreeReaderArray<unsigned short> m_adc0;" << endl;
    ss << endl;
    ss << "public:" << endl;
    ss << "    ReadMyTree();" << endl;
    ss << "    ~ReadMyTree(){}" << endl;
    ss << endl;
    ss << "    virtual int set_read_branch();" << endl;
    ss << "    virtual int put_branch_value();" << endl;
    ss << "};" << endl;
    ss << "#endif" << endl;

    return ss.str();
}
