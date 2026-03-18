Shader "Unlit/HexShader"
{
    Properties
    {
        _BaseColor          ("Base Color", Color) = (0,0,0,1)
        _Progress           ("Progress", Range(0,1)) = 0
         _MirrorTiling      ("Tiling", Float) = 1
        _MainTex            ("Texture", 2D) = "white" {}
        _MaskTex            ("Mask", 2D) = "white" {}
       
    }
    SubShader
    {
        Tags
        {
            "RenderType"="Opaque" 
        }
        LOD 100
        Blend SrcAlpha OneMinusSrcAlpha  // ← 이게 없으면 alpha 무시됨!

        Pass
        {
            CGPROGRAM
            #pragma vertex  VS
            #pragma fragment PS
            // make fog work
            #pragma multi_compile_fog

            #include "UnityCG.cginc"

            struct VS_In
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct VS_Out
            {
                float2 uv : TEXCOORD0;
                UNITY_FOG_COORDS(1)
                float4 vertex : SV_POSITION;
            };

            sampler2D   _MainTex;
            sampler2D   _MaskTex;
            float4      _MainTex_ST;
            float       _Progress;
            float       _MirrorTiling;

            VS_Out VS (VS_In In)
            {
                VS_Out Out;
                Out.vertex = UnityObjectToClipPos(In.vertex);
                Out.uv = TRANSFORM_TEX(In.uv, _MainTex);
                return Out;
            }

            float4 PS (VS_Out In) : SV_Target
            {
                // sample the texture
                float2 uv = In.uv * _MirrorTiling;

                float4 MainColor = tex2D(_MaskTex, uv);
                float MaskColor = tex2D(_MaskTex, uv).r;

                if(_Progress <= MaskColor)
                    discard;
                
                MainColor.a = lerp(0.f, 1.f, _Progress * 3);
                // apply fog
                return MainColor;
            }
            ENDCG
        }
    }
}
