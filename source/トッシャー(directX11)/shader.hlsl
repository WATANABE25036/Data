

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マトリクスバッファ
cbuffer WorldBuffer : register( b0 )
{
	matrix World;
}

cbuffer ViewBuffer : register( b1 )
{
	matrix View;
}

cbuffer ProjectionBuffer : register( b2 )
{
	matrix Projection;
}

// マテリアルバッファ
struct MATERIAL
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	int			noTexSampling;
	float		Dummy[2];//16byte境界用
};

cbuffer MaterialBuffer : register( b3 )
{
	MATERIAL	Material;
}

// ライト用バッファ
struct LIGHT
{
	float4		Direction[10];
	float4		Position[10];
	float4		Diffuse[10];
	float4		Ambient[10];
	float4		Attenuation[10];
	int4		Flags[10];
	int			Enable;
	int			Dummy[3];//16byte境界用
};

cbuffer LightBuffer : register( b4 )
{
	LIGHT		Light;
}


//=============================================================================
// 頂点シェーダ
//=============================================================================
void VertexShaderPolygon( in float4 inPosition		: POSITION0,	// 頂点の位置情報（x, y, z, w）
						  in float4 inNormal		: NORMAL0,		// 頂点の法線ベクトル（x, y, z, w）
						  in float4 inDiffuse		: COLOR0,		// 頂点の拡散反射率（色情報）
						  in float2 inTexCoord		: TEXCOORD0,	// 頂点のテクスチャ座標（x, y）

						  out float4 outPosition	: SV_POSITION,	// スクリーン上の位置情報（x, y, z, w）
						  out float4 outNormal		: NORMAL0,
						  out float2 outTexCoord	: TEXCOORD0,
						  out float4 outDiffuse		: COLOR0
)
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	outPosition = mul(inPosition, wvp);
	outNormal = inNormal;
	outTexCoord = inTexCoord;

	if (Light.Enable == 0) 
	{
		outDiffuse = inDiffuse * Material.Diffuse;
	}
	else
	{
		float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 outColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

		for (int i = 0; i < 10; i++)
		{
			if (Light.Flags[i].y == 1)
			{
                if (Light.Flags[i].x == 1)//ディレクショナルライト
				{
					float4 worldNormal, normal;
					normal = float4(inNormal.xyz, 0.0);
					worldNormal = mul(normal, World);
					worldNormal = normalize(worldNormal);

					float light = 1.0 * -dot(Light.Direction[i].xyz, worldNormal.xyz);

					color = inDiffuse * Material.Diffuse * light * Light.Diffuse[i];
					color += inDiffuse * Material.Ambient * Light.Ambient[i];
				}
                else if (Light.Flags[i].x == 2)//ポイントライト
                {					
                    float4 worldNormal, normal;
                    normal = float4(inNormal.xyz, 0.0);
                    worldNormal = mul(normal, World);
                    worldNormal = normalize(worldNormal);

                    float3 posWorld = mul(inPosition, World);
                    float3 lightDir;
                    lightDir = normalize(posWorld - Light.Position[i]);
                    float light = 1.0 * -dot(lightDir.xyz, worldNormal.xyz);

                    color = inDiffuse * Material.Diffuse * light * Light.Diffuse[i];
                    color += inDiffuse * Material.Ambient * Light.Ambient[i];
                    float distance = length(posWorld - Light.Position[i]);

                    float att = saturate((Light.Attenuation[i].x - distance) / Light.Attenuation[i].x);
                    color *= att;
					
                    //float3 l;
                    //float3 n;
                    //float3 r;
                    //float3 v;
                    //float ss;
                    //float4 normalWorld;
 
                    //l = normalize(Light.Position[i].xyz - inPosition.xyz);
					
                    //normalWorld = mul(inNormal, World);//ワールドに変換
                    //n = normalize(normalWorld.xyz);
                    //r = 2.0 * n * dot(n, l) - l;
                    //v = normalize(View._41_42_43 - inPosition.xyz);
                    //ss = pow(saturate(dot(r, v)), inSpecular.w);
					
					
                    //outSpecular = float4(ss * inSpecular.xyz * Light.Diffuse[i].xyz, 1.0);
                    //outSpecular = saturate(outSpecular);
                }
				else
				{
					color = float4(0.0f, 0.0f, 0.0f, 0.0f);
				}

				outColor += color;
			}
		}

		outColor += Material.Emission;

		outDiffuse = saturate(outColor);
		outDiffuse.a = inDiffuse.a * Material.Diffuse.a;
	}
}



//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void PixelShaderPolygon( in float4 inPosition	: SV_POSITION,	// 頂点の位置情報（x, y, z, w）
						 in float4 inNormal		: NORMAL0,		// 頂点の法線ベクトル（x, y, z, w）
						 in float2 inTexCoord	: TEXCOORD0,	// 頂点のテクスチャ座標（x, y）
						 in float4 inDiffuse	: COLOR0,		// 頂点の拡散反射率（色情報）

						 out float4 outDiffuse	: SV_Target)
{
    float4 color;

    if (Material.noTexSampling == 0)
    {
        color = g_Texture.Sample(g_SamplerState, inTexCoord);

        color *= inDiffuse;
    }
    else
    {
        color = inDiffuse;
    }

    outDiffuse = color;
}