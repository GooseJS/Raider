#version 320 es

in highp vec3 worldPos;
in highp vec3 outLightPos;
in highp vec3 outTexCoord;
out highp vec3 color;

uniform highp sampler2DArray texAtlas;

void main()
{

	color = texture(texAtlas, outTexCoord).xyz;
	highp vec3 worldNormal = cross(dFdx(worldPos.xyz), dFdy(worldPos.xyz));
	highp float ambient = 0.3;
	worldNormal = normalize(worldNormal);
	highp vec3 lightDir = normalize(outLightPos + worldPos);
	highp float diff = max(dot(worldNormal, lightDir), 0.0);
	highp vec3 result = (ambient + diff) * color;
	color = result;

}