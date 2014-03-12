#include "pch.h"
#include "PlatformTools.h"

using namespace Tungsten;
using namespace Tungsten::PlatformTools;
HRESULT Tungsten::PlatformTools::CreateByteCodeFromFile(const WCHAR* filename,MemoryBlock* block)
{
	HANDLE file;
	file=CreateFileHandle(filename,FileAccess::Read);
	_FILE_STANDARD_INFO info;
	CheckFatalError( GetFileInformationByHandleEx(file,FileStandardInfo,&info,sizeof(info)) );
	
	block->width=info.EndOfFile.LowPart;
	
	block->ptr=new byte[block->width];
	if(!ReadFile(file,block->ptr,block->width,NULL,NULL))
#ifdef _DEBUG
	{
	const DWORD size=100+1;
	DWORD error=GetLastError();
	WCHAR errorstring[size];
	DWORD errormessage=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL,error,
		NULL,errorstring,
		size,NULL);
	CloseHandle(file);
	free(block->ptr);
	block->ptr=NULL;
	return E_FAIL;
	}
#else
	{
		CloseHandle(file);
		return E_FAIL;
	}
#endif
	
	CloseHandle(file);
	return S_OK;
}

HRESULT Tungsten::PlatformTools::CreateStringBufferFromFile(const WCHAR* filename, _Out_ std::stringstream** p_stringBuff)
{

	HANDLE file;
	*p_stringBuff=NULL;
	file=CreateFileHandle(filename,Read);
	if(file==NULL) return E_INVALIDARG;
	byte* array_buffer;
	/*
	BOOL WINAPI GetFileInformationByHandleEx(
  _In_   HANDLE hFile,
  _In_   FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  _Out_  LPVOID lpFileInformation,
  _In_   DWORD dwBufferSize
	);
	*/
	_FILE_STANDARD_INFO info;
	GetFileInformationByHandleEx(file,FileStandardInfo,&info,sizeof(info));

	DWORD size=info.EndOfFile.LowPart;
	DWORD read_bytes;
	array_buffer=new byte[size+1];
	if(!ReadFile(file,array_buffer,size,&read_bytes,NULL))
#ifdef _DEBUG
	{
	const DWORD size=100+1;
	DWORD error=GetLastError();
	WCHAR errorstring[size];
	DWORD errormessage=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_ARGUMENT_ARRAY,
		NULL,error,
		NULL,errorstring,
		size,NULL);
	CloseHandle(file);
	free(array_buffer);
	return E_FAIL;
	}
#else
	{
		CloseHandle(file);
		return E_FAIL;
	}
#endif
	array_buffer[size]=0;
	*p_stringBuff=new std::stringstream((char*)array_buffer);
	delete[] array_buffer;
	CloseHandle(file);
	return S_OK;
}

 HANDLE Tungsten::PlatformTools::CreateFileHandle(const WCHAR* filename,int desiredAcces)
{
	
	//Win32 Implementation
	std::wstring filepath;
	bool create=desiredAcces&Create;
	desiredAcces=desiredAcces&~Create;

#ifdef _DESKTOPAPP
	
	WCHAR buffer[260];
	GetModuleFileName(NULL,buffer,260);
	//Remove the trailing executable file name
	int index=0;
	int pathLength;
	while(index<260)
	{
		if(buffer[index]=='\\') pathLength=index;
		index++;
	}
	filepath.append(buffer,0,pathLength);
#endif
#ifdef _WINRTAPP
	filepath=Windows::ApplicationModel::Package::Current->InstalledLocation->Path->Data();
#endif
	filepath.append(L"\\");
	filepath.append(filename);
	//HANDLE file=CreateFile2(filepath.c_str(),GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING,NULL);
	int flag;
	if(create) flag=CREATE_ALWAYS;
	else flag=OPEN_EXISTING;
	
	HANDLE file=CreateFile2(filepath.c_str(),desiredAcces,FILE_SHARE_READ,flag,NULL);
	if(file==INVALID_HANDLE_VALUE)
#ifdef _DEBUG
	{
		DWORD error=GetLastError();
		const DWORD size=500+1;
		WCHAR errorstring[size];
		DWORD errormessage=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_ARGUMENT_ARRAY,
			NULL,error,
			NULL,errorstring,
			size,NULL);
		wcscat_s(errorstring,L"\n");
		wcscat_s(errorstring,filepath.c_str());
		Tungsten::PlatformTools::PostError(errorstring);
		return NULL;
		
	}
#else
	{
		DWORD error=GetLastError();
		const DWORD size=100+1;
		WCHAR errorstring[size];
		DWORD errormessage=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_ARGUMENT_ARRAY,
			NULL,error,
			NULL,errorstring,
			size,NULL);
		return NULL;

	}
#endif
	return file;
	
		
}

#if defined _DESKTOPAPP

#include <xmllite.h>
#include <Shlwapi.h>
#include <string>

#pragma comment(lib,"XmlLite.lib")
#pragma comment(lib,"Shlwapi.lib")
 struct character
 {
	 int x;
	 int y;
	 int width;
	 int height;
 };
 void XMLParse()
 {
	 IXmlReader* reader;
	 CreateXmlReader(IID_PPV_ARGS(&reader), NULL);
	 IStream* stream;
	 SHCreateStreamOnFile(L"input.xml", STGM_FAILIFTHERE, &stream);
	 reader->SetInput(stream);
	 XmlNodeType nodeType;
	 character buffer[256];
	 character* active;
	 int* cursor = NULL;
	 while (S_OK == reader->Read(&nodeType))
	 {
		 switch (nodeType)
		 {
		 case XmlNodeType_Element:
			 const WCHAR* name;
			 const WCHAR* value;
			 reader->GetLocalName(&name, NULL);
			 if (!wcscmp(name, L"character"))
			 {
				 reader->MoveToAttributeByName(L"key", NULL);
				 reader->GetValue(&value, NULL);
				 active = buffer + wcstol(value, NULL, 10);
			 }
			 if (!wcscmp(name, L"x"))
			 {

				 cursor = &active->x;
			 }
			 if (!wcscmp(name, L"y"))
			 {

				 cursor = &active->y;
			 }
			 if (!wcscmp(name, L"width"))
			 {


				 cursor = &active->width;
			 }
			 if (!wcscmp(name, L"height"))
			 {

				 cursor = &active->height;
			 }
			 break;
		 case XmlNodeType_Text:

			 reader->GetValue(&value, NULL);
			 *cursor = wcstol(value, NULL, 10);
		 default:
			 ;
		 }
	 }
	 HANDLE file = CreateFile2(L"output.bfd", GENERIC_WRITE, NULL, CREATE_ALWAYS, NULL);
	 WriteFile(file, buffer, sizeof(buffer), NULL, NULL);
	 CloseHandle(file);
 }

#endif