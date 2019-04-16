/**
   @date 2018/11/26
**/
#ifndef DSReadDatabase_hpp
#define DSReadDatabase_hpp

#include <utility>
#include <map>
#include <vector>

#include <TSpline.h>

#include "ANLModuleBase.hpp"
//#include "BnkROOT.hpp"
#include "GXTTreeIO.hpp"

class DSReadDatabase : public anlcross::ANLModuleBase
{
private:
    using pairmap = std::map< std::pair<int, int>, std::pair<int, int> >;
    using entrymap = std::map< std::pair<int, int>, int >;

    class stripinfo
    {
    public:
	stripinfo() : calfunc(nullptr) {}
	~stripinfo() {}
	int asicid, asicch;
	int detid, stripid;
	float posx, posy, posz;
	float widthx, widthy, widthz;
	float ethre;
	TSpline3 * calfunc;
    };

    std::string m_infile_name;
    std::string m_intree_name;

    TFile * mInFile;
    TTree * mDatabase;
    pairmap mStripMap;
    entrymap mEntryIndex;
    std::vector<stripinfo*> mDatabaseList;
    
    int m_asicid, m_asicch;
    int m_detid, m_stripid;
    float m_posx, m_posy, m_posz;
    float m_widthx, m_widthy, m_widthz;
    float m_ethre;
    TSpline3 * m_calfunc;

public:
    DSReadDatabase();
    ~DSReadDatabase() {}

    //void mod_startup(int &status);
    void mod_init(int &status);
    void mod_com(int &status);
    //void mod_his(int &status);
    void mod_bgnrun(int &status);
    void mod_ana(int &status);
    //void mod_ana(int&, int&, int &status);
    void mod_endrun(int &status);
    void mod_exit(int &status);

    int find_strip(int asicid, int asicch, int* detid, int* stripid);
    int find_index(int detid, int stripid, int* index);
    int get_posx(int detid, int stripid, float* pos);
    int get_posy(int detid, int stripid, float* pos);
    int get_posz(int detid, int stripid, float* pos);
    int get_widthx(int detid, int stripid, float* width);
    int get_widthy(int detid, int stripid, float* width);
    int get_widthz(int detid, int stripid, float* width);
    int get_ethre(int detid, int stripid, float* thre);
    int get_epi(int asicid, int asicch, float pha, float* epi);
    //float get_epi(int detid, int stripid, int pha);

    TTree * GetTree(){ return mDatabase; }
    int GetX(int detid, int stripid, float* pos){ return get_posx(detid, stripid, pos); }
    int GetY(int detid, int stripid, float* pos){ return get_posy(detid, stripid, pos); }
    int GetWidthX(int detid, int stripid, float* pos){ return get_widthx(detid, stripid, pos); }
    int GetWidthY(int detid, int stripid, float* pos){ return get_widthy(detid, stripid, pos); }
    int GetEthre(int detid, int stripid, float* thre){ return get_ethre(detid, stripid, thre); }
    int GetEPI(int asicid, int asicch, float pha, float* epi){ return get_epi(asicid, asicch, pha, epi); }
    int GetBadch(int asicid, int asicch, int* badch) {return anlcross::ANL_NG;}
    //int FindStrip(int asicid, int asicch, int* detid, int* stripid) { return find_strip(asicid, asicch, detid, stripid); }
    int FindStrip(int asicid, int asicch, int* detid, int* stripid);
    //static DSReadDatabase* get(){ return mPtr;}
    bool IsXside(int detid, int stripid)
    {
	float width;
	GetWidthY(detid, stripid, &width);
	if( width == -1 ) return true;
	else return false;
    }
};
#endif