//*****************************************************************************
// グローバル変数
//*****************************************************************************
//Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);
Texture2D g_DepthTex : register(t0);
//SamplerState g_DepthSamplerState : register(s1);

cbuffer ConstantBuffer : register(b0) //Shader.cppから転送される
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

cbuffer LightBuffer : register(b1) //Shader.cppから転送される
{
    LIGHT Light;
}

struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float4 inDiffuse : COLOR0;
   // float2 inTexCoord : TEXCOORD1;
    float4 inDepthTexCoord : TEXCOORD0;
    float4 inSpecular : COROL1;
    float4 inWorldPosition : POSITION1;
    float4 inNormal : NORMAL0;
};

float4 main(in PS_IN input) : SV_Target
{
    float4 outDiffuse;
    
    input.inDepthTexCoord /= input.inDepthTexCoord.w;
    input.inDepthTexCoord.x = input.inDepthTexCoord.x * 0.5 + 0.5;
    input.inDepthTexCoord.y = -input.inDepthTexCoord.y * 0.5 + 0.5;
    
    float depth = g_DepthTex.Sample(g_SamplerState, input.inDepthTexCoord.xy).x;
    if (depth < input.inDepthTexCoord.z - 0.01)//0.01はバイアス
        outDiffuse.rgb = 0.0f;
    else
        outDiffuse.rgb = 1.0f;
        //g_Texture.Sample(g_SamplerState, input.inTexCoord);
    //outDiffuse.rgb = depth;
    outDiffuse.a = 1.0f;
    return outDiffuse;
}