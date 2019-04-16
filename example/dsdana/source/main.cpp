/**
   @file main.cpp
   @author Goro Yabu
   @date 2018/12/03
   @date 2019/04/16 v1.1
**/
#include <ANLCross.hpp>

#include "ReadDatabase.hpp"
//#include "ReadROOTTree.hpp"
#include "ApplyDatabase.hpp"
//#include "MergeAdjacent.hpp"
//#include "MakeHit.hpp"
//#include "MakePhotonList.hpp"
//#include "WriteROOTTree.hpp"

int main()
{
    using namespace anlcross;
    
    add_module(new ReadDatabase());
    //add_module(new ReadROOTTree());
    add_module(new ApplyDatabase());
    //add_module(new MergeAdjacent());
    //add_module(new MakeHit());
    //add_module(new MakePhotonList());
    //add_module(new WriteROOTTree());
    
    anl_init();
    anl_body();
    
    return 0;
}
