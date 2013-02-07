#define _X86_
#define WIN32_LEAN_AND_MEAN
#define _DLL
#define _MT
#define UNICODE

#include <windows.h>
#include <Shellapi.h>

#pragma optimize("gsy",on)

//#pragma comment(lib,"kernel32.lib")
//#pragma comment(lib,"shell32.lib")
//#pragma comment(linker, "-entry:Main")

#if (_MSC_VER<1300)
  #pragma comment(linker,"/RELEASE")
#endif
#pragma comment(linker, "-opt:nowin98")
#pragma comment(linker, "-opt:ref")
#pragma comment(linker, "-merge:.rdata=.text")
#pragma comment(linker, "-merge:.data=.text")
#pragma comment(linker, "-merge:.reloc=.text")
#pragma comment(linker, "-subsystem:windows")
#pragma comment(linker,"-ignore:4078") // ignore warning about merged sections

typedef VOID (WINAPI * PFCFGDIALOG)();

int __cdecl mainW(int argc, LPWSTR *argv)
{
	PFCFGDIALOG pfCfgDialog = NULL;
	HMODULE hLib = LoadLibrary(L"AgreementGINA.dll");
	if(!hLib)
	{
		MessageBox(0, L"Make sure the AgreementGINA.dll is in the path - the name is important. It could not be loaded!",
			L"Error", MB_OK | MB_ICONERROR);
		return 0xFF;
	}
	pfCfgDialog = (PFCFGDIALOG)GetProcAddress(hLib, "CfgDialog");
	if(!pfCfgDialog)
	{
		MessageBox(0, L"The DLL version you supplied does not support configuration!",
			L"Error", MB_OK | MB_ICONERROR);
		FreeLibrary(hLib);
		return 0xFE;
	}
	pfCfgDialog();
	FreeLibrary(hLib);

	return 0;
}

void __cdecl Main(void)
{
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	ExitProcess(mainW(argc, argv));
}
