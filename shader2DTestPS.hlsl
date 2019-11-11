void main(in float4 inPosition : SV_POSITION,
          in float4 inDiffuse : COLOR0,
          out float4 outDiffuse : SV_Target)
{
    outDiffuse = inDiffuse;
    //outDiffuse = float4(1.0f, 0.0f, 1.0f, 1.0f);
}