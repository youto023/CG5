#include <Windows.h>
#include"KamataEngine.h"
#include "GameScene.h"
using namespace KamataEngine;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジン初期化
	KamataEngine::Initialize(L"LE3D_09_タケダ_ユウト_CG4");
	
	// DirectXCommonインスタンスを取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// DirectXCommonクラスが管理している、ウィンドウの幅と高さの値を取得
	int32_t w = dxCommon->GetBackBufferWidth();
	int32_t h = dxCommon->GetBackBufferHeight();
	DebugText::GetInstance()->ConsolePrintf(std::format("width:{} height:{}\n", w, h).c_str());

	// DirectXCommonクラスが管理している、コマンドリストを取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();

	// RootSignature作成
    //構造体にデータを用意する
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature= {};
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlog = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlog);
	if (FAILED(hr)) {
		DebugText::GetInstance()->ConsolePrintf(
		reinterpret_cast<char*>(errorBlog->GetBufferPointer()));
		assert(false);
	}
	//バイナリを元に作成
	ID3D12RootSignature* rootSignature = nullptr;
	hr = dxCommon->GetDevice()->CreateRootSignature(
		0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(hr));

	//InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	// BlendState-----------今回は不透明
	D3D12_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = false;
	//すべての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;

	// RasterizerState-----
	D3D12_RASTERIZER_DESC rasterizerDesc = {};
	//裏面（反時計回り）をカリングする
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	//塗りつぶしモードをソリッドにする（ワイヤーフレームなら、D3D12_FILL_MODE_WIREFRAME）
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;















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
