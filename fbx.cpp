////======================================================================
////
//// FBX読み込み[fbx.cpp]
////
////======================================================================
//
////**********************************************************************
//// インクルードヘッダー
////**********************************************************************
//#include "main.h"
//#include "renderer.h"
//#include "fbx.h"
//#include "texture.h"
//#include <string>
//#include <vector>
//#include <fbxsdk.h>
//
//
////**********************************************************************
//// マクロ定義
////**********************************************************************
//#ifdef IOS_REF
//#undef  IOS_REF
//#define IOS_REF (*(m_pFbxManager->GetIOSettings()))
//#endif
//
//
////======================================================================
//// コンストラクタ
////======================================================================
//CFBX::CFBX() {
//
//}
//
////======================================================================
//// デストラクタ
////======================================================================
//CFBX::~CFBX() {
//
//}
//
////======================================================================
//// FBXの読み込み
////======================================================================
//MODEL_ CFBX::Load(const char* FileName) {
//	// ファイル名保存
//	m_FileName = FileName;
//
//	// Fbx管理するやつ作成
//	FbxManager* pFbxManager = FbxManager::Create();
//	if (!pFbxManager) {
//		// FbxManagerの作成に失敗
//		MessageBox(NULL, "FbxManagerの作成に失敗しました", "エラー", MB_OK);
//		return MODEL_();
//	}
//
//	// Fbxから情報を引き出すやつ作成
//	FbxImporter* pFbxImporter = FbxImporter::Create(pFbxManager, "");
//	if (!pFbxImporter) {
//		// FbxImporterの作成に失敗
//		MessageBox(NULL, "FbxImporterの作成に失敗しました", "エラー", MB_OK);
//		return MODEL_();
//	}
//
//	// SceneオブジェクトにFbxファイル内の情報を流し込む
//	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "");
//	if (!pFbxImporter) {
//		// FbxSceneの作成に失敗
//		MessageBox(NULL, "FbxSceneの作成に失敗しました", "エラー", MB_OK);
//		return MODEL_();
//	}
//
//	// Fbxファイルを開く
//	if (!pFbxImporter->Initialize(FileName)) {
//		// Fbxファイルを開くのに失敗
//		MessageBox(NULL, "Fbxファイルを開くのに失敗しました", "エラー", MB_OK);
//		return MODEL_();
//	}
//
//	// pFbxSceneにFbxファイルを読み込む
//	if (!pFbxImporter->Import(pFbxScene)) {
//		// Fbxファイルの読み込みに失敗
//		MessageBox(NULL, "Fbxファイルの読み込みに失敗しました", "エラー", MB_OK);
//		return MODEL_();
//	}
//
//	// 使ったから解放
//	if (pFbxImporter) {
//		pFbxImporter->Destroy();
//		pFbxImporter = NULL;
//	}
//
//	// じおめとりー
//	FbxGeometryConverter GeometryConverter(pFbxManager);
//	// ポリゴンをすべて三角形化
//	GeometryConverter.Triangulate(pFbxScene, true);
//	// 縮退メッシュをクリーンアップまたは削除(クリーンアップされたメッシュが無効になると、完全に削除されます)
//	GeometryConverter.RemoveBadPolygonsFromMeshes(pFbxScene);
//	//// マテリアルごとにメッシュを分割
//	//GeometryConverter.SplitMeshesPerMaterial(pFbxScene, true);
//
//	// ノードの取得
//	FbxNode* pFbxRootNode = pFbxScene->GetRootNode();
//	if (!pFbxRootNode) {
//		// ノードの取得に失敗
//		MessageBox(NULL, "ノードの取得に失敗しました", "エラー", MB_OK);
//		return MODEL_();
//	}
//
//	// メッシュ取得
//	GetMesh(pFbxRootNode);
//
//	// 返すのモデル構造体
//	MODEL_ model;
//
//	// メッシュ情報取得
//	if (FAILED(GetMeshData(pFbxRootNode, model))) {
//		// メッシュ情報の取得に失敗
//		MessageBox(NULL, "メッシュ情報の取得に失敗しました", "エラー", MB_OK);
//		return MODEL_();
//	}
//
//	// Fbx全開放
//	pFbxScene->Destroy();
//	pFbxManager->Destroy();
//
//	model.bone = m_BoneList;
//	return model;
//
//
//
//
//
//
//
//	//// FBXManagerの生成
//	//m_pFbxManager = FbxManager::Create();
//
//	//// FBXManagerが生成されたか確認
//	//if (!m_pFbxManager)
//	//	assert(false);
//
//	//// FBXに対する入出力を定義する
//	//FbxIOSettings* pFbxIO = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
//	//m_pFbxManager->SetIOSettings(pFbxIO);
//
//	//// 実行可能なディレクトリ(オプション)からプラグインをロード
//	//FbxString lPath = FbxGetApplicationDirectory();
//	//m_pFbxManager->LoadPluginsDirectory(lPath.Buffer());
//
//	//// Fbxシーンを生成
//	//m_pFbxScene = FbxScene::Create(m_pFbxManager, "Scene");
//
//	//// Fbxシーンが生成されたか確認
//	//if (!m_pFbxScene)
//	//	assert(false);
//
//	//// バージョンメジャー番号、バージョンマイナー番号、バージョンリビジョン番号
//	//int lSDKMajor, lSDKMinor, lSDKRevision;
//
//	//// このバージョンのFBXSDKの現在のデフォルトのFBXファイル形式のバージョン番号を取得
//	//FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);
//
//	//// FBXインポータを初期化する
//	//FbxImporter* pImporter = FbxImporter::Create(m_pFbxManager, "");
//
//	//// FBXファイルの読み込みを実行する
//	//const bool lImportStatus = pImporter->Initialize(FileName, -1, m_pFbxManager->GetIOSettings());
//
//	//// バージョンメジャー番号、バージョンマイナー番号、バージョンリビジョン番号
//	//int lFileMajor, lFileMinor, lFileRevision;
//
//	//// ファイル情報を取得
//	//pImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);
//
//	//// インポータの情報が生成されたか確認
//	//if (!lImportStatus)
//	//	assert(false);
//
//	//int i, lAnimStackCount;
//	//bool animation = false;
//
//	//if (pImporter->IsFBX())
//	//{
//	//	if (animation)
//	//	{
//	//		lAnimStackCount = pImporter->GetAnimStackCount();
//
//	//		for (i = 0; i < lAnimStackCount; i++)
//	//		{
//	//			FbxTakeInfo* lTakeInfo = pImporter->GetTakeInfo(i);
//
//	//			// タイムモード取得
//	//			FbxGlobalSettings& Set = m_pFbxScene->GetGlobalSettings();
//	//			FbxTime::EMode timeMode = Set.GetTimeMode();
//
//	//			FBXANIMATION temp;
//	//			temp.name = lTakeInfo->mName;
//
//	//			// アニメーションが始まる時間と終わる時間
//	//			FbxTime start = lTakeInfo->mLocalTimeSpan.GetStart();
//	//			FbxTime stop = lTakeInfo->mLocalTimeSpan.GetStop();
//
//	//			//fbxの1フレームあたりの時間数
//	//			temp.framePeriod.SetTime(0, 0, 0, 1, 0, timeMode);
//
//	//			// 1フレームあたりで割れば、フレーム数になる
//	//			temp.startFrame = (int)(start.Get() / temp.framePeriod.Get());
//	//			temp.endFrame = (int)(stop.Get() / temp.framePeriod.Get());
//	//			temp.frameNum = temp.endFrame - temp.startFrame + 1;
//
//	//			animationStack_.emplace_back(temp);
//
//	//		}
//	//	}
//
//	//	IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
//	//	IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
//	//	IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
//	//	IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
//	//	IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
//	//	IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
//	//	IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
//	//}
//
//	//bool lStatus;
//
//	//lStatus = pImporter->Import(m_pFbxScene);
//
//	//char lPassword[1024];
//
//	//if (lStatus == false && pImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
//	//{
//	//	lPassword[0] = '\0';
//
//	//	FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
//	//		scanf("%s", lPassword);
//	//	FBXSDK_CRT_SECURE_NO_WARNING_END
//
//	//		FbxString lString(lPassword);
//
//	//	IOS_REF.SetStringProp(IMP_FBX_PASSWORD, lString);
//	//	IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);
//
//	//	lStatus = pImporter->Import(m_pFbxScene);
//	//}
//
//	//pImporter->Destroy();
//}
//
////======================================================================
//// メッシュを取得
////======================================================================
//void CFBX::GetMesh(FbxNode* pNode) {
//	// ルートノードの子ノード数
//	int ChildCount = pNode->GetChildCount();
//
//	// 子ノードの数だけ探す
//	for (int i = 0; i < ChildCount; i++) {
//
//		// 子ノードを取得
//		FbxNode*			pChild = pNode->GetChild(i);
//		// ノード属性
//		FbxNodeAttribute*	pAttribute = pChild->GetNodeAttribute();
//
//		// NULLノード属性
//		if (pAttribute == nullptr) { continue; }
//
//		switch (pAttribute->GetAttributeType())
//		{
//		case FbxNodeAttribute::eMesh:
//			m_MaterialCount[0]++;
//			break;
//		default:
//			break;
//		}
//
//		// メッシュ探し
//		GetMesh(pNode->GetChild(i));
//	}
//}
//
////======================================================================
//// メッシュデータの取得
////======================================================================
//HRESULT CFBX::GetMeshData(FbxNode* pNode, MODEL_& model) {
//	m_TempNode.emplace_back(pNode);
//	int childNodeNum = pNode->GetChildCount();
//	FbxMesh* mesh = nullptr;
//
//	for (int i = 0; i < childNodeNum; ++i) {
//		// 子ノードを取得
//		FbxNode*			pChild = pNode->GetChild(i);
//		FbxNodeAttribute*	pAttrib = pChild->GetNodeAttribute();
//
//		if (pAttrib == nullptr) { continue; }
//
//		switch (pAttrib->GetAttributeType()) {
//		case FbxNodeAttribute::eMesh:
//		{
//			mesh = pChild->GetMesh();
//			m_TempName = pChild->GetName();
//
//			int vertexCnt = mesh->GetPolygonVertexCount();
//			int normalLayerCount = mesh->GetElementNormalCount();
//			int UVLayerCount = mesh->GetElementUVCount();
//			int vColorLayerCount = mesh->GetElementVertexColorCount();
//
//			GetPosition(mesh);
//			GetVertexNormal(mesh);
//			GetVertexTangent(mesh);
//			GetVertexUV(mesh);
//			std::string temp = "";
//			GetTextureNames(mesh, FbxSurfaceMaterial::sDiffuse, temp);
//			temp = "";
//			GetTextureNames(mesh, FbxSurfaceMaterial::sBump, temp);
//			if (temp == "") {
//				GetTextureNames(mesh, FbxSurfaceMaterial::sNormalMap, temp);
//			}
//			GetVertexColor(mesh);
//			if (FAILED(CreateModelData(model))) {
//				return E_FAIL;
//			}
//
//			// 読み込んだ数を増やす
//			m_MaterialCount[1]++;
//
//			//マテリアル数だけ取得したら再帰をぬける
//			if (m_MaterialCount[1] >= m_MaterialCount[0])
//			{
//				m_TempNode.emplace_back(pChild);
//				m_MaterialCount[0] = m_MaterialCount[1] = 0;
//				return S_OK;
//			}
//			break;
//		}
//		default:
//			break;
//		}
//		if (FAILED(GetMeshData(pChild, model))) {
//			return E_FAIL;
//		}
//	}
//	return S_OK;
//}
//
////======================================================================
//// 頂点座標の取得
////======================================================================
//void CFBX::GetPosition(FbxMesh* pMesh) {
//	// メッシュマテリアルリストの取得
//	GetMeshMaterialList(pMesh);
//
//	// 総頂点数
//	m_PointCount = pMesh->GetControlPointsCount();
//	// 総ポリゴン数の取得
//	m_PolygonCount = pMesh->GetPolygonCount();
//	// 総インデックス数の取得
//	m_IndexCount = pMesh->GetPolygonVertexCount();
//
//	// 頂点の取得
//	FbxVector4* vertex = pMesh->GetControlPoints();
//
//	// 頂点の取得
//	for (int i = 0; i < m_PointCount; ++i)
//	{
//		// 頂点情報をインデックス順で取得
//		VERTEXPOINTBONE temp;
//		temp.position = { -(float)vertex[i][0], (float)vertex[i][1], (float)vertex[i][2] };
//		for (int j = 0; j < 4; ++j)
//		{
//			temp.boneData[j].boneIndex = 0;
//			temp.boneData[j].weight = 0;
//		}
//		m_TempPoint.emplace_back(temp);
//	}
//
//	GetBone(pMesh);
//}
//
////======================================================================
//// メッシュに入ってるマテリアルリストの取得
////======================================================================
//void CFBX::GetMeshMaterialList(FbxMesh* pMesh) {
//	// 中身の解放
//	m_MeshMaterialList.clear();
//
//	// メッシュに付いているマテリアルの数の取得
//	int layerCount = pMesh->GetLayerCount();
//
//	for (int i = 0; i < layerCount; ++i)
//	{
//		// マテリアルの取得
//		FbxLayerElementMaterial* pMat = pMesh->GetLayer(i)->GetMaterials();
//		if (pMat) {
//			if (pMat->GetReferenceMode() == FbxLayerElement::eIndex || pMat->GetReferenceMode() == FbxLayerElement::eIndexToDirect) {
//				// マテリアルのポリゴン数を取得
//				int polygonNum = pMat->GetIndexArray().GetCount();
//
//				for (int j = 0; j < polygonNum; ++j) {
//					// ポリゴン数分なのでインデックス分に変える(三角頂点化しているため3倍でいいはず)
//					m_MeshMaterialList.emplace_back(pMat->GetIndexArray().GetAt(j));
//					m_MeshMaterialList.emplace_back(pMat->GetIndexArray().GetAt(j));
//					m_MeshMaterialList.emplace_back(pMat->GetIndexArray().GetAt(j));
//				}
//			}
//		}
//	}
//}
//
////======================================================================
//// ボーンの取得
////======================================================================
//void CFBX::GetBone(FbxMesh* pMesh) {
//	// スキンの数を取得
//	int skinMax = pMesh->GetDeformerCount(FbxDeformer::eSkin);
//	if (skinMax == 0)
//	{
//		BONE ofBone;
//		ofBone.name = pMesh->GetNode()->GetName();
//		ofBone.initMtx = XMMatrixIdentity();
//		XMMATRIX x = XMMatrixIdentity();
//		x.r->m128_f32[0] = -1;
//		ofBone.initMtx *= x;
//
//		m_BoneList.emplace_back(ofBone);
//
//		int cnt = 0;
//		for (const auto& bone : m_BoneList)
//		{
//			if (bone.name == ofBone.name)
//			{
//				break;
//			}
//			cnt++;
//		}
//		if (cnt == m_BoneList.size())
//		{
//			m_BoneList.emplace_back(ofBone);
//		}
//
//		for (int k = 0; k < m_PointCount; ++k)
//		{
//			VERTEXBONE t;
//			t.boneIndex = (float)cnt;
//			t.weight = 1.0f;
//
//			if (m_TempPoint[k].boneData[0].weight == 0)
//			{
//				m_TempPoint[k].boneData[0].boneIndex = t.boneIndex;
//				m_TempPoint[k].boneData[0].weight = t.weight;
//			}
//		}
//	}
//
//	for (int i = 0; i < skinMax; ++i)
//	{
//		// i番目のスキンを取得
//		FbxSkin* skin = (FbxSkin*)(pMesh->GetDeformer(i, FbxDeformer::eSkin));
//
//		// クラスターの数を取得
//		int clusterNum = skin->GetClusterCount();
//
//		for (int j = 0; j < clusterNum; ++j)
//		{
//			// j番目のクラスタを取得 クラスタ ＝ ボーン
//			FbxCluster* cluster = skin->GetCluster(j);
//			int			pointNum = cluster->GetControlPointIndicesCount();
//			int*		pointAry = cluster->GetControlPointIndices();
//			double*		weightAry = cluster->GetControlPointWeights();
//			// ボーンオフセット行列の取得
//
//			BONE ofBone;
//			ofBone.name = cluster->GetLink()->GetName();
//			FbxAMatrix initMtx;
//			cluster->GetTransformLinkMatrix(initMtx);
//			CreateMtx(ofBone.initMtx, initMtx);
//			XMMATRIX x = XMMatrixIdentity();
//			x.r->m128_f32[0] = -1;
//			ofBone.initMtx *= x;
//
//			int cnt = 0;
//			for (const auto& bone : m_BoneList)
//			{
//				if (bone.name == ofBone.name)
//				{
//					break;
//				}
//				cnt++;
//			}
//			if (cnt == m_BoneList.size())
//			{
//				m_BoneList.emplace_back(ofBone);
//			}
//
//			// ボーンの影響度の取得
//			for (int k = 0; k < m_PointCount; ++k)
//			{
//				for (int l = 0; l < pointNum; ++l)
//				{
//					// 影響頂点が存在した場合
//					if (pointAry[l] == k)
//					{
//						// 影響度の取得
//						VERTEXBONE t;
//						t.boneIndex = (float)cnt;
//						t.weight = (float)weightAry[l];
//
//						for (int m = 0; m < 4; ++m)
//						{
//							if (m_TempPoint[k].boneData[m].weight == 0)
//							{
//								m_TempPoint[k].boneData[m].boneIndex = t.boneIndex;
//								m_TempPoint[k].boneData[m].weight = t.weight;
//								break;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	// インデックスの取得
//	int* index = pMesh->GetPolygonVertices();
//
//	// インデックス分回す
//	for (int i = 0; i < m_IndexCount; ++i)
//	{
//		m_TempVertex.emplace_back(m_TempPoint[index[i]]);
//	}
//}
//
////======================================================================
//// 法線の取得
////======================================================================
//void CFBX::GetVertexNormal(FbxMesh* pMesh) {
//	// 法線レイヤーの数取得
//	int normalLayerCount = pMesh->GetElementNormalCount();
//
//	// レイヤー数だけ回る
//	for (int i = 0; i < normalLayerCount; ++i)
//	{
//		// 法線セットを取得
//		FbxGeometryElementNormal* normal = pMesh->GetElementNormal(i);
//		// マッピングモードの取得
//		FbxGeometryElement::EMappingMode mapping = normal->GetMappingMode();
//		// リファレンスモードの取得
//		FbxGeometryElement::EReferenceMode reference = normal->GetReferenceMode();
//
//		// マッピングモードの判別
//		switch (mapping)
//		{
//		case FbxGeometryElement::eByControlPoint:
//			// リファレンスモードの判別
//			switch (reference)
//			{
//			case FbxGeometryElement::eDirect:
//			{
//				// 法線の数を取得
//				int normalCount = normal->GetDirectArray().GetCount();
//
//				// 法線の数分格納する
//				std::vector<XMFLOAT3> directNormal;
//				for (int j = 0; j < normalCount; ++j)
//				{
//					XMFLOAT3 temp;
//					// 法線の取得
//					temp.x = -(float)normal->GetDirectArray().GetAt(j)[0];
//					temp.y = (float)normal->GetDirectArray().GetAt(j)[1];
//					temp.z = (float)normal->GetDirectArray().GetAt(j)[2];
//					directNormal.emplace_back(temp);
//				}
//
//				// 法線をインデックス順で格納
//				int* index = pMesh->GetPolygonVertices();
//				for (int j = 0; j < m_IndexCount; j++)
//				{
//					XMFLOAT3 temp = { directNormal[index[j]].x, directNormal[index[j]].y, directNormal[index[j]].z };
//					m_TempNormal.emplace_back(temp);
//				}
//			}
//			break;
//
//			case FbxGeometryElement::eIndexToDirect:
//				break;
//
//			default:
//				break;
//			}
//
//			break;
//		case FbxGeometryElement::eByPolygonVertex:
//			// リファレンスモードの判別
//			switch (reference)
//			{
//			case FbxGeometryElement::eDirect:
//			{
//				int normalCount = normal->GetDirectArray().GetCount();
//				for (int j = 0; j < normalCount; ++j)
//				{
//					// 法線の取得
//					XMFLOAT3 temp;
//					temp.x = -(float)normal->GetDirectArray().GetAt(j)[0];
//					temp.y = (float)normal->GetDirectArray().GetAt(j)[1];
//					temp.z = (float)normal->GetDirectArray().GetAt(j)[2];
//					m_TempNormal.emplace_back(temp);
//				}
//			}
//			break;
//
//			case FbxGeometryElement::eIndexToDirect:
//			{
//				std::vector<XMFLOAT3> directNormal;
//				int normalCount = normal->GetDirectArray().GetCount();
//				for (int j = 0; j < normalCount; ++j)
//				{
//					// 法線の取得
//					XMFLOAT3 temp;
//					temp.x = -(float)normal->GetDirectArray().GetAt(j)[0];
//					temp.y = (float)normal->GetDirectArray().GetAt(j)[1];
//					temp.z = (float)normal->GetDirectArray().GetAt(j)[2];
//					directNormal.emplace_back(temp);
//				}
//
//				// インデックスを取得
//				int* index = pMesh->GetPolygonVertices();
//				for (int j = 0; j < normal->GetIndexArray().GetCount(); ++j)
//				{
//					XMFLOAT3 temp = { directNormal[index[j]].x, directNormal[index[j]].y, directNormal[index[j]].z };
//					m_TempNormal.emplace_back(temp);
//				}
//			}
//			break;
//
//			default:
//				break;
//			}
//
//			break;
//		default:
//			break;
//		}
//	}
//}
//
////======================================================================
//// タンジェントの取得
////======================================================================
//void CFBX::GetVertexTangent(FbxMesh* pMesh) {
//	// 法線セット数を取得
//	int normalLayerCount = pMesh->GetElementTangentCount();
//
//	// レイヤー数だけ回る
//	for (int i = 0; i < normalLayerCount; ++i)
//	{
//		// 法線セットを取得
//		FbxGeometryElementTangent* tangent = pMesh->GetElementTangent(i);
//		// マッピングモードの取得
//		FbxGeometryElement::EMappingMode mapping = tangent->GetMappingMode();
//		// リファレンスモードの取得
//		FbxGeometryElement::EReferenceMode reference = tangent->GetReferenceMode();
//
//		// マッピングモードの判別
//		switch (mapping)
//		{
//		case FbxGeometryElement::eByControlPoint:
//			// リファレンスモードの判別
//			switch (reference)
//			{
//			case FbxGeometryElement::eDirect:
//			{
//				int tangentCount = tangent->GetDirectArray().GetCount();
//
//				std::vector<XMFLOAT3> directNormal;
//				for (int j = 0; j < tangentCount; ++j)
//				{
//					XMFLOAT3 temp;
//					// 法線の取得
//					temp.x = -(float)tangent->GetDirectArray().GetAt(j)[0];
//					temp.y = (float)tangent->GetDirectArray().GetAt(j)[1];
//					temp.z = (float)tangent->GetDirectArray().GetAt(j)[2];
//					directNormal.emplace_back(temp);
//				}
//
//				// 法線をインデックス順で格納
//				int* index = pMesh->GetPolygonVertices();
//				for (int j = 0; j < m_IndexCount; j++)
//				{
//					XMFLOAT3 temp = { directNormal[index[j]].x, directNormal[index[j]].y, directNormal[index[j]].z };
//					m_TempTangent.emplace_back(temp);
//				}
//			}
//			break;
//
//			case FbxGeometryElement::eIndexToDirect:
//				break;
//
//			default:
//				break;
//			}
//
//			break;
//		case FbxGeometryElement::eByPolygonVertex:
//		{
//			// 法線数を取得
//			int tangentCount = tangent->GetDirectArray().GetCount();
//			int indexCount = tangent->GetIndexArray().GetCount();
//
//			std::vector<XMFLOAT3> directNormal;
//			for (int j = 0; j < tangentCount; ++j)
//			{
//				// 法線の取得
//				XMFLOAT3 temp;
//				temp.x = -(float)tangent->GetDirectArray().GetAt(j)[0];
//				temp.y = (float)tangent->GetDirectArray().GetAt(j)[1];
//				temp.z = (float)tangent->GetDirectArray().GetAt(j)[2];
//				directNormal.emplace_back(temp);
//			}
//
//			// 法線の数がインデックスの数と同じならそのまま
//			if (tangentCount == m_IndexCount)
//			{
//				m_TempTangent = directNormal;
//			}
//			// 法線インデックスの数が頂点のインデックスと同じ時
//			else if (indexCount == m_IndexCount)
//			{
//				// インデックス数取得
//				int indexCount = tangent->GetIndexArray().GetCount();
//
//				// インデックスを取得
//				int* index = pMesh->GetPolygonVertices();
//
//				for (int j = 0; j < indexCount; ++j)
//				{
//					XMFLOAT3 temp = { directNormal[index[j]].x, directNormal[index[j]].y, directNormal[index[j]].z };
//					m_TempTangent.emplace_back(temp);
//				}
//			}
//		}
//		break;
//		default:
//			break;
//		}
//	}
//}
//
////======================================================================
//// テクスチャ座標の取得
////======================================================================
//void CFBX::GetVertexUV(FbxMesh* pMesh) {
//	// UVセット数を取得
//	int UVLayerCount = pMesh->GetElementUVCount();
//
//	for (int i = 0; i < UVLayerCount; ++i) {
//		// UVバッファを取得
//		FbxGeometryElementUV* UV = pMesh->GetElementUV(i);
//		// マッピングモードの取得
//		FbxGeometryElement::EMappingMode mapping = UV->GetMappingMode();
//		// リファレンスモードの取得
//		FbxGeometryElement::EReferenceMode reference = UV->GetReferenceMode();
//
//		// マッピングモードの判別
//		switch (mapping) {
//		case FbxGeometryElement::eByControlPoint:
//			break;
//
//		case FbxGeometryElement::eByPolygonVertex:
//			// リファレンスモードの判別
//			switch (reference) {
//			case FbxGeometryElement::eDirect:
//				break;
//
//			case FbxGeometryElement::eIndexToDirect:
//			{
//				// インデックス数取得
//				int indexCount = UV->GetIndexArray().GetCount();
//
//				// UVを保持
//				FBXUV tempUV;
//				for (int j = 0; j < indexCount; ++j)
//				{
//					XMFLOAT2 temp = { 0.0f, 0.0f };
//					int index = UV->GetIndexArray().GetAt(j);
//
//					temp.x = (float)UV->GetDirectArray().GetAt(index)[0];
//					temp.y = 1.0f - (float)UV->GetDirectArray().GetAt(index)[1];
//
//					tempUV.texcoord.emplace_back(temp);
//				}
//
//				// UVSet名を取得
//				tempUV.uvSetName = std::string(UV->GetName());
//
//				m_TempTexcoord.emplace_back(tempUV);
//			}
//			break;
//
//			default:
//				break;
//			}
//			break;
//		case FbxGeometryElement::eByEdge:
//			break;
//		case FbxGeometryElement::eByPolygon:
//			break;
//		default:
//			break;
//		}
//	}
//}
//
////======================================================================
//// テクスチャ
////======================================================================
//void CFBX::GetTextureNames(FbxMesh* pMesh, const char* materialType, std::string& get) {
//	int textureNum = 0;
//
//	// メッシュからノードを取得
//	FbxNode* node = pMesh->GetNode();
//
//	// マテリアルの数を取得
//	int materialCnt = node->GetMaterialCount();
//	// マテリアルの数だけ繰り返す
//	for (int i = 0; i < materialCnt; i++)
//	{
//		// マテリアルを取得
//		FbxSurfaceMaterial* material = node->GetMaterial(i);
//		FbxProperty			prop = material->FindProperty(materialType);
//
//		// FbxLayeredTexture の数を取得
//		int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();
//		// アタッチされたテクスチャが FbxLayeredTexture の場合
//		if (0 < layeredTextureCount)
//		{
//			// アタッチされたテクスチャの数だけ繰り返す
//			for (int j = 0; j < layeredTextureCount; ++j)
//			{
//				// テクスチャを取得
//				FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
//				// レイヤー数を取得
//				int textureCount = 1;
//
//				// レイヤー数だけ繰り返す
//				for (int k = 0; k < textureCount; ++k)
//				{
//					// テクスチャを取得
//					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);
//					if (texture) {
//						UVSet temp;
//						// テクスチャ名を取得
//						temp.texName = std::string(texture->GetRelativeFileName());
//						get = temp.texName;
//						// UVSet名を取得
//						temp.uvSetName = std::string(texture->UVSet.GetName());
//
//						m_TempUVSet.emplace_back(temp);
//
//						//--- UVSet名を比較し対応しているテクスチャなら保持 ---//
//						//???
//						//size_t size = strlen(textureName);
//						//aMeshBuffer[model].uvSet[materialCount].texture = new char[size + 1];
//						//memcpy(aMeshBuffer[model].uvSet[materialCount].uvSetName, textureName, size);
//						//aMeshBuffer[model].uvSet[materialCount].texture[size] = '\0';
//					}
//				}
//			}
//		}
//		else
//		{
//			// テクスチャ数を取得
//			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
//			if (fileTextureCount > 0)
//			{
//				// テクスチャの数だけ繰り返す
//				for (int j = 0; j < fileTextureCount; j++)
//				{
//					// テクスチャを取得
//					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
//					if (texture)
//					{
//						UVSet temp;
//						// テクスチャ名を取得
//						temp.texName = m_FileName;
//						// テクスチャのディレクトリはモデルと同じ
//						for (UINT k = temp.texName.size() - 1; temp.texName[k] != '/' && k > 0; k--)
//						{
//							temp.texName.pop_back();
//						}
//
//						std::string tempName = texture->GetFileName();
//						std::string texName;
//						for (UINT k = tempName.size() - 1; tempName[k] != 92 && tempName[k] != '/' && k > 0; k--)
//						{
//							texName.insert(texName.begin(), tempName[k]);
//						}
//						temp.texName += texName;
//
//						// UVSet名を取得
//						temp.uvSetName = std::string(texture->UVSet.Get().Buffer());
//
//						if (materialType == FbxSurfaceMaterial::sDiffuse)
//						{
//							temp.type = MaterialType::Diffuse;
//						}
//						else if (materialType == FbxSurfaceMaterial::sBump || materialType == FbxSurfaceMaterial::sNormalMap)
//						{
//							temp.type = MaterialType::Normal;
//						}
//
//						get = temp.texName;
//						m_TempUVSet.emplace_back(temp);
//						textureNum++;
//					}
//				}
//			}
//			else
//			{
//				FbxSurfaceMaterial*			material = node->GetSrcObject<FbxSurfaceMaterial>(i);
//				const FbxImplementation*	implementation = GetImplementation(material, FBXSDK_IMPLEMENTATION_HLSL);
//				FbxString implemenationType = "HLSL";
//				if (!implementation)
//				{
//					implementation = GetImplementation(material, FBXSDK_IMPLEMENTATION_CGFX);
//					implemenationType = "CGFX";
//				}
//
//				if (implementation)
//				{
//					const FbxBindingTable*	rootTable = implementation->GetRootTable();
//					FbxString				fileName = rootTable->DescAbsoluteURL.Get();
//					FbxString				techniqueName = rootTable->DescTAG.Get();
//					const FbxBindingTable*	table = implementation->GetRootTable();
//					size_t					entryCount = table->GetEntryCount();
//					for (int j = 0; j < (int)entryCount; ++j)
//					{
//						const FbxBindingTableEntry& entry = table->GetEntry(j);
//						const char*					entrySrcType = entry.GetEntryType(true);
//						FbxProperty					fbxProp;
//						FbxString					source = entry.GetSource();
//
//						if (strcmp(FbxPropertyEntryView::sEntryType, entrySrcType) == 0)
//						{
//							fbxProp = material->FindPropertyHierarchical(entry.GetSource());
//							if (!fbxProp.IsValid())
//							{
//								fbxProp = material->RootProperty.FindHierarchical(entry.GetSource());
//							}
//						}
//						else
//							if (strcmp(FbxConstantEntryView::sEntryType, entrySrcType) == 0)
//							{
//								fbxProp = implementation->GetConstants().FindHierarchical(entry.GetSource());
//							}
//
//						if (fbxProp.IsValid())
//						{
//							if (fbxProp.GetSrcObjectCount<FbxTexture>() > 0)
//							{
//								for (int k = 0; k < fbxProp.GetSrcObjectCount<FbxFileTexture>(); ++k)
//								{
//									FbxFileTexture* pTex = fbxProp.GetSrcObject<FbxFileTexture>(k);
//
//									std::string type = "";
//									if (materialType == FbxSurfaceMaterial::sDiffuse)
//									{
//										type = "DiffuseTexture";
//									}
//									if (materialType == FbxSurfaceMaterial::sBump)
//									{
//										type = "NormalTexture";
//									}
//
//									if (strstr(source.Buffer(), type.c_str()) != nullptr)
//									{
//										UVSet temp;
//										// テクスチャ名を取得
//										temp.texName = m_FileName;
//										// テクスチャのディレクトリはモデルと同じ
//										for (UINT k = temp.texName.size() - 1; temp.texName[k] != '/' && k > 0; k--)
//										{
//											temp.texName.pop_back();
//										}
//
//										std::string tempName = pTex->GetFileName();
//										std::string texName;
//										for (UINT k = tempName.size() - 1; tempName[k] != 92 && tempName[k] != '/' && k > 0; k--)
//										{
//											texName.insert(texName.begin(), tempName[k]);
//										}
//
//										temp.texName += texName;
//										temp.uvSetName = "";
//
//										if (materialType == FbxSurfaceMaterial::sDiffuse)
//										{
//											temp.type = MaterialType::Diffuse;
//										}
//										else if (materialType == FbxSurfaceMaterial::sBump)
//										{
//											temp.type = MaterialType::Normal;
//										}
//										get = temp.texName;
//										m_TempUVSet.emplace_back(temp);
//										textureNum++;
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	if (materialType == FbxSurfaceMaterial::sDiffuse)
//	{
//		// 設定がなかった時
//		if (textureNum == 0)
//		{
//			UVSet temp;
//			temp.texName = "";
//			temp.uvSetName = "";
//			m_TempUVSet.emplace_back(temp);
//		}
//	}
//}
//
////======================================================================
//// 頂点色取得
////======================================================================
//void CFBX::GetVertexColor(FbxMesh* pMesh) {
//	// 頂点色数を取得
//	int vColorLayerCount = pMesh->GetElementVertexColorCount();
//
//	// 頂点カラー設定がなかった時
//	if (vColorLayerCount == 0) {
//		for (int i = 0; i < m_IndexCount; ++i)
//		{
//			COLOR temp = COLOR(1, 1, 1, 1);
//			m_TempColor.emplace_back(temp);
//		}
//		return;
//	}
//
//	// レイヤー数だけ回る
//	for (int i = 0; i < vColorLayerCount; ++i)
//	{
//		// 頂点カラーセットを取得
//		FbxGeometryElementVertexColor* color = pMesh->GetElementVertexColor(i);
//		// マッピングモードの取得
//		FbxGeometryElement::EMappingMode mappingMode = color->GetMappingMode();
//		// リファレンスモードの取得
//		FbxGeometryElement::EReferenceMode referenceMode = color->GetReferenceMode();
//
//		// マッピングモードの判別
//		switch (mappingMode) {
//		case FbxGeometryElement::eByControlPoint:
//		{
//			for (int j = 0; j < m_IndexCount; ++j) {
//				COLOR diffuse = COLOR(1, 1, 1, 1);
//				diffuse.r = (float)color->GetDirectArray().GetAt(color->GetIndexArray().GetAt(j))[0];
//				diffuse.g = (float)color->GetDirectArray().GetAt(color->GetIndexArray().GetAt(j))[1];
//				diffuse.b = (float)color->GetDirectArray().GetAt(color->GetIndexArray().GetAt(j))[2];
//				diffuse.a = (float)color->GetDirectArray().GetAt(color->GetIndexArray().GetAt(j))[3];
//
//				m_TempColor.emplace_back(diffuse);
//			}
//		}
//		break;
//
//		case FbxGeometryElement::eByPolygon:
//			break;
//
//		case FbxGeometryElement::eByPolygonVertex:
//			// リファレンスモードの判別
//			switch (referenceMode) {
//			case FbxGeometryElement::eIndexToDirect:
//			{
//				for (int j = 0; j < m_IndexCount; ++j) {
//					COLOR diffuse = COLOR(1, 1, 1, 1);
//					diffuse.r = (float)color->GetDirectArray().GetAt(color->GetIndexArray().GetAt(j))[0];
//					diffuse.g = (float)color->GetDirectArray().GetAt(color->GetIndexArray().GetAt(j))[1];
//					diffuse.b = (float)color->GetDirectArray().GetAt(color->GetIndexArray().GetAt(j))[2];
//					diffuse.a = (float)color->GetDirectArray().GetAt(color->GetIndexArray().GetAt(j))[3];
//
//					m_TempColor.emplace_back(diffuse);
//				}
//			}
//			break;
//
//			case FbxGeometryElement::eDirect:
//				break;
//
//			case FbxGeometryElement::eIndex:
//				break;
//
//			default:
//				break;
//			}
//			break;
//
//		default:
//			break;
//		}
//	}
//
//	// 入れた色が足りなかったら白で追加する
//	if (m_TempColor.size() != m_IndexCount)
//	{
//		for (int j = (int)m_TempColor.size(); j < m_IndexCount; ++j)
//		{
//			m_TempColor.emplace_back(COLOR(1, 1, 1, 1));
//		}
//	}
//}
//
////======================================================================
//// 
////======================================================================
//HRESULT CFBX::CreateModelData(MODEL_& model) {
//	if (m_MeshMaterialList.size() / 3 == 1) {
//		std::vector<int> index;
//		for (int i = 0; i < m_IndexCount; ++i) {
//			index.emplace_back(i);
//		}
//		if (FAILED(CreateVeretx(model, (int)index.size(), &index[0], m_TempUVSet[0], m_TempUVSet))) {
//			return E_FAIL;
//		}
//	}
//	else {
//		m_PolygonCount = 0;
//		// マテリアルの最大値を出す
//		int materialMax = 0;
//		for (int i = 0; i < (int)m_MeshMaterialList.size(); ++i) {
//			if (materialMax < m_MeshMaterialList[i]) {
//				materialMax = m_MeshMaterialList[i];
//			}
//		}
//		materialMax++;
//
//		// マテリアルの数だけ繰り返す
//		for (int i = 0; i < materialMax; ++i) {
//			// マテリアルを構成するインデックスの数
//			std::vector<int> index;
//			for (int j = 0; j < (int)m_MeshMaterialList.size(); ++j) {
//				if (m_MeshMaterialList[j] == i) {
//					index.emplace_back(j);
//				}
//			}
//
//			m_PolygonCount = index.size() / 3;
//			if (FAILED(CreateVeretx(model, (int)index.size(), &index[0], m_TempUVSet[m_MaterialCount[1]], m_TempUVSet))) {
//				return E_FAIL;
//			}
//
//			m_MaterialCount[1]++;
//		}
//	}
//
//	ReleaseTempObj();
//
//	return S_OK;
//}
//
////======================================================================
//// 
////======================================================================
//HRESULT CFBX::CreateVeretx(MODEL_& model, int indexNum, const int* index, UVSet uv, std::vector<UVSet>& uvset) {
//	UINT size = m_TempVertex.size();
//
//	if (m_TempTangent.size() != size) {
//		MessageBox(NULL, "Tangentがありません。全て0を代入します。", "警告", MB_OK | MB_ICONINFORMATION);
//
//		for (UINT i = m_TempTangent.size(); i < size; ++i) {
//			m_TempTangent.emplace_back(XMFLOAT3(0, 0, 0));
//		}
//	}
//
//	if (m_TempVertex.size() == size && m_TempNormal.size() == size /*&& m_TempTexcoord[0].texcoord.size() == size*/ && m_TempColor.size() == size) {
//		MESH tempMesh;
//
//		tempMesh.name = m_TempName;
//		tempMesh.frameTransMtx = XMMatrixIdentity();
//		auto& m = tempMesh.material;
//		m.ambient = COLOR(0.3f, 0.3f, 0.3f, 0.3f);
//		m.diffuse = COLOR(1, 1, 1, 1);
//		m.emission = COLOR(0, 0, 0, 0);
//		m.specular = COLOR(0, 0, 0, 0);
//		m.power = 0;
//		for (auto& t : m.texture) { t = 0; }
//		for (auto& n : m.textureName) { n = ""; }
//
//		for (int i = 0; i < indexNum; ++i)
//		{
//			VERTEX temp;
//			temp.position = m_TempVertex[index[i]].position;
//			temp.normal = m_TempNormal[index[i]];
//
//			if(m_TempTexcoord.size() != 0)
//				temp.texcoord = m_TempTexcoord[0].texcoord[index[i]];
//
//			temp.color = m_TempColor[index[i]];
//			temp.tangent = m_TempTangent[index[i]];
//
//			temp.boneIndex.x = m_TempVertex[index[i]].boneData[0].boneIndex;
//			temp.boneIndex.y = m_TempVertex[index[i]].boneData[1].boneIndex;
//			temp.boneIndex.z = m_TempVertex[index[i]].boneData[2].boneIndex;
//			temp.boneIndex.w = m_TempVertex[index[i]].boneData[3].boneIndex;
//
//			temp.weight.x = m_TempVertex[index[i]].boneData[0].weight;
//			temp.weight.y = m_TempVertex[index[i]].boneData[1].weight;
//			temp.weight.z = m_TempVertex[index[i]].boneData[2].weight;
//			temp.weight.w = m_TempVertex[index[i]].boneData[3].weight;
//
//			tempMesh.vertex.emplace_back(temp);
//			tempMesh.index.emplace_back((indexNum - 1) - i);
//		}
//		tempMesh.material.textureName[static_cast<int>(MaterialType::Diffuse)] = uv.texName;
//
//		if (uvset.size() >= 2) {
//			if (uvset[1].type == MaterialType::Normal) {
//				tempMesh.material.textureName[static_cast<int>(MaterialType::Normal)] = uvset[1].texName;
//			}
//		}
//
//		for (auto& name : tempMesh.material.textureName) {
//			std::string extension;
//			for (int i = name.size() - 1; i > 0 && name[i] != '.'; --i) {
//				extension.insert(extension.begin(), name[i]);
//			}
//			if (extension == "tga") {
//				for (int i = name.size() - 1; i > 0 && name[i] != '.'; --i) {
//					name.pop_back();
//				}
//				name += "png";
//			}
//		}
//
//		// バッファーの設定														  
//		D3D11_BUFFER_DESC VertexBufferDesc;
//		ZeroMemory(&VertexBufferDesc, sizeof(VertexBufferDesc));
//		VertexBufferDesc.ByteWidth = sizeof(tempMesh.vertex[0]) * tempMesh.vertex.size();
//		VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//		VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//		VertexBufferDesc.CPUAccessFlags = 0;
//		VertexBufferDesc.MiscFlags = 0;
//		VertexBufferDesc.StructureByteStride = 0;
//
//		// 初期化データの指定
//		D3D11_SUBRESOURCE_DATA VertexData;
//		ZeroMemory(&VertexData, sizeof(VertexData));
//		VertexData.pSysMem = &tempMesh.vertex[0];
//		VertexData.SysMemPitch = 0;
//		VertexData.SysMemSlicePitch = 0;
//
//		// デバイスに設定
//		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&VertexBufferDesc, &VertexData, &tempMesh.buffer.vertexBuffer))) {
//			// 頂点情報の設定に失敗
//			MessageBox(NULL, "頂点情報の設定に失敗しました", "エラー", MB_OK);
//		}
//
//		// バッファーの設定
//		D3D11_BUFFER_DESC IndexBufferDesc;
//		ZeroMemory(&IndexBufferDesc, sizeof(IndexBufferDesc));
//		IndexBufferDesc.ByteWidth = sizeof(tempMesh.index[0]) * tempMesh.index.size();
//		IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//		IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//		IndexBufferDesc.CPUAccessFlags = 0;
//		IndexBufferDesc.MiscFlags = 0;
//		IndexBufferDesc.StructureByteStride = 0;
//
//		// 初期化データの指定
//		D3D11_SUBRESOURCE_DATA IndexData;
//		ZeroMemory(&IndexData, sizeof(IndexData));
//		IndexData.pSysMem = &tempMesh.index[0];
//		IndexData.SysMemPitch = 0;
//		IndexData.SysMemSlicePitch = 0;
//
//		// デバイスに設定
//		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&IndexBufferDesc, &IndexData, &tempMesh.buffer.indexBuffer))) {
//			// インデックスバッファーの設定に失敗
//			MessageBox(NULL, "インデックスバッファーの設定に失敗しました", "エラー", MB_OK);
//		}
//
//		tempMesh.buffer.indexCount = indexNum;
//		
//		//// テクスチャの読み込み
//		//if (uv.texName != "") {
//		//	tempMesh.texture = new CTexture();
//		//	tempMesh.texture->Load(uv.texName.c_str());
//		//}
//
//		model.mesh.emplace_back(tempMesh);
//	}
//	else {
//		MessageBox(NULL, "頂点情報の数が合いません", "エラー", MB_OK | MB_ICONINFORMATION);
//		return E_FAIL;
//	}
//
//	return S_OK;
//}
//
////======================================================================
//// 
////======================================================================
//void CFBX::CreateMtx(XMMATRIX& mtx, const FbxMatrix fbxMtx) {
//	for (int mtxXCnt = 0; mtxXCnt < 4; mtxXCnt++)
//	{
//		for (int mtxYCnt = 0; mtxYCnt < 4; mtxYCnt++)
//		{
//			mtx.r[mtxYCnt].m128_f32[mtxXCnt] = (float)fbxMtx.Get(mtxYCnt, mtxXCnt);
//		}
//	}
//}
//
////======================================================================
//// 一時情報の解放
////======================================================================
//void CFBX::ReleaseTempObj() {
//	m_TempName = "";
//	std::vector<VERTEXPOINTBONE>().swap(m_TempPoint);
//	std::vector<VERTEXPOINTBONE>().swap(m_TempVertex);
//	std::vector<XMFLOAT3>().swap(m_TempNormal);
//	std::vector<XMFLOAT3>().swap(m_TempTangent);
//	std::vector<COLOR>().swap(m_TempColor);
//	std::vector<FBXUV>().swap(m_TempTexcoord);
//	std::vector<UVSet>().swap(m_TempUVSet);
//	std::vector<FBXANIMATION>().swap(m_TempAnim);
//}
