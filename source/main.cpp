/**
   @file main.cpp
   @author Goro Yabu
   @date 2018/12/03
**/
#include <vector>

#include "evs.hpp"
#include "bnk.hpp"
//#include "GXTTreeIO.hpp"
#include "ANLModuleBase.hpp"
//#include "ANLFunc.hpp"
#include "ANLCross.hpp"

/*
#include "DSReadDatabase.hpp"
#include "DSDataProcessLv1.hpp"
#include "DSDataProcessLv2.hpp"
#include "DSDataProcessLv3.hpp"
#include "MakePhotonList.hpp"
*/
int main()
{
    using namespace anlcross;
    
    //ANLCross * anlcross = new ANLCross();
    
    std::vector<ANLModuleBase*> vec_module;

    /*
    AnlAdd(new DSReadDatabase());
    AnlAdd(new DSDataProcessLv1());
    AnlAdd(new DSDataProcessLv2());
    AnlAdd(new DSDataProcessLv3());
    AnlAdd(new MakePhotonList());
    */
    //anlcross->anl_body(vec_module);
    anl_init();
    anl_body();
    
    return 0;
}
