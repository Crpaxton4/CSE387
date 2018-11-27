#pragma once
#include "Component.h"
#include "SharedGeneralLighting.h"
class LightComponent :public Component
{
public:
	LightComponent(class Actor* owner, lightSource id, bool enabled);

	void setEnable();
	void setDisable();
	
	void setAmbientColor(vec4 newAmb);
	void setDiffuseColor(vec4 newDif);
	void setSpecularColor(vec4 newSpec);

protected:
	lightSource id;
	vec4 ambientColor = vec4(0, 0, 0, 1);;
	vec4 diffuseColor = vec4(0, 0, 0, 1);
	vec4 specularColor = vec4(0, 0, 0, 1);
	bool enabled = true;
};

