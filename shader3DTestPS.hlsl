//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D g_Texture : register(t0);
//Texture2D g_Texture[2] : register(t0);
SamplerState g_SamplerState : register(s0);

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
};

cbuffer LightBuffer : register(b1) //Shader.cppから転送される
{
    LIGHT Light;
}

struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
    float4 inSpecular : COROL1;
    float4 inWorldPosition : POSITION1;
    float4 inNormal : NORMAL0;
};

float4 main(in PS_IN input) : SV_Target
{
    float4 outDiffuse;
    outDiffuse = g_Texture.Sample(g_SamplerState, input.inTexCoord);    //画像のリソースから画像を表示
    //ピクセルライティング
    input.inNormal = normalize(input.inNormal);
    float light = 0.5 - dot(input.inNormal.xyz, Light.Direction.xyz) * 0.5; //真上から光がきたと仮定する(長さは１)
    light = saturate(light); //0以下を0に、1以上を1にする関数
    outDiffuse *= light;
    outDiffuse.a = 1.0;
    
    //スペキュラー設定
    float3 refv = reflect(Light.Direction.xyz, input.inNormal.xyz); //反射ベクトルを求める    １、反射させる光　２、反射する法線
    refv = normalize(refv); //正規化
    float3 eyev = input.inWorldPosition - CameraPosition; //視線ベクトル    カメラから面の頂点までのベクトル
    eyev = normalize(eyev); //正規化
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10); //10乗   大きくすると強くなり、小さくすると弱くなる
    outDiffuse += specular;
    
    
    //outDiffuse *= input.inDiffuse;
    //outDiffuse += input.inSpecular;
    //outDiffuse.a = 1.0f;
    
   //マルチテクスチャ設定
    //outDiffuse = g_Texture[0].Sample(g_SamplerState, input.inTexCoord);
    //outDiffuse *= g_Texture[1].Sample(g_SamplerState, input.inTexCoord);

    //グレースケール(平均)
    //outDiffuse.rgb = (outDiffuse.r + outDiffuse.g + outDiffuse.b) * 0.3333f;

    //グレースケール(輝度)
    //outDiffuse.rgb = outDiffuse.r * 0.299 + outDiffuse.g * 0.587 + outDiffuse.b * 0.114;

    //セピア
    //outDiffuse.r *= 1.07;
    //outDiffuse.g *= 0.74;
    //outDiffuse.b *= 0.43;
    
    return outDiffuse;
}