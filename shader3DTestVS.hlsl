cbuffer ConstantBuffer : register(b0)   //Shader.cpp����]�������
{
    matrix World;
    matrix View;
    matrix Projection;
}

struct VS_IN
{
    float4 inPosition : POSITION0;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
};

struct VS_OUT
{
    float4 outPosition : SV_POSITION;
    float4 outDiffuse : COLOR0;
    float2 outTexCoord : TEXCOORD0;
};

void main(in VS_IN input, out VS_OUT output)
{
    matrix wvp;
    wvp = mul(World, View); //�}�g���N�X
    wvp = mul(wvp, Projection); //�}�g���N�X��Z

    output.outDiffuse = input.inDiffuse;
    output.outPosition = mul(input.inPosition, wvp); //���W�Ԋ�
    output.outTexCoord = input.inTexCoord;
}