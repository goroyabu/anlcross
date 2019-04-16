/**
   @file bnk.hpp
   @author Goro Yabu
   @date 2018/11/23
   @version 1.0
**/
#ifndef bnk_hpp
#define bnk_hpp

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>

/**
   @namespace bnk
**/
namespace bnk
{
    const int BNK_OK = 0;
    const int BNK_NG = -1;
    const int BNK_TRUE = 1;
    const int BNK_FALSE = 0;

    template<typename T>
    std::string value_type(){ return "template"; }
    //template<> std::string value_type<int>(){ return "int"; }
    //template<> std::string value_type<float>(){ return "float"; }
    //template<> std::string value_type<double>(){ return "double"; }
    
    class databank_base
    {
    protected:
	databank_base(const std::string name, const int size = 1)
	    : m_name(name), m_alloc_size(size), m_used_size(0), m_attribute(0),
	      m_file_descripter(""), m_num_put(0), m_num_get(0) {}
	std::string m_name;
	int m_alloc_size;
	int m_used_size;
	int m_attribute;
	std::string m_file_descripter;
	bool m_save_file;
	double m_num_put;
	double m_num_get;
	std::string m_type;
	
    public:
	std::string GetName() const { return m_name; }
	int GetAllocSize() const { return m_alloc_size; }
	int GetUsedSize() const { return m_used_size; }
	int GetAttribute() const { return m_attribute; }
	std::string GetFileIO() const { return m_file_descripter; }
	double GetNumPut() const { return m_num_put; }
	double GetNumGet() const { return m_num_get; }

	std::string Key() const { return GetName(); }
	
	virtual void List() = 0;
	virtual void Export() = 0;
	virtual std::string ClassName() { return "databank_base"; }
	virtual std::string ValueType() const { return "template"; }
    };
    
    /**
       @class databank
    **/
    template<typename T> class databank : public databank_base
    {
    protected:
	std::vector<T> m_array;
	
    public:
	databank(const std::string name, int size = 1)
	    : databank_base(name, size)
	{
	    if(size<0) size = 1; m_array.resize(size);
	}
	~databank() {}

	int Put(const T& in)
	{
	    m_array[0] = in; m_used_size = 1;
	    ++m_num_put; return BNK_OK;
	}
	int Put(const std::vector<T>& vec, int begin, int end)
	{
	    if(end<begin || GetAllocSize()<end-begin || vec.size()<end-begin) return BNK_NG;
	    m_array.clear();
	    for(int i=begin; i<end; ++i) m_array.push_back(vec[i]);
	    m_used_size = end-begin; ++m_num_put;
	    return BNK_OK;
	}

	int Get(T* out)
	{
	    *out = m_array[0]; ++m_num_get;
	    return BNK_OK;
	} 
        int Get(std::vector<T>* out, int begin, int end)
	{
	    if(end<begin || GetUsedSize()<end-begin) return BNK_NG;
	    out->clear();
	    for(int i=begin; i<end; ++i) out->push_back(m_array[i]);
	    ++m_num_get;
	    return BNK_OK;
	}
	
	virtual void List()
	{
	    using namespace std;
	    cout << setw(32) << m_name << setw(8) << m_alloc_size;
	    cout << setw(8) << m_used_size;
	    cout << setw(10) << m_num_put << setw(10) << m_num_get;
	    cout << endl;
	}
	virtual void Export()
	{
	    using namespace std;
	    cout << setw(20) << m_name << "[";
	    cout << setw(3) << m_alloc_size << "] (";
	    for(int i=0; i<m_used_size; ++i){
		cout << m_array[i];
		if(i < m_used_size-1) cout << ",";
	    }
	    cout << ")" << endl;
	}
	virtual std::string ClassName() { return "databank"; }
	virtual std::string ValueType() const { return value_type<T>(); }
    };

    int add_bank(databank_base* bank);
    databank_base* get_bank(int index); 
    
    int bnk_init();
    int bnk_end();
    int bnk_list();
    int bnk_export_all();
    int bnk_connect(std::string server);
    int bnk_server(int port);
    int bnk_ndef();
    
    /** @brief Return -1 if NOT defined. **/
    int bnk_is_def(const std::string key);

    /** @brief Define a new buffer. **/
    template<typename T>
    int bnk_def(const std::string key, const int size = 1)
    {
	if( bnk_is_def(key) == BNK_OK ) return BNK_NG;
	add_bank( new databank<T>(key, size) );
	return BNK_OK;
    }
    
    /** @brief Find index of key. **/
    int bnk_key(const std::string key, int* index);

    int bnk_equiv(const std::string new_key, const std::string old_key);

    /** @brief Put data. **/
    template<typename T> int bnk_put(const std::string key, const T& value)
    {
	int index; if( bnk_key(key, &index) == BNK_NG ) return BNK_NG;
	if( get_bank(index)->GetAllocSize()!=1 ) return BNK_NG;
	((databank<T>*)get_bank(index))->Put(value);
	return BNK_OK;
    }
    template<typename T> int bnk_put(const std::string key, const std::vector<T>& in, int begin, int end)
    {
	int index; if( bnk_key(key, &index) == BNK_NG ) return BNK_NG;
	int size = end-begin;
	if( get_bank(index)->GetAllocSize() < size )
	    size = get_bank(index)->GetAllocSize();
	((databank<T>*)get_bank(index))->Put(in, begin, end);
	return BNK_OK;
    }

    //modify on 2019/03/19
    template<typename T> T bnk_get(const std::string key)
    {
	int index;
        if( bnk_key(key, &index) == BNK_NG ) return 0;
	if( get_bank(index)->GetAllocSize()!=1 ) return 0;
	T out; if( ((databank<T>*)get_bank(index))->Get(&out) == BNK_NG ) return 0;
	return out;
    }
    template<typename T> int bnk_get(const std::string key, std::vector<T>* out, int begin, int end)
    {
	int index;
	if( bnk_key(key, &index) == BNK_NG ) return BNK_NG;
	if( end<begin || get_bank(index)->GetUsedSize()<end-begin ) end = begin;
	return ((databank<T>*)get_bank(index))->Get(out, begin, end);
    }    
    
    /** **/
    int bnk_net_update(const int index);

    /** **/
    int bnk_export(const std::string key);
};
#endif
