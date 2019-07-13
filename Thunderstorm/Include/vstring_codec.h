#ifndef _VSTRING_CODEC_H_
#define _VSTRING_CODEC_H_

class VSTRING_CODEC
{
public:
	VSTRING_CODEC(){};
	virtual ~VSTRING_CODEC(){};
	virtual uint32_t GetNum(){return 0;};
	virtual uint32_t Convert(const char * pString){return 0;};
	virtual uint32_t Convert(const char * pString, long iLen) {return 0;};
	virtual char * Convert(uint32_t code){return nullptr;};
	virtual void VariableChanged() {};
};

#endif