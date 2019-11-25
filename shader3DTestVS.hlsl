cbuffer ConstantBuffer : register(b0)   //Shader.cppから転送される
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
    wvp = mul(World, View); //マトリクス
    wvp = mul(wvp, Projection); //マトリクス乗算

    output.outDiffuse = input.inDiffuse;
    output.outPosition = mul(input.inPosition, wvp); //座標返還
    output.outTexCoord = input.inTexCoord;
}