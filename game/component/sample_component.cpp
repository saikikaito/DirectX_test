#include "sample_component.h"



void SampleComponent::update() {

	//--------------------------------------------------
	// ��]

	getTransform()->rotate(lib::Vector3::UP, lib::Math::toRadian(90.0f * lib::Time::getDeltaTime()));

	//--------------------------------------------------

}
