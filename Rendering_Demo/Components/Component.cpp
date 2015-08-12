#include "Component.h"

bool Component::isEnabled()
{
	if (!m_enabled)
		return false;

	if (gameObject == NULL || gameObject->isEnabled())
		return true;
	else
		return false;
}

Component::Component()
{
}


Component::~Component()
{
}
