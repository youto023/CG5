#include <Windows.h>
#include"KamataEngine.h"
#include "GameScene.h"
using namespace KamataEngine;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// DirectXCommonインスタンスを取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	//エンジン初期化
	KamataEngine::Initialize(L"LE3D_09_タケダ_ユウト_CG4");
	//メインループ
	while (true) {
		// エンジン更新
		if (KamataEngine::Update()) {
			break;
		}
		//ゲームシーンのインスタンス生成
		GameScene* gameScene = new GameScene();
		// ゲームシーンの初期化
		gameScene->Initialize();
		//ゲームシーンの解放
		delete gameScene;
		// nullptrに代入
		gameScene = nullptr;

		// ゲームシーンの更新
		gameScene->Update();
	// 描画開始
		dxCommon->PreDraw();

		// ゲームシーンの描画
		gameScene->Draw();

		// 描画終了
		dxCommon->PostDraw();	
	}
	

	// エンジン終了
	KamataEngine::Finalize();
	return 0;
}
