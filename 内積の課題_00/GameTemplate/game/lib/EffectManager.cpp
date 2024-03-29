/*!
 * @brief	エフェクトマネージャ
 */

#include "stdafx.h"
#include "lib/EffectManager.h"


/*!
 * @brief	コンストラクタ。
 */
EffectManager::EffectManager()
{
}
/*!
 * @brief	デストラクタ。
 */
EffectManager::~EffectManager()
{
	Release();
}
/*!
 *@brief	エフェクトのロード。
 *@details
 * 読み込み済みのエフェクトの場合はロードは行われず、</br>
 * 既存のエフェクトが返ってきます。
 *@param[in]	filePath	ロードするエフェクトのファイルパス。
 *@return	ロードしたエフェクトファイル。
 */
LPD3DXEFFECT EffectManager::LoadEffect( const char* filePath )
{
	
	LPD3DXEFFECT effect = nullptr;
	int hash = MakeHash(filePath);
	
	auto it = effectDictinary.find(hash);
	if (it == effectDictinary.end()) {
		//新規。
		LPD3DXBUFFER  compileErrorBuffer = nullptr;
		HRESULT hr = D3DXCreateEffectFromFile(
			g_pd3dDevice,
			filePath,
			NULL,
			NULL,
#ifdef _DEBUG
			D3DXSHADER_DEBUG,
#else
			D3DXSHADER_SKIPVALIDATION,
#endif
			NULL,
			&effect,
			&compileErrorBuffer
			);
		if (FAILED(hr)) {
			MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			//読み込み失敗。
			std::abort();
		}
		
		std::pair<int, LPD3DXEFFECT> node(hash, effect);
		effectDictinary.insert(node);
	}
	else {
		//登録済み。
		effect = it->second;
	}
	return effect;
}
/*!
 * @brief	リリース。
 */
void EffectManager::Release()
{
	for (auto p : effectDictinary) {
		p.second->Release();;
	}
	effectDictinary.clear();
}