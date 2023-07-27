#include "CrAssetManager.h"


CrAssetManager G_AssetManager;                                        
CrAssetManager* GetAssetManager() { return &G_AssetManager; }