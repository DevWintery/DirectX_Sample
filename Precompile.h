#pragma once

#pragma comment(lib, "dsound.lib")

#include<Windows.h>
#include<d3dx9.h>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<math.h>
#include<functional>
#include<memory>
#include<iostream>
#include<map>

using namespace std;

using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;

using Color = D3DXCOLOR;

using Matrix4 = D3DXMATRIX;

#include"SDKwavefile.h"
#include"SDKsound.h"

#include "Singleton.h"

#include"App.h"

#include"Texture.h"

#include"Object.h"
#include"Sprite.h"
#include"ObjectList.h"
#include"Camera.h"

#include"Scene.h"

#include"Math.h"

#include"Animation.h"

#include"ProgressBar.h"
#include"Button.h"
#include"Font.h"
