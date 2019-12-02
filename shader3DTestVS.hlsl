cbuffer ConstantBuffer : register(b0)   //Shader.cpp����]�������
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

struct VS_IN
{
    float4 inPosition : POSITION0;
    float4 inNormal : NORMAL0;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
};

struct VS_OUT
{
    float4 outPosition : SV_POSITION;
    float4 outDiffuse : COLOR0;
    float2 outTexCoord : TEXCOORD0;
    float4 outSpecular : COROL1;
};

VS_OUT main(in VS_IN input)
{
    VS_OUT output;
    
    matrix wvp;
    wvp = mul(World, View); //�}�g���N�X
    wvp = mul(wvp, Projection); //�}�g���N�X��Z

    output.outDiffuse = input.inDiffuse;
    output.outPosition = mul(input.inPosition, wvp); //���W�ϊ�
    output.outTexCoord = input.inTexCoord;
    
    input.inNormal.w = 0.0;     //�ړ��ϊ��𖳂����Čv�Z����
    float4 worldNormal = mul(input.inNormal, World);    //���W�ϊ�
    float light = 0.5 -dot(worldNormal, Light.Direction) * 0.5; //�^�ォ����������Ɖ��肷��(�����͂P)
    light = saturate(light);    //0�ȉ���0�ɁA1�ȏ��1�ɂ���֐�
    output.outDiffuse = input.inDiffuse * light;    //���C�g���Ō�ɂ�����
    output.outDiffuse += Light.Diffuse;
    
    //�X�y�L�����[�ݒ�
    float4 worldPosition = mul(input.inPosition, World);
    float3 refv = reflect(Light.Direction.xyz, worldNormal.xyz);    //���˃x�N�g�������߂�    �P�A���˂�������@�Q�A���˂���@��
    refv = normalize(refv); //���K��
    float3 eyev = worldPosition - CameraPosition;   //�����x�N�g��    �J��������ʂ̒��_�܂ł̃x�N�g��
    eyev = normalize(eyev); //���K��
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10);   //10��   �傫������Ƌ����Ȃ�A����������Ǝキ�Ȃ�
    output.outSpecular = specular;
    
    
    return output; //�߂�l
}