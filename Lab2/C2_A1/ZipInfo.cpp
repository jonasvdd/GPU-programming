#include <string>
#include <vector>
#include "ZipInfo.h"

typedef unsigned int	ui32;
typedef unsigned short	ui16;

struct ZipFileheader
{
	ui32 signature;
	ui16 version_made_by;
	ui16 version_needed;
	ui16 bitflags;
	ui16 comp_method;
	ui16 lastModFileTime;
	ui16 lastModFileDate;
	ui32 crc_32;
	ui32 comp_size;
	ui32 uncompr_size;
	ui16 fname_len;
	ui16 extra_field_len;
	ui16 fcomment_len;
	ui16 disk_num_start;
	ui16 internal_fattribute;
	ui32 external_fattribute;
	ui32 relative_offset;
	char* file_name;
	char* extra_field;
	char* file_comment;
};

namespace
{
#define ZIP_OK					0
#define ZIP_ERR_OPEN			1
#define ZIP_ERR_WRONG_FILE		2
#define ZIP_ERR_WRONG_HEADER	3

	class ZipFile
	{

	public:
		ZipFile() : m_FileName("") { }
		ZipFile(::std::string fn)  : m_FileName(fn) { }
		virtual					~ZipFile() { ResetContent(); }

		void					ResetContent(void);
		bool					OpenFile(void);

		inline ::std::string	GetFileName(void) const { return m_FileName; }
		inline void				SetFileName(::std::string fn) { m_FileName = fn; }
		int						GetFilesNumber(void) const { return m_FileAttributes.size(); }
		ZipFileheader *			GetFileAttributes(unsigned int);

	private:
		::std::string			m_FileName;
		::std::vector<ZipFileheader*> m_FileAttributes;

		void					ReadCentralDirectory(char * data,long len);
		int						ReadFileHeader(char * data, ZipFileheader * hdr);
		unsigned int			ReadValue(unsigned char * buf, int nbits);

	};

	void ZipFile::ResetContent(void)
	{
		for(int i=0;i<GetFilesNumber();i++)
		{
			delete(GetFileAttributes(i));
		}
		m_FileAttributes.clear();
		m_FileName="";

	}

	bool ZipFile::OpenFile(void)
	{
		//filename must be filled
		if(m_FileName=="")
		{
			return ZIP_ERR_OPEN;
		}

		//read all the file data
		FILE * fp;
		::std::string st_temp;

		fopen_s(&fp, m_FileName.c_str(),"rb");
		if(fp==NULL)
		{
			return ZIP_ERR_OPEN;
		}

		fseek(fp,0,SEEK_END);
		long siz=ftell(fp);
		fseek(fp,0,SEEK_SET);
		char *buf=new char[siz];
		unsigned int n= fread((void*) buf,(unsigned int)siz,1,fp);
		fclose(fp);

		//local file header signature control to check the file correctiveness
		if(*((unsigned int*)buf)!=0x04034b50)
		{
			return (bool)ZIP_ERR_WRONG_FILE;
		}

		ReadCentralDirectory(buf,siz);

		return (bool)ZIP_OK;
	}


	void ZipFile::ReadCentralDirectory(char * data,long len)
	{
		char * tmp;

		//search signature
		tmp=data;
		unsigned int * tmp2;
		tmp2= (unsigned int *)tmp;
		len-=4;

		while((*tmp2)!=0x02014b50 && len)
		{
			tmp++;
			tmp2= (unsigned int *)tmp;
			len--;
		}

		//retrieve FileHeader for each file
		int siz;
		do
		{
			ZipFileheader fhdr;
			siz = ReadFileHeader(tmp, &fhdr);
			if(siz)
			{
				ZipFileheader *pfhdr = new(ZipFileheader);
				*pfhdr=fhdr;
				m_FileAttributes.push_back(pfhdr);
			}
			tmp+=siz;
		} while(siz!=0);
	}

	int ZipFile::ReadFileHeader(char * data, ZipFileheader * hdr)
	{
		char * origdata=data;
		::std::string m_stData,st_temp;

		//fill the values into the file_header structure
		hdr->signature            = (unsigned int)		ReadValue((unsigned char*)data   ,32);
		if(hdr->signature!=0x02014b50)	return 0; //no further file
		hdr->version_made_by      = (unsigned short)	ReadValue((unsigned char*)data+4 ,16);
		hdr->version_needed       = (unsigned short)	ReadValue((unsigned char*)data+6 ,16);
		hdr->bitflags             = (unsigned short)	ReadValue((unsigned char*)data+8 ,16);
		hdr->comp_method          = (unsigned short)	ReadValue((unsigned char*)data+10,16);
		hdr->lastModFileTime      = (unsigned short)	ReadValue((unsigned char*)data+12,16);
		hdr->lastModFileDate      = (unsigned short)	ReadValue((unsigned char*)data+14,16);
		hdr->crc_32               = (unsigned int)		ReadValue((unsigned char*)data+16,32);
		hdr->comp_size            = (unsigned int)		ReadValue((unsigned char*)data+20,32);
		hdr->uncompr_size         = (unsigned int)		ReadValue((unsigned char*)data+24,32);
		hdr->fname_len            = (unsigned short)	ReadValue((unsigned char*)data+28,16);
		hdr->extra_field_len      = (unsigned short)	ReadValue((unsigned char*)data+30,16);
		hdr->fcomment_len         = (unsigned short)	ReadValue((unsigned char*)data+32,16);
		hdr->disk_num_start       = (unsigned short)	ReadValue((unsigned char*)data+34,16);
		hdr->internal_fattribute  = (unsigned short)	ReadValue((unsigned char*)data+36,16);
		hdr->external_fattribute  = (unsigned int)		ReadValue((unsigned char*)data+38,32);
		hdr->relative_offset      = (unsigned int)		ReadValue((unsigned char*)data+42,32);

		data+=46;

		if(hdr->fname_len>0)
		{
			char *fn;
			fn=new char[hdr->fname_len+1];
			strncpy_s(fn,hdr->fname_len+1,(char*)data,hdr->fname_len);
			fn[hdr->fname_len]='\0';
			hdr->file_name = fn;
			data+=hdr->fname_len;
		}

		if(hdr->extra_field_len>0)
		{
			char *fn;
			fn=new char[hdr->extra_field_len+1];
			strncpy_s(fn,hdr->extra_field_len+1,(char*)data,hdr->extra_field_len);
			fn[hdr->extra_field_len]='\0';
			hdr->extra_field = fn;
			data += hdr->extra_field_len;
		}

		//file comment
		if(hdr->fcomment_len>0)
		{
			char *fn;
			fn=new char[hdr->fcomment_len+1];
			strncpy_s(fn,hdr->fcomment_len+1,(char*)data,hdr->fcomment_len);
			fn[hdr->fcomment_len]='\0';
			hdr->file_comment = fn;
			data += hdr->extra_field_len;
		}

		return (data-origdata);
	}

	ui32 ZipFile::ReadValue(unsigned char * buf, int nbits)
	{
		/*Name:    void ReadValue(char*buf, int nbits)
		/*Return the value read from the buffer of size nbits;
		*/
		ui32 value = 0;
		switch (nbits)
		{
			case (8):
				value = (ui32)*(buf);
				break;
			case(16):
				value = (((ui32)*(buf+1))<<8)+(ui32)*(buf);
				break;
			case(24):
				value = (((ui32)*(buf+2))<<16)+(((ui32)*(buf+1))<<8)+((ui32)*(buf));
				break;
			case(32):
				value = (((ui32)*(buf+3))<<24)+(((ui32)*(buf+2))<<16)+(((ui32)*(buf+1))<<8)+((ui32)*(buf));
				break;
			default:
				printf("ReadValue has implemented only the cases with nbits = 8, 16, 24, 32.");
				break;
		}
		return(value);
	}

	ZipFileheader * ZipFile::GetFileAttributes(unsigned int index)
	{
		if(index<0 || index >=m_FileAttributes.size())
		{
			return NULL;
		}
		else
		{
			return((ZipFileheader *)m_FileAttributes.at(index));
		}
	}

	ZipFile workspace;

};

unsigned int GetNumberOfFiles(const char* zipfilename)
{
	::workspace.ResetContent();
	::workspace.SetFileName(zipfilename);
	if(::workspace.OpenFile()==ZIP_OK)
	{
		return ::workspace.GetFilesNumber();
	}
	return 0;
}

char* GetFilenameFrom(const char* zipfilename, unsigned int index)
{
	::workspace.ResetContent();
	::workspace.SetFileName(zipfilename);
	if(::workspace.OpenFile()==ZIP_OK)
	{
		return ::workspace.GetFileAttributes(index)->file_name;
	}
	return NULL;
}

unsigned int GetFilesizeFrom(const char* zipfilename, unsigned int index)
{
	::workspace.ResetContent();
	::workspace.SetFileName(zipfilename);
	if(::workspace.OpenFile()==ZIP_OK)
	{
		return ::workspace.GetFileAttributes(index)->uncompr_size;
	}
	return 0;
}