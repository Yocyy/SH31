//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//Texture2D g_Texture : register(t0);
Texture2D g_Texture[3] : register(t0);
SamplerState g_SamplerState : register(s0);

cbuffer ConstantBuffer : register(b0) //Shader.cpp����]�������
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
}

struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer LightBuffer : register(b1) //Shader.cpp����]�������
{
    LIGHT Light;
}

struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
    float4 inSpecular : COROL1;
    float4 inWorldPosition : POSITION1;
    float4 inNormal : NORMAL0;
    float4 inBinormal : BINORMAL0;
    float4 inTangent : TANGENT0;
};

float4 main(in PS_IN input) : SV_Target
{
    float4 eyev = input.inWorldPosition - CameraPosition; //�����x�N�g��    �J��������ʂ̒��_�܂ł̃x�N�g��
    eyev = normalize(eyev); //���K��
    
    matrix mat = { input.inBinormal, -input.inTangent, input.inNormal, float4(0, 0, 0, 1) };
    matrix invmat = transpose(mat); //�t�s��
    float3 invEyev = mul(eyev, invmat).xyz;
    float heightMap = (g_Texture[2].Sample(g_SamplerState, input.inTexCoord).r - 0.5) * 0.2; //50���O���[
    input.inTexCoord += invEyev.xy * -heightMap;
    
    float4 outDiffuse;
    float4 normalMap = g_Texture[0].Sample(g_SamplerState, input.inTexCoord); //�m�[�}���}�b�v�擾�A�F�������k��������0.0�`1.0
    normalMap = (normalMap * 2.0) - 1.0; //0.0�`1.0��-1.0�`1.0�ɕϊ�
    normalMap = (normalMap.x * input.inBinormal) + (normalMap.y * input.inTangent) + (normalMap.z * input.inNormal); //�e�N�X�`���̌����Ɩ@���̌��������킹��
    normalMap.w = 0.0;
    normalMap = normalize(normalMap); //���K��
   
    //�X�y�L�����[�ݒ�
    float3 refv;
    //refv = reflect(Light.Direction.xyz, input.inNormal.xyz);
    refv = reflect(Light.Direction.xyz, normalMap.xyz); //���˃x�N�g�������߂�    �P�A���˂�������@�Q�A���˂���@��
    refv = normalize(refv); //���K��
 
    outDiffuse = g_Texture[1].Sample(g_SamplerState, input.inTexCoord); //�e�N�X�`���̐F������Z
    outDiffuse *= input.inDiffuse; //�摜�̃��\�[�X����摜��\��
    //�s�N�Z�����C�e�B���O
    float light = 0.5 - dot(normalMap.xyz, Light.Direction.xyz) * 0.5; //�^�ォ����������Ɖ��肷��(�����͂P)
    light = saturate(light); //0�ȉ���0�ɁA1�ȏ��1�ɂ���֐�
    outDiffuse *= light;
    outDiffuse.a = 1.0;
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10); //10��   �傫������Ƌ����Ȃ�A����������Ǝキ�Ȃ�
    outDiffuse += specular;
    
    return outDiffuse;
}