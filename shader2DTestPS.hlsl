//*****************************************************************************
// ƒOƒ[ƒoƒ‹•Ï”
//*****************************************************************************
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
};

void main(in PS_IN input,out float4 outDiffuse : SV_Target)
{
    outDiffuse = g_Texture.Sample(g_SamplerState, input.inTexCoord);
    //outDiffuse = input.inDiffuse;
    //outDiffuse = float4(1.0f, 0.0f, 1.0f, 1.0f);
}