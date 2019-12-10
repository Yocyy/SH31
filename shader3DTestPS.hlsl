//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Texture2D g_Texture : register(t0);
//Texture2D g_Texture[2] : register(t0);
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
};

float4 main(in PS_IN input) : SV_Target
{
    float4 outDiffuse;
    outDiffuse = g_Texture.Sample(g_SamplerState, input.inTexCoord);    //�摜�̃��\�[�X����摜��\��
    //�s�N�Z�����C�e�B���O
    input.inNormal = normalize(input.inNormal);
    float light = 0.5 - dot(input.inNormal.xyz, Light.Direction.xyz) * 0.5; //�^�ォ����������Ɖ��肷��(�����͂P)
    light = saturate(light); //0�ȉ���0�ɁA1�ȏ��1�ɂ���֐�
    outDiffuse *= light;
    outDiffuse.a = 1.0;
    
    //�X�y�L�����[�ݒ�
    float3 refv = reflect(Light.Direction.xyz, input.inNormal.xyz); //���˃x�N�g�������߂�    �P�A���˂�������@�Q�A���˂���@��
    refv = normalize(refv); //���K��
    float3 eyev = input.inWorldPosition - CameraPosition; //�����x�N�g��    �J��������ʂ̒��_�܂ł̃x�N�g��
    eyev = normalize(eyev); //���K��
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10); //10��   �傫������Ƌ����Ȃ�A����������Ǝキ�Ȃ�
    outDiffuse += specular;
    
    
    //outDiffuse *= input.inDiffuse;
    //outDiffuse += input.inSpecular;
    //outDiffuse.a = 1.0f;
    
   //�}���`�e�N�X�`���ݒ�
    //outDiffuse = g_Texture[0].Sample(g_SamplerState, input.inTexCoord);
    //outDiffuse *= g_Texture[1].Sample(g_SamplerState, input.inTexCoord);

    //�O���[�X�P�[��(����)
    //outDiffuse.rgb = (outDiffuse.r + outDiffuse.g + outDiffuse.b) * 0.3333f;

    //�O���[�X�P�[��(�P�x)
    //outDiffuse.rgb = outDiffuse.r * 0.299 + outDiffuse.g * 0.587 + outDiffuse.b * 0.114;

    //�Z�s�A
    //outDiffuse.r *= 1.07;
    //outDiffuse.g *= 0.74;
    //outDiffuse.b *= 0.43;
    
    return outDiffuse;
}