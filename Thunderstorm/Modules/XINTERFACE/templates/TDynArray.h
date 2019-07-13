#ifndef TDYNLIST_HPP
#define TDYNLIST_HPP

#include <assert.h>

#define DYNAMIC_ARRAY_BLOCK_SIZE	100

template<class T> class TDynamicArray
{
	typedef TDynamicArray<T> TThis;
	T *		m_pBuffer;
	uint32_t	m_dwBlockSize;
	uint32_t	m_dwSize;
	uint32_t	m_dwReservSize;

public:
	// constructor & destructor
		// empty constructor
	TDynamicArray()
	{
		m_pBuffer = null;
		m_dwBlockSize = DYNAMIC_ARRAY_BLOCK_SIZE;
		m_dwSize = m_dwReservSize = 0;
	}
		// constructor with block size setting
	TDynamicArray(uint32_t nBlockSize)
	{
		m_pBuffer = null;
		m_dwBlockSize = nBlockSize;
		m_dwSize = m_dwReservSize = 0;
	}
		// constructor by doubling
	TDynamicArray( TDynamicArray & da )
	{
		uint32_t q = da.Getsize();
		ResizeBuffer(q);
		for(uint32_t n=0; n<q; n++)
			m_pBuffer[n] = da[n];
		m_dwSize = q;
	}
	~TDynamicArray() {ReleaseAll();}

	// release function
	void	ReleaseAll()
	{
		if( m_pBuffer!= nullptr ) delete[] m_pBuffer;	m_pBuffer = null;
		m_dwSize = m_dwReservSize = 0;
	}

	// block size functions
	uint32_t	GetBlocksize() {return m_dwBlockSize;}
	void	SetBlockSize(uint32_t dwNewBlockSize)
	{
		if(dwNewBlockSize>0) m_dwBlockSize=dwNewBlockSize;
	}

	// resize function
	uint32_t	Getsize() {return m_dwSize;}
	void	ResizeBuffer(uint32_t dwNewSize)
	{
		uint32_t dwNeedReserv = ((dwNewSize-1)/m_dwBlockSize+1)*m_dwBlockSize;
		if(dwNeedReserv==m_dwReservSize) return; // same size
		T * pOldBuf = m_pBuffer;
		m_pBuffer = new T[dwNeedReserv];
		assert(m_pBuffer);
		if(pOldBuf) {
			//memcpy(m_pBuffer,pOldBuf,sizeof(T)*m_dwSize);
			for(uint32_t n=0; n<m_dwSize; n++) m_pBuffer[n] = pOldBuf[n];
			delete[] pOldBuf;
		}
		m_dwReservSize = dwNeedReserv;
	}

	// add & delete functions
	long	SimpleAdd(T one)
	{
		ResizeBuffer(m_dwSize+1);
		m_pBuffer[m_dwSize] = one;
		m_dwSize++;
		return m_dwSize-1;
	}
	long	Add(T & one)
	{
		ResizeBuffer(m_dwSize+1);
		m_pBuffer[m_dwSize] = one;
		m_dwSize++;
		return m_dwSize-1;
	}
	void	Insert(T & one, int idx)
	{
		if(idx<0 || idx>=(int)Getsize()) return; // out of rang
		ResizeBuffer(m_dwSize+1);
		for(int n=m_dwSize; n>idx; n--) m_pBuffer[n] = m_pBuffer[n-1];
		m_pBuffer[idx] = one;
		m_dwSize++;
	}
	T *		Add(T * list, int nSize) // for char * access
	{
		if(list== nullptr) return nullptr;
		ResizeBuffer(m_dwSize+nSize);
		for(int n=0; n<nSize; n++)	m_pBuffer[m_dwSize+n] = list[n];
		m_dwSize += nSize;
		return &m_pBuffer[m_dwSize-nSize];
	}
	void	Delete(T & one) {Delete(Find(one));}
	void	SimpleDelete(T one) {Delete(Find(one));}
	void	Delete(int n, int q=1)
	{
		if(n<0 || n>=(int)m_dwSize) return; // out of range
		m_dwSize -= q;
		for(int i=n; i<(int)m_dwSize; i++)	m_pBuffer[i] = m_pBuffer[i+q];
		ResizeBuffer(m_dwSize);
	}
	void	Replace(int idx, T & one)
	{
		if(idx<0 || idx>=(int)m_dwSize) return; // out of range
		m_pBuffer[i] = one;
	}

	// find function
	int		SimpleFind(T one){return Find(one);}
	int		Find(T & one)
	{
		for(uint32_t n=0; n<m_dwSize; n++)	if( m_pBuffer[n] == one ) return n;
		return -1;
	}

	// access operators
	//T * operator &() {return m_pBuffer;}
	T & operator [](int idx) {return m_pBuffer[idx];}
	T & operator [](long idx) {return m_pBuffer[idx];}
	T & operator [](uint32_t idx) {return m_pBuffer[idx];}
	TThis & operator =(TThis & srcArray)
	{
		ReleaseAll();
		uint32_t q = srcArray.Getsize();
		ResizeBuffer(q);
		for(uint32_t n=0; n<q; n++) m_pBuffer[n] = srcArray[n];
		m_dwSize = q;
		return *this;
	}

	// access functions
	uint32_t GetIndex(T * pT)
	{
		if( (uint32_t)pT<(uint32_t)m_pBuffer || (uint32_t)pT>(uint32_t)&m_pBuffer[m_dwSize-1] ) return -1;
		return ((uint32_t)pT-(uint32_t)m_pBuffer)/sizeof(T);
	}
};

#endif
