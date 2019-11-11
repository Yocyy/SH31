cbuffer ConstantBuffer : register(b0)
{
    matrix Projection;
}

void main(in  float4 inPosition  : POSITION0,
          in  float4 inDiffuse   : COLOR0,
          out float4 outPosition : SV_POSITION,
          out float4 outDiffuse  : COLOR0)
{
    outDiffuse = inDiffuse;
    outPosition = mul(inPosition, Projection);
}