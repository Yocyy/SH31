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
    matrix View;
    matrix Projection;
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
    float4 outDepthTexCoord : TEXCOORD0;
    float2 outTexCoord : TEXCOORD1;
    float4 outSpecular : COROL1;
    float4 outWorldPosition : POSITION1;
    float4 outNormal : NORMAL0;
};

VS_OUT main(in VS_IN input)
{
    VS_OUT output;
    
    matrix wvp;
    wvp = mul(World, View); //�}�g���N�X
    wvp = mul(wvp, Projection); //�}�g���N�X��Z

    output.outWorldPosition = mul(input.inPosition, World);
    input.inNormal.w = 0.0f;
    output.outNormal = mul(input.inNormal, World);
    output.outDiffuse = input.inDiffuse;
    output.outTexCoord = input.inTexCoord;
    output.outPosition = mul(input.inPosition, wvp); //���W�ϊ�
    
    matrix lightwvp;
    lightwvp = mul(World, Light.View);
    lightwvp = mul(lightwvp, Light.Projection);
    output.outDepthTexCoord = mul(input.inPosition, lightwvp);
    
    return output; //�߂�l
}