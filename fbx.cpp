////======================================================================
////
//// FBX�ǂݍ���[fbx.cpp]
////
////======================================================================
//
////**********************************************************************
//// �C���N���[�h�w�b�_�[
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
//// �}�N����`
////**********************************************************************
//#ifdef IOS_REF
//#undef  IOS_REF
//#define IOS_REF (*(m_pFbxManager->GetIOSettings()))
//#endif
//
//
////======================================================================
//// �R���X�g���N�^
////======================================================================
//CFBX::CFBX() {
//
//}
//
////======================================================================
//// �f�X�g���N�^
////======================================================================
//CFBX::~CFBX() {
//
//}
//
////======================================================================
//// FBX�̓ǂݍ���
////======================================================================
//MODEL_ CFBX::Load(const char* FileName) {
//	// �t�@�C�����ۑ�
//	m_FileName = FileName;
//
//	// Fbx�Ǘ������쐬
//	FbxManager* pFbxManager = FbxManager::Create();
//	if (!pFbxManager) {
//		// FbxManager�̍쐬�Ɏ��s
//		MessageBox(NULL, "FbxManager�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
//		return MODEL_();
//	}
//
//	// Fbx������������o����쐬
//	FbxImporter* pFbxImporter = FbxImporter::Create(pFbxManager, "");
//	if (!pFbxImporter) {
//		// FbxImporter�̍쐬�Ɏ��s
//		MessageBox(NULL, "FbxImporter�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
//		return MODEL_();
//	}
//
//	// Scene�I�u�W�F�N�g��Fbx�t�@�C�����̏��𗬂�����
//	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "");
//	if (!pFbxImporter) {
//		// FbxScene�̍쐬�Ɏ��s
//		MessageBox(NULL, "FbxScene�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
//		return MODEL_();
//	}
//
//	// Fbx�t�@�C�����J��
//	if (!pFbxImporter->Initialize(FileName)) {
//		// Fbx�t�@�C�����J���̂Ɏ��s
//		MessageBox(NULL, "Fbx�t�@�C�����J���̂Ɏ��s���܂���", "�G���[", MB_OK);
//		return MODEL_();
//	}
//
//	// pFbxScene��Fbx�t�@�C����ǂݍ���
//	if (!pFbxImporter->Import(pFbxScene)) {
//		// Fbx�t�@�C���̓ǂݍ��݂Ɏ��s
//		MessageBox(NULL, "Fbx�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
//		return MODEL_();
//	}
//
//	// �g����������
//	if (pFbxImporter) {
//		pFbxImporter->Destroy();
//		pFbxImporter = NULL;
//	}
//
//	// �����߂Ƃ�[
//	FbxGeometryConverter GeometryConverter(pFbxManager);
//	// �|���S�������ׂĎO�p�`��
//	GeometryConverter.Triangulate(pFbxScene, true);
//	// �k�ރ��b�V�����N���[���A�b�v�܂��͍폜(�N���[���A�b�v���ꂽ���b�V���������ɂȂ�ƁA���S�ɍ폜����܂�)
//	GeometryConverter.RemoveBadPolygonsFromMeshes(pFbxScene);
//	//// �}�e���A�����ƂɃ��b�V���𕪊�
//	//GeometryConverter.SplitMeshesPerMaterial(pFbxScene, true);
//
//	// �m�[�h�̎擾
//	FbxNode* pFbxRootNode = pFbxScene->GetRootNode();
//	if (!pFbxRootNode) {
//		// �m�[�h�̎擾�Ɏ��s
//		MessageBox(NULL, "�m�[�h�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
//		return MODEL_();
//	}
//
//	// ���b�V���擾
//	GetMesh(pFbxRootNode);
//
//	// �Ԃ��̃��f���\����
//	MODEL_ model;
//
//	// ���b�V�����擾
//	if (FAILED(GetMeshData(pFbxRootNode, model))) {
//		// ���b�V�����̎擾�Ɏ��s
//		MessageBox(NULL, "���b�V�����̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
//		return MODEL_();
//	}
//
//	// Fbx�S�J��
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
//	//// FBXManager�̐���
//	//m_pFbxManager = FbxManager::Create();
//
//	//// FBXManager���������ꂽ���m�F
//	//if (!m_pFbxManager)
//	//	assert(false);
//
//	//// FBX�ɑ΂�����o�͂��`����
//	//FbxIOSettings* pFbxIO = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
//	//m_pFbxManager->SetIOSettings(pFbxIO);
//
//	//// ���s�\�ȃf�B���N�g��(�I�v�V����)����v���O�C�������[�h
//	//FbxString lPath = FbxGetApplicationDirectory();
//	//m_pFbxManager->LoadPluginsDirectory(lPath.Buffer());
//
//	//// Fbx�V�[���𐶐�
//	//m_pFbxScene = FbxScene::Create(m_pFbxManager, "Scene");
//
//	//// Fbx�V�[�����������ꂽ���m�F
//	//if (!m_pFbxScene)
//	//	assert(false);
//
//	//// �o�[�W�������W���[�ԍ��A�o�[�W�����}�C�i�[�ԍ��A�o�[�W�������r�W�����ԍ�
//	//int lSDKMajor, lSDKMinor, lSDKRevision;
//
//	//// ���̃o�[�W������FBXSDK�̌��݂̃f�t�H���g��FBX�t�@�C���`���̃o�[�W�����ԍ����擾
//	//FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);
//
//	//// FBX�C���|�[�^������������
//	//FbxImporter* pImporter = FbxImporter::Create(m_pFbxManager, "");
//
//	//// FBX�t�@�C���̓ǂݍ��݂����s����
//	//const bool lImportStatus = pImporter->Initialize(FileName, -1, m_pFbxManager->GetIOSettings());
//
//	//// �o�[�W�������W���[�ԍ��A�o�[�W�����}�C�i�[�ԍ��A�o�[�W�������r�W�����ԍ�
//	//int lFileMajor, lFileMinor, lFileRevision;
//
//	//// �t�@�C�������擾
//	//pImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);
//
//	//// �C���|�[�^�̏�񂪐������ꂽ���m�F
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
//	//			// �^�C�����[�h�擾
//	//			FbxGlobalSettings& Set = m_pFbxScene->GetGlobalSettings();
//	//			FbxTime::EMode timeMode = Set.GetTimeMode();
//
//	//			FBXANIMATION temp;
//	//			temp.name = lTakeInfo->mName;
//
//	//			// �A�j���[�V�������n�܂鎞�ԂƏI��鎞��
//	//			FbxTime start = lTakeInfo->mLocalTimeSpan.GetStart();
//	//			FbxTime stop = lTakeInfo->mLocalTimeSpan.GetStop();
//
//	//			//fbx��1�t���[��������̎��Ԑ�
//	//			temp.framePeriod.SetTime(0, 0, 0, 1, 0, timeMode);
//
//	//			// 1�t���[��������Ŋ���΁A�t���[�����ɂȂ�
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
//// ���b�V�����擾
////======================================================================
//void CFBX::GetMesh(FbxNode* pNode) {
//	// ���[�g�m�[�h�̎q�m�[�h��
//	int ChildCount = pNode->GetChildCount();
//
//	// �q�m�[�h�̐������T��
//	for (int i = 0; i < ChildCount; i++) {
//
//		// �q�m�[�h���擾
//		FbxNode*			pChild = pNode->GetChild(i);
//		// �m�[�h����
//		FbxNodeAttribute*	pAttribute = pChild->GetNodeAttribute();
//
//		// NULL�m�[�h����
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
//		// ���b�V���T��
//		GetMesh(pNode->GetChild(i));
//	}
//}
//
////======================================================================
//// ���b�V���f�[�^�̎擾
////======================================================================
//HRESULT CFBX::GetMeshData(FbxNode* pNode, MODEL_& model) {
//	m_TempNode.emplace_back(pNode);
//	int childNodeNum = pNode->GetChildCount();
//	FbxMesh* mesh = nullptr;
//
//	for (int i = 0; i < childNodeNum; ++i) {
//		// �q�m�[�h���擾
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
//			// �ǂݍ��񂾐��𑝂₷
//			m_MaterialCount[1]++;
//
//			//�}�e���A���������擾������ċA���ʂ���
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
//// ���_���W�̎擾
////======================================================================
//void CFBX::GetPosition(FbxMesh* pMesh) {
//	// ���b�V���}�e���A�����X�g�̎擾
//	GetMeshMaterialList(pMesh);
//
//	// �����_��
//	m_PointCount = pMesh->GetControlPointsCount();
//	// ���|���S�����̎擾
//	m_PolygonCount = pMesh->GetPolygonCount();
//	// ���C���f�b�N�X���̎擾
//	m_IndexCount = pMesh->GetPolygonVertexCount();
//
//	// ���_�̎擾
//	FbxVector4* vertex = pMesh->GetControlPoints();
//
//	// ���_�̎擾
//	for (int i = 0; i < m_PointCount; ++i)
//	{
//		// ���_�����C���f�b�N�X���Ŏ擾
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
//// ���b�V���ɓ����Ă�}�e���A�����X�g�̎擾
////======================================================================
//void CFBX::GetMeshMaterialList(FbxMesh* pMesh) {
//	// ���g�̉��
//	m_MeshMaterialList.clear();
//
//	// ���b�V���ɕt���Ă���}�e���A���̐��̎擾
//	int layerCount = pMesh->GetLayerCount();
//
//	for (int i = 0; i < layerCount; ++i)
//	{
//		// �}�e���A���̎擾
//		FbxLayerElementMaterial* pMat = pMesh->GetLayer(i)->GetMaterials();
//		if (pMat) {
//			if (pMat->GetReferenceMode() == FbxLayerElement::eIndex || pMat->GetReferenceMode() == FbxLayerElement::eIndexToDirect) {
//				// �}�e���A���̃|���S�������擾
//				int polygonNum = pMat->GetIndexArray().GetCount();
//
//				for (int j = 0; j < polygonNum; ++j) {
//					// �|���S�������Ȃ̂ŃC���f�b�N�X���ɕς���(�O�p���_�����Ă��邽��3�{�ł����͂�)
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
//// �{�[���̎擾
////======================================================================
//void CFBX::GetBone(FbxMesh* pMesh) {
//	// �X�L���̐����擾
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
//		// i�Ԗڂ̃X�L�����擾
//		FbxSkin* skin = (FbxSkin*)(pMesh->GetDeformer(i, FbxDeformer::eSkin));
//
//		// �N���X�^�[�̐����擾
//		int clusterNum = skin->GetClusterCount();
//
//		for (int j = 0; j < clusterNum; ++j)
//		{
//			// j�Ԗڂ̃N���X�^���擾 �N���X�^ �� �{�[��
//			FbxCluster* cluster = skin->GetCluster(j);
//			int			pointNum = cluster->GetControlPointIndicesCount();
//			int*		pointAry = cluster->GetControlPointIndices();
//			double*		weightAry = cluster->GetControlPointWeights();
//			// �{�[���I�t�Z�b�g�s��̎擾
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
//			// �{�[���̉e���x�̎擾
//			for (int k = 0; k < m_PointCount; ++k)
//			{
//				for (int l = 0; l < pointNum; ++l)
//				{
//					// �e�����_�����݂����ꍇ
//					if (pointAry[l] == k)
//					{
//						// �e���x�̎擾
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
//	// �C���f�b�N�X�̎擾
//	int* index = pMesh->GetPolygonVertices();
//
//	// �C���f�b�N�X����
//	for (int i = 0; i < m_IndexCount; ++i)
//	{
//		m_TempVertex.emplace_back(m_TempPoint[index[i]]);
//	}
//}
//
////======================================================================
//// �@���̎擾
////======================================================================
//void CFBX::GetVertexNormal(FbxMesh* pMesh) {
//	// �@�����C���[�̐��擾
//	int normalLayerCount = pMesh->GetElementNormalCount();
//
//	// ���C���[���������
//	for (int i = 0; i < normalLayerCount; ++i)
//	{
//		// �@���Z�b�g���擾
//		FbxGeometryElementNormal* normal = pMesh->GetElementNormal(i);
//		// �}�b�s���O���[�h�̎擾
//		FbxGeometryElement::EMappingMode mapping = normal->GetMappingMode();
//		// ���t�@�����X���[�h�̎擾
//		FbxGeometryElement::EReferenceMode reference = normal->GetReferenceMode();
//
//		// �}�b�s���O���[�h�̔���
//		switch (mapping)
//		{
//		case FbxGeometryElement::eByControlPoint:
//			// ���t�@�����X���[�h�̔���
//			switch (reference)
//			{
//			case FbxGeometryElement::eDirect:
//			{
//				// �@���̐����擾
//				int normalCount = normal->GetDirectArray().GetCount();
//
//				// �@���̐����i�[����
//				std::vector<XMFLOAT3> directNormal;
//				for (int j = 0; j < normalCount; ++j)
//				{
//					XMFLOAT3 temp;
//					// �@���̎擾
//					temp.x = -(float)normal->GetDirectArray().GetAt(j)[0];
//					temp.y = (float)normal->GetDirectArray().GetAt(j)[1];
//					temp.z = (float)normal->GetDirectArray().GetAt(j)[2];
//					directNormal.emplace_back(temp);
//				}
//
//				// �@�����C���f�b�N�X���Ŋi�[
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
//			// ���t�@�����X���[�h�̔���
//			switch (reference)
//			{
//			case FbxGeometryElement::eDirect:
//			{
//				int normalCount = normal->GetDirectArray().GetCount();
//				for (int j = 0; j < normalCount; ++j)
//				{
//					// �@���̎擾
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
//					// �@���̎擾
//					XMFLOAT3 temp;
//					temp.x = -(float)normal->GetDirectArray().GetAt(j)[0];
//					temp.y = (float)normal->GetDirectArray().GetAt(j)[1];
//					temp.z = (float)normal->GetDirectArray().GetAt(j)[2];
//					directNormal.emplace_back(temp);
//				}
//
//				// �C���f�b�N�X���擾
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
//// �^���W�F���g�̎擾
////======================================================================
//void CFBX::GetVertexTangent(FbxMesh* pMesh) {
//	// �@���Z�b�g�����擾
//	int normalLayerCount = pMesh->GetElementTangentCount();
//
//	// ���C���[���������
//	for (int i = 0; i < normalLayerCount; ++i)
//	{
//		// �@���Z�b�g���擾
//		FbxGeometryElementTangent* tangent = pMesh->GetElementTangent(i);
//		// �}�b�s���O���[�h�̎擾
//		FbxGeometryElement::EMappingMode mapping = tangent->GetMappingMode();
//		// ���t�@�����X���[�h�̎擾
//		FbxGeometryElement::EReferenceMode reference = tangent->GetReferenceMode();
//
//		// �}�b�s���O���[�h�̔���
//		switch (mapping)
//		{
//		case FbxGeometryElement::eByControlPoint:
//			// ���t�@�����X���[�h�̔���
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
//					// �@���̎擾
//					temp.x = -(float)tangent->GetDirectArray().GetAt(j)[0];
//					temp.y = (float)tangent->GetDirectArray().GetAt(j)[1];
//					temp.z = (float)tangent->GetDirectArray().GetAt(j)[2];
//					directNormal.emplace_back(temp);
//				}
//
//				// �@�����C���f�b�N�X���Ŋi�[
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
//			// �@�������擾
//			int tangentCount = tangent->GetDirectArray().GetCount();
//			int indexCount = tangent->GetIndexArray().GetCount();
//
//			std::vector<XMFLOAT3> directNormal;
//			for (int j = 0; j < tangentCount; ++j)
//			{
//				// �@���̎擾
//				XMFLOAT3 temp;
//				temp.x = -(float)tangent->GetDirectArray().GetAt(j)[0];
//				temp.y = (float)tangent->GetDirectArray().GetAt(j)[1];
//				temp.z = (float)tangent->GetDirectArray().GetAt(j)[2];
//				directNormal.emplace_back(temp);
//			}
//
//			// �@���̐����C���f�b�N�X�̐��Ɠ����Ȃ炻�̂܂�
//			if (tangentCount == m_IndexCount)
//			{
//				m_TempTangent = directNormal;
//			}
//			// �@���C���f�b�N�X�̐������_�̃C���f�b�N�X�Ɠ�����
//			else if (indexCount == m_IndexCount)
//			{
//				// �C���f�b�N�X���擾
//				int indexCount = tangent->GetIndexArray().GetCount();
//
//				// �C���f�b�N�X���擾
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
//// �e�N�X�`�����W�̎擾
////======================================================================
//void CFBX::GetVertexUV(FbxMesh* pMesh) {
//	// UV�Z�b�g�����擾
//	int UVLayerCount = pMesh->GetElementUVCount();
//
//	for (int i = 0; i < UVLayerCount; ++i) {
//		// UV�o�b�t�@���擾
//		FbxGeometryElementUV* UV = pMesh->GetElementUV(i);
//		// �}�b�s���O���[�h�̎擾
//		FbxGeometryElement::EMappingMode mapping = UV->GetMappingMode();
//		// ���t�@�����X���[�h�̎擾
//		FbxGeometryElement::EReferenceMode reference = UV->GetReferenceMode();
//
//		// �}�b�s���O���[�h�̔���
//		switch (mapping) {
//		case FbxGeometryElement::eByControlPoint:
//			break;
//
//		case FbxGeometryElement::eByPolygonVertex:
//			// ���t�@�����X���[�h�̔���
//			switch (reference) {
//			case FbxGeometryElement::eDirect:
//				break;
//
//			case FbxGeometryElement::eIndexToDirect:
//			{
//				// �C���f�b�N�X���擾
//				int indexCount = UV->GetIndexArray().GetCount();
//
//				// UV��ێ�
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
//				// UVSet�����擾
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
//// �e�N�X�`��
////======================================================================
//void CFBX::GetTextureNames(FbxMesh* pMesh, const char* materialType, std::string& get) {
//	int textureNum = 0;
//
//	// ���b�V������m�[�h���擾
//	FbxNode* node = pMesh->GetNode();
//
//	// �}�e���A���̐����擾
//	int materialCnt = node->GetMaterialCount();
//	// �}�e���A���̐������J��Ԃ�
//	for (int i = 0; i < materialCnt; i++)
//	{
//		// �}�e���A�����擾
//		FbxSurfaceMaterial* material = node->GetMaterial(i);
//		FbxProperty			prop = material->FindProperty(materialType);
//
//		// FbxLayeredTexture �̐����擾
//		int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();
//		// �A�^�b�`���ꂽ�e�N�X�`���� FbxLayeredTexture �̏ꍇ
//		if (0 < layeredTextureCount)
//		{
//			// �A�^�b�`���ꂽ�e�N�X�`���̐������J��Ԃ�
//			for (int j = 0; j < layeredTextureCount; ++j)
//			{
//				// �e�N�X�`�����擾
//				FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
//				// ���C���[�����擾
//				int textureCount = 1;
//
//				// ���C���[�������J��Ԃ�
//				for (int k = 0; k < textureCount; ++k)
//				{
//					// �e�N�X�`�����擾
//					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);
//					if (texture) {
//						UVSet temp;
//						// �e�N�X�`�������擾
//						temp.texName = std::string(texture->GetRelativeFileName());
//						get = temp.texName;
//						// UVSet�����擾
//						temp.uvSetName = std::string(texture->UVSet.GetName());
//
//						m_TempUVSet.emplace_back(temp);
//
//						//--- UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ� ---//
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
//			// �e�N�X�`�������擾
//			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
//			if (fileTextureCount > 0)
//			{
//				// �e�N�X�`���̐������J��Ԃ�
//				for (int j = 0; j < fileTextureCount; j++)
//				{
//					// �e�N�X�`�����擾
//					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
//					if (texture)
//					{
//						UVSet temp;
//						// �e�N�X�`�������擾
//						temp.texName = m_FileName;
//						// �e�N�X�`���̃f�B���N�g���̓��f���Ɠ���
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
//						// UVSet�����擾
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
//										// �e�N�X�`�������擾
//										temp.texName = m_FileName;
//										// �e�N�X�`���̃f�B���N�g���̓��f���Ɠ���
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
//		// �ݒ肪�Ȃ�������
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
//// ���_�F�擾
////======================================================================
//void CFBX::GetVertexColor(FbxMesh* pMesh) {
//	// ���_�F�����擾
//	int vColorLayerCount = pMesh->GetElementVertexColorCount();
//
//	// ���_�J���[�ݒ肪�Ȃ�������
//	if (vColorLayerCount == 0) {
//		for (int i = 0; i < m_IndexCount; ++i)
//		{
//			COLOR temp = COLOR(1, 1, 1, 1);
//			m_TempColor.emplace_back(temp);
//		}
//		return;
//	}
//
//	// ���C���[���������
//	for (int i = 0; i < vColorLayerCount; ++i)
//	{
//		// ���_�J���[�Z�b�g���擾
//		FbxGeometryElementVertexColor* color = pMesh->GetElementVertexColor(i);
//		// �}�b�s���O���[�h�̎擾
//		FbxGeometryElement::EMappingMode mappingMode = color->GetMappingMode();
//		// ���t�@�����X���[�h�̎擾
//		FbxGeometryElement::EReferenceMode referenceMode = color->GetReferenceMode();
//
//		// �}�b�s���O���[�h�̔���
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
//			// ���t�@�����X���[�h�̔���
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
//	// ���ꂽ�F������Ȃ������甒�Œǉ�����
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
//		// �}�e���A���̍ő�l���o��
//		int materialMax = 0;
//		for (int i = 0; i < (int)m_MeshMaterialList.size(); ++i) {
//			if (materialMax < m_MeshMaterialList[i]) {
//				materialMax = m_MeshMaterialList[i];
//			}
//		}
//		materialMax++;
//
//		// �}�e���A���̐������J��Ԃ�
//		for (int i = 0; i < materialMax; ++i) {
//			// �}�e���A�����\������C���f�b�N�X�̐�
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
//		MessageBox(NULL, "Tangent������܂���B�S��0�������܂��B", "�x��", MB_OK | MB_ICONINFORMATION);
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
//		// �o�b�t�@�[�̐ݒ�														  
//		D3D11_BUFFER_DESC VertexBufferDesc;
//		ZeroMemory(&VertexBufferDesc, sizeof(VertexBufferDesc));
//		VertexBufferDesc.ByteWidth = sizeof(tempMesh.vertex[0]) * tempMesh.vertex.size();
//		VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//		VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//		VertexBufferDesc.CPUAccessFlags = 0;
//		VertexBufferDesc.MiscFlags = 0;
//		VertexBufferDesc.StructureByteStride = 0;
//
//		// �������f�[�^�̎w��
//		D3D11_SUBRESOURCE_DATA VertexData;
//		ZeroMemory(&VertexData, sizeof(VertexData));
//		VertexData.pSysMem = &tempMesh.vertex[0];
//		VertexData.SysMemPitch = 0;
//		VertexData.SysMemSlicePitch = 0;
//
//		// �f�o�C�X�ɐݒ�
//		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&VertexBufferDesc, &VertexData, &tempMesh.buffer.vertexBuffer))) {
//			// ���_���̐ݒ�Ɏ��s
//			MessageBox(NULL, "���_���̐ݒ�Ɏ��s���܂���", "�G���[", MB_OK);
//		}
//
//		// �o�b�t�@�[�̐ݒ�
//		D3D11_BUFFER_DESC IndexBufferDesc;
//		ZeroMemory(&IndexBufferDesc, sizeof(IndexBufferDesc));
//		IndexBufferDesc.ByteWidth = sizeof(tempMesh.index[0]) * tempMesh.index.size();
//		IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//		IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//		IndexBufferDesc.CPUAccessFlags = 0;
//		IndexBufferDesc.MiscFlags = 0;
//		IndexBufferDesc.StructureByteStride = 0;
//
//		// �������f�[�^�̎w��
//		D3D11_SUBRESOURCE_DATA IndexData;
//		ZeroMemory(&IndexData, sizeof(IndexData));
//		IndexData.pSysMem = &tempMesh.index[0];
//		IndexData.SysMemPitch = 0;
//		IndexData.SysMemSlicePitch = 0;
//
//		// �f�o�C�X�ɐݒ�
//		if (FAILED(CRenderer::GetDevice()->CreateBuffer(&IndexBufferDesc, &IndexData, &tempMesh.buffer.indexBuffer))) {
//			// �C���f�b�N�X�o�b�t�@�[�̐ݒ�Ɏ��s
//			MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�[�̐ݒ�Ɏ��s���܂���", "�G���[", MB_OK);
//		}
//
//		tempMesh.buffer.indexCount = indexNum;
//		
//		//// �e�N�X�`���̓ǂݍ���
//		//if (uv.texName != "") {
//		//	tempMesh.texture = new CTexture();
//		//	tempMesh.texture->Load(uv.texName.c_str());
//		//}
//
//		model.mesh.emplace_back(tempMesh);
//	}
//	else {
//		MessageBox(NULL, "���_���̐��������܂���", "�G���[", MB_OK | MB_ICONINFORMATION);
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
//// �ꎞ���̉��
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
