cbuffer ConstantBuffer : register(b0)   //Shader.cpp����]�������
{
    matrix World;
    matrix View;
    matrix Projection;
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
    float light = -dot(worldNormal, float4(0.0, -1.0, 0.0, 0.0));   //�^�ォ����������Ɖ��肷��(�����͂P)
    light = saturate(light);    //0�ȉ���0�ɁA1�ȏ��1�ɂ���֐�
    output.outDiffuse = input.inDiffuse * light;    //���C�g���Ō�ɂ�����
    
    return output; //�߂�l
}