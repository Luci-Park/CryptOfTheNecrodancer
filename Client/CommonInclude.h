#pragma once
#include <windows.h>
#include <wingdi.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <filesystem>
#include <random>
#include <algorithm>
#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#define DEFAULTUNIT 24
#define UNITSCALE 3
#define UNITLENGTH 72 
#define BEATPERCENT 30