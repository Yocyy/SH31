cbuffer ConstantBuffer : register(b0)   //Shader.cppから転送される
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
    wvp = mul(World, View); //マトリクス
    wvp = mul(wvp, Projection); //マトリクス乗算

    output.outDiffuse = input.inDiffuse;
    output.outPosition = mul(input.inPosition, wvp); //座標変換
    output.outTexCoord = input.inTexCoord;
    
    input.inNormal.w = 0.0;     //移動変換を無くして計算する
    float4 worldNormal = mul(input.inNormal, World);    //座標変換
    float light = -dot(worldNormal, float4(0.0, -1.0, 0.0, 0.0));   //真上から光がきたと仮定する(長さは１)
    light = saturate(light);    //0以下を0に、1以上を1にする関数
    output.outDiffuse = input.inDiffuse * light;    //ライトを最後にかける
    
    return output; //戻り値
}