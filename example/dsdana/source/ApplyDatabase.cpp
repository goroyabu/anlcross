/**
   @file ApplyDatabase.cpp
   @author Goro Yabu
   @date 2018/11/27
   @date 2019/04/16 v1.1 Change this module name to ApplyDatabase
   @version 1.1
**/
#include "ApplyDatabase.hpp"
using namespace anlcross;
ApplyDatabase::ApplyDatabase() : ANLModuleBase("ApplyDatabase", "1.1"),
				 mDatabase(nullptr), mRandom(nullptr),
				 m_histall(nullptr), m_spectall(nullptr),
				 m_multi_hist(nullptr)
{  
}
void ApplyDatabase::mod_init(int &status)
{
    status = ANL_OK;

    mRandom = new TRandom();
    mRandom->SetSeed(time(NULL));

    mDatabase = (ReadDatabase*)get_module("ReadDatabase");
    if( !mDatabase || mDatabase->mod_name()!="ReadDatabase") status = ANL_NG;
    
    this->bnkDefAll();

    evs::EvsDef("0 PHA signal");
    evs::EvsDef("1Pt-0Al PHA signals");
    evs::EvsDef("0Pt-1Al PHA signals");
    evs::EvsDef("1Pt-1Al PHA signals");
    evs::EvsDef("2Pt-1Al PHA signals");
    evs::EvsDef("1Pt-2Al PHA signals");
    evs::EvsDef("2Pt-2Al PHA signals");
    evs::EvsDef("over 3 PHA signals");

    status = ANL_OK;
    
    std::cout << std::endl;
}
void ApplyDatabase::mod_his(int &status)
{
    m_histall = new TH2D("histall_lv1", "histall;stripid;pha", 256, -0.5, 255.5, 1000, -10.5, 989.5);
    m_spectall = new TH2D("spectall_lv1", "spectall;stripid;epi", 256, -0.5, 255.5, 1000, -10.25, 489.75);
    m_multi_hist = new TH2D("multipli_lv1", "multiplicity lv1;nsignal_x_lv1;nsignal_y_lv1;", 50, -0.5, 49.5, 50, -0.5, 49.5);
    status = ANL_OK;
}
void ApplyDatabase::mod_com(int &status)
{
    //com_cli::read_value<std::string>("Input file name", &m_infile_name);
    //com_cli::read_value<std::string>("Output file name", &m_outfile_name);
    //com_cli::ask_yesno("Output Tree ?", &m_save_branch);
    
    //random mode
    status = ANL_OK;
}
void ApplyDatabase::mod_ana(int &status)
{
    using namespace std;
    status = ANL_OK;
    /*
    if( TTreeFirstOwn(m_intree_name, module_name) == GX_OK ){
        if( TTreeNext( m_intree_name ) == GX_NG ) status = ANL_QUIT;
    }
    */
    if( status == ANL_OK ){
	this->clearVectorAll();
	this->bnkGetAll();
	
	for(int iasic = 0; iasic < m_nasic; iasic++){
	    int hitnum = mvec_hitnum[iasic];
	  
	    //cout << "#######" << endl;
	    //cout << mvec_hitnum[iasic] << endl;
	    //cout << mvec_adc[iasic].size() << endl;
	    //cout << mvec_index[iasic].size() << endl;
	    
	    for(int isignal = 0; isignal < hitnum; isignal++){		
		int asicid = iasic;
		int asicch = mvec_index[iasic][isignal];
		float pha = mvec_adc[iasic][isignal] - mvec_cmn[iasic] + getRandom();

		int detid, stripid;
		if( mDatabase->FindStrip(asicid, asicch, &detid, &stripid) == ANL_NG ) continue;
		if( this->isBadch(asicid, asicch) == ANL_YES ) continue;
		
		float epi;
		mDatabase->GetEPI(asicid, asicch, pha, &epi);
		m_histall->Fill(stripid, pha);
		m_spectall->Fill(stripid, epi);
		
		if( this->isXside(asicid, asicch) == ANL_YES ){
		    m_detid_x_lv1.emplace_back(detid);
		    //m_stripid_x_lv1.push_back(stripid);
		    m_stripid_x_lv1.emplace_back(stripid);
		    //m_epi_x_lv1.push_back(epi);
		    m_epi_x_lv1.emplace_back(epi);
		    m_nsignal_x_lv1++;
		}else{
		    m_detid_y_lv1.emplace_back(detid);
		    //m_stripid_y_lv1.push_back(stripid);
		    m_stripid_y_lv1.emplace_back(stripid);
		    //m_epi_y_lv1.push_back(epi);
		    m_epi_y_lv1.emplace_back(epi);
		    m_nsignal_y_lv1++;
		}
		
		//if(m_nsignal_x_lv1>0) cout << epi << " " << m_epi_x_lv1[0] << endl;
	    }
	}
	
	m_multi_hist->Fill(m_nsignal_x_lv1, m_nsignal_y_lv1);
	//cout << m_nsignal_x_lv1 << endl;
	if(m_nsignal_x_lv1==0 && m_nsignal_y_lv1==0) evs::EvsSet("0 PHA signals");
	else if(m_nsignal_x_lv1==1 && m_nsignal_y_lv1==0) evs::EvsSet("1Pt-0Al PHA signals");
	else if(m_nsignal_x_lv1==0 && m_nsignal_y_lv1==1) evs::EvsSet("0Pt-1Al PHA signals");
	else if(m_nsignal_x_lv1==1 && m_nsignal_y_lv1==1) evs::EvsSet("1Pt-1Al PHA signals");
	else if(m_nsignal_x_lv1==2 && m_nsignal_y_lv1==1) evs::EvsSet("2Pt-1Al PHA signals");
	else if(m_nsignal_x_lv1==1 && m_nsignal_y_lv1==2) evs::EvsSet("1Pt-2Al PHA signals");
	else if(m_nsignal_x_lv1==2 && m_nsignal_y_lv1==2) evs::EvsSet("2Pt-2Al PHA signals");
	else evs::EvsSet("over 3 PHA signals");
	
	//evs::EvsAcm();

	if( this->bnkPutAll() ) status = ANL_SKIP;
	
    }
    
    /*
    if( TTreeLastOwn(m_outtree_name, module_name) == GX_OK ){
	TTreeFill( m_outtree_name );
    }
    */
}
void ApplyDatabase::mod_endrun(int &status)
{
    using namespace gxroot;
    
    //TFileCd(m_outfile_name);
    
    //TTreeWrite(m_outtree_name);
    m_histall->Write();
    m_spectall->Write();
    m_multi_hist->Write();
    mDatabase->GetTree()->Clone()->Write();
    
    status = ANL_OK;
}
void ApplyDatabase::mod_exit(int &status)
{
    //gxroot::TFileClose( m_infile_name );
    //gxroot::TFileClose( m_outfile_name );
    //mRandom->Delete();    
    status = ANL_OK;
    std::cout << std::endl;
}

int ApplyDatabase::bnkDefAll()
{

    using namespace bnk;
    using namespace std;

    m_nasic=0;
    while(true){
	if( bnk_is_def("hitnum"+to_string(m_nasic))==BNK_NG ) break;
	++m_nasic;
    }
    mvec_hitnum.resize(m_nasic);
    mvec_cmn.resize(m_nasic);
    mvec_adc.resize(m_nasic);
    mvec_index.resize(m_nasic);

    //using namespace gxroot;
    //mInFile = TFileOpen( m_infile_name, "read");
    //if(!mInFile) return ANL_NG;

    //mInTree = TTreeDef( m_intree_name, "read", module_name);
    //if(!mInTree) return ANL_NG;

    /*
    for(int i = 0; i < 8; ++i){
	mvec_adc[i].reserve(64);
	mvec_adc[i].resize(64);
	mvec_index[i].resize(64);
	ReadBranch( Form("hitnum%d", i), "s", 1);
	ReadBranch( Form("cmn%d", i), "s", 1);
	ReadBranch( Form("adc%d", i), "s", 64);
	ReadBranch( Form("index%d", i), "s", 64);	
    }
    */
    //mOutFile = TFileOpen( m_outfile_name, "recreate");
    //if(!mOutFile) return ANL_NG;

    //mOutTree = TTreeDef( m_outtree_name, "write", module_name);
    //if(!mOutTree) return ANL_NG;

    m_detid_x_lv1.reserve(128);
    m_detid_y_lv1.reserve(128);
    m_stripid_x_lv1.reserve(128);
    m_stripid_y_lv1.reserve(128);
    m_epi_x_lv1.reserve(128);
    m_epi_y_lv1.reserve(128);

    /*
    //CloneBranchValue("livetime", "i", m_intree_name, m_outtree_name);
    //CloneBranchValue("unixtime", "i", m_intree_name, m_outtree_name);
    MakeBranch("nsignal_x_lv1", "I", 1, "", m_save_branch);
    MakeBranch("nsignal_y_lv1", "I", 1, "", m_save_branch);
    MakeBranch("stripid_x_lv1", "I", 128, "nsignal_x_lv1", m_save_branch);
    MakeBranch("stripid_y_lv1", "I", 128, "nsignal_y_lv1", m_save_branch);
    MakeBranch("epi_x_lv1", "F", 128, "nsignal_x_lv1", m_save_branch);
    MakeBranch("epi_y_lv1", "F", 128, "nsignal_y_lv1", m_save_branch);
    */
    
    bnk_def<int>("nsignal_x_lv1", 1);
    bnk_def<int>("nsignal_y_lv1", 1);
    bnk_def<int>("detid_x_lv1", 128);
    bnk_def<int>("detid_y_lv1", 128);
    bnk_def<int>("stripid_x_lv1", 128);
    bnk_def<int>("stripid_y_lv1", 128);
    bnk_def<float>("epi_x_lv1", 128);
    bnk_def<float>("epi_y_lv1", 128);
    
    return ANL_OK;
}
int ApplyDatabase::bnkGetAll()
{
    using namespace bnk;
    using namespace std;

    //int index;
    //if(bnk_key("hitnum0", &index)==BNK_NG) cout << "no def" << endl;
    //m_nasic = 0;
    for(int i=0; i<8; ++i){
	mvec_hitnum[i] = bnk_get<unsigned short>("hitnum"+to_string(i));
	mvec_cmn[i] = bnk_get<unsigned short>("cmn"+to_string(i));	
	bnk_get<unsigned short>("adc"+to_string(i), &mvec_adc[i], 0, mvec_hitnum[i]);
	bnk_get<unsigned short>("index"+to_string(i), &mvec_index[i], 0, mvec_hitnum[i]);
	//++m_nasic;
     }
    
    /*
    using namespace gxroot;
    m_nasic = 0;
    int total_hitnum = 0;
    for(int i = 0; i < 8; ++i){
	GetValue( Form("hitnum%d", i), &mvec_hitnum[i]);
        GetValue( Form("cmn%d", i), &mvec_cmn[i]);
        GetArray( Form("adc%d", i), &mvec_adc[i], mvec_hitnum[i]);
        GetArray( Form("index%d", i), &mvec_index[i], mvec_hitnum[i]);
	m_nasic++;
	total_hitnum += mvec_hitnum[i];
    }
    //if(total_hitnum==0) evs::EvsSet("0 PHA signal");
    */
    return ANL_OK;
}
int ApplyDatabase::bnkPutAll()
{
    /*
    using namespace gxroot;
    PutValue("nsignal_x_lv1", m_nsignal_x_lv1);
    PutValue("nsignal_y_lv1", m_nsignal_y_lv1);
    PutArray("stripid_x_lv1", m_stripid_x_lv1, m_nsignal_x_lv1);
    PutArray("stripid_y_lv1", m_stripid_y_lv1, m_nsignal_y_lv1);
    PutArray("epi_x_lv1", m_epi_x_lv1, m_nsignal_x_lv1);
    PutArray("epi_y_lv1", m_epi_y_lv1, m_nsignal_y_lv1);
    
    m_multi_hist->Fill(m_nsignal_x_lv1, m_nsignal_y_lv1);
    
    if( m_nsignal_x_lv1 < 1 && m_nsignal_y_lv1 < 1 ) return ANL_SKIP;
    */

    using namespace bnk;
    using namespace std;

    //cout << m_epi_x_lv1[0] << endl;
    bnk_put<int>("nsignal_x_lv1", m_nsignal_x_lv1);
    bnk_put<int>("nsignal_y_lv1", m_nsignal_y_lv1);
    bnk_put<int>("detid_x_lv1", m_detid_x_lv1, 0, m_nsignal_x_lv1);
    bnk_put<int>("detid_y_lv1", m_detid_y_lv1, 0, m_nsignal_y_lv1);
    bnk_put<int>("stripid_x_lv1", m_stripid_x_lv1, 0, m_nsignal_x_lv1);
    bnk_put<int>("stripid_y_lv1", m_stripid_y_lv1, 0, m_nsignal_y_lv1);
    bnk_put<float>("epi_x_lv1", m_epi_x_lv1, 0, m_nsignal_x_lv1);
    bnk_put<float>("epi_y_lv1", m_epi_y_lv1, 0, m_nsignal_y_lv1);
    
    return ANL_OK;
}
int ApplyDatabase::clearVectorAll()
{
    
    mvec_hitnum.clear();
    mvec_cmn.clear();
    for(int i=0; i<8; ++i){
	mvec_adc[i].clear();
	mvec_index[i].clear();
    }
    
    m_nsignal_x_lv1 = 0;
    m_nsignal_y_lv1 = 0;

    m_detid_x_lv1.clear();
    m_detid_y_lv1.clear();
    m_stripid_x_lv1.clear();
    m_stripid_y_lv1.clear();
    m_epi_x_lv1.clear();
    m_epi_y_lv1.clear();
    
    return ANL_OK;
}
int ApplyDatabase::isBadch(int asicid, int asicch)
{
    int badch;
    if( mDatabase->GetBadch(asicid, asicch, &badch) == ANL_NG ) return ANL_NG;
    if( badch == 1 ) return ANL_YES;
    return ANL_NO;
}
int ApplyDatabase::isXside(int asicid, int asicch)
{
    if( 4 <= asicid%8 ) return ANL_NO;
    return ANL_YES;
}
float ApplyDatabase::getRandom(){
    return mRandom->Uniform(-0.5, 0.5);
}
