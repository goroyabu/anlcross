/**
   @file main.cpp
   @author Goro Yabu
   @date 2018/12/20
   @version 1.0
**/
#include "mkanlmodule.hpp"

using namespace std;

cmdline::parser get_parser()
{
    cmdline::parser p;
    //p.add<string>("modulename", 'n', "name of module", true, "USER");
    p.add<string>("author", 'a', "name of author", false, "USER");

    p.add("read_tree", 0, "Template for Reading ROOT TTree");
    p.add("write_tree", 0, "Template for Writing ROOT TTree");
    p.add("read_table", 0, "Template for Reading FITS Table");
    p.add("write_table", 0, "Template for Writing FITS Table");
    
    p.add("help", 'h', "print help");
    return p;
}
int print_error(std::string program, std::string message)
{
    cerr << program << ":Error: " << message << endl;
    return -1;
}
int main(int argc, char* argv[])
{
    cmdline::parser args = get_parser();

    if ( !args.parse(argc, argv) || args.exist("help") || args.rest().size()==0 ){
	cout << args.error_full() << args.usage();
	return 0;
    }

    string author = args.get<string>("author");
    vector<string> list = args.rest();//args.get<string>("modulename");
    //string module_name =

    /*
    for(auto module_name : list){
	//write_impl(module_name, author);
	//write_def(module_name, author);
    }
    */

    cout << read_tree() << endl;
    return 0;
}
