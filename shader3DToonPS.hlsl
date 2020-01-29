//*****************************************************************************
// ÉOÉçÅ[ÉoÉãïœêî
//*****************************************************************************
//Texture2D g_Texture : register(t0);
Texture2D g_Texture[2] : register(t0);
SamplerState g_SamplerState : register(s0);

cbuffer ConstantBuffer : register(b0) //Shader.cppÇ©ÇÁì]ëóÇ≥ÇÍÇÈ
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
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
    float4 outDiffuse;
    
    input.inNormal = normalize(input.inNormal);
    float3 eye = input.inWorldPosition.xyz - CameraPosition.xyz;
    eye = normalize(eye);
    float light = 0.5 - dot(input.inNormal.xyz, float3(0.0, -1.0, 0.0)) * 0.5;
    float facing = -dot(input.inNormal.xyz, eye);
    float2 toonTexCoord;
    toonTexCoord.x = light;
    toonTexCoord.y = facing;
    
    outDiffuse = g_Texture[1].Sample(g_SamplerState, input.inTexCoord);
    outDiffuse *= g_Texture[0].Sample(g_SamplerState, toonTexCoord);

    return outDiffuse;
    
}