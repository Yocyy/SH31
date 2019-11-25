//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Texture2D g_Texture : register(t0);
//Texture2D g_Texture[2] : register(t0);
SamplerState g_SamplerState : register(s0);

struct PS_IN
{
    float4 inPosition : SV_POSITION;
    float4 inDiffuse : COLOR0;
    float2 inTexCoord : TEXCOORD0;
};

float4 main(in PS_IN input) : SV_Target
{
    float4 outDiffuse;
    outDiffuse = g_Texture.Sample(g_SamplerState, input.inTexCoord);    //�摜�̃��\�[�X����摜��\��
    
    outDiffuse *= input.inDiffuse;
    
   //�}���`�e�N�X�`���ݒ�
    //outDiffuse = g_Texture[0].Sample(g_SamplerState, input.inTexCoord);
    //outDiffuse *= g_Texture[1].Sample(g_SamplerState, input.inTexCoord);

    //�O���[�X�P�[��(����)
    //outDiffuse.rgb = (outDiffuse.r + outDiffuse.g + outDiffuse.b) * 0.3333f;

    //�O���[�X�P�[��(�P�x)
    //outDiffuse.rgb = outDiffuse.r * 0.299 + outDiffuse.g * 0.587 + outDiffuse.b * 0.114;

    //�Z�s�A
    //outDiffuse.r *= 1.07;
    //outDiffuse.g *= 0.74;
    //outDiffuse.b *= 0.43;
    
    return outDiffuse;
}