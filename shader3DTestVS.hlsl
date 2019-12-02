cbuffer ConstantBuffer : register(b0)   //Shader.cppから転送される
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
    float4 outSpecular : COROL1;
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
    float light = 0.5 -dot(worldNormal, Light.Direction) * 0.5; //真上から光がきたと仮定する(長さは１)
    light = saturate(light);    //0以下を0に、1以上を1にする関数
    output.outDiffuse = input.inDiffuse * light;    //ライトを最後にかける
    output.outDiffuse += Light.Diffuse;
    
    //スペキュラー設定
    float4 worldPosition = mul(input.inPosition, World);
    float3 refv = reflect(Light.Direction.xyz, worldNormal.xyz);    //反射ベクトルを求める    １、反射させる光　２、反射する法線
    refv = normalize(refv); //正規化
    float3 eyev = worldPosition - CameraPosition;   //視線ベクトル    カメラから面の頂点までのベクトル
    eyev = normalize(eyev); //正規化
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10);   //10乗   大きくすると強くなり、小さくすると弱くなる
    output.outSpecular = specular;
    
    
    return output; //戻り値
}