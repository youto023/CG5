#pragma once

#include"KamataEngine.h"  //WorldTransformクラスの利用

class WorldTransformEX : public KamataEngine::WorldTransform {
public:
	// Affine変換行列の生成と定数バッファへの転送を行う
	void UpdateMatrix();

	// Affine変換行列の生成
	KamataEngine::Matrix4x4 MakeAffineMatrix();
	};