#include "GameApplicationPCH.h"
#include "WaterSimulationController.h"

WaterSimulationController::WaterSimulationController(void)
{
	VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("tankcamera");
	Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());
/*#if defined(_VISION_ANDROID)
	pMod = static_cast<vHavokPhysicsModule*>(vHavokPhysicsModule::GetInstance());
	pMotionInput = (VMotionInputAndroid*)(&VInputManager::GetInputDevice(INPUT_DEVICE_MOTION_SENSOR));
	pMotionInput->SetEnabled(true);
#endif*/
}
bool WaterSimulationController::Run(VInputMap* inputMap){

	if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE)){
		VisBaseEntity_cl *ent = this->AddSphere(0, 0, 300);
		ent->SetScaling(0.15f);
		ent->RemoveAllComponents();
		vHavokRigidBody *sphere = new vHavokRigidBody();
		sphere->Havok_TightFit = true;
		sphere->Havok_Restitution = 0.1f;
		ent->AddComponent(sphere);
	}
	if(inputMap->GetTrigger(CUSTOM_CONTROL_TWO)){
		TriggerBoxEntity_cl *triggerbox = vdynamic_cast <TriggerBoxEntity_cl *> (Vision::Game.SearchEntity("triggerbox"));
		
		if(triggerbox->IsEnabled())
			triggerbox->SetEnabled(false);
		else if(!triggerbox->IsEnabled())
			triggerbox->SetEnabled(true);
	}
	return true;
}


WaterSimulationController::~WaterSimulationController(void)
{
}
void WaterSimulationController::MapTriggers(VInputMap* inputMap){
#if defined(WIN32)
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, V_KEYBOARD, VInputControl::CT_KB_UP, VInputOptions::Once()); 
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, V_KEYBOARD, VInputControl::CT_KB_DOWN, VInputOptions::Once()); 
#endif

#if defined(_VISION_ANDROID)
	int width = Vision::Video.GetXRes();
	int height = Vision::Video.GetYRes();
	VTouchArea* addRagdollArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef((float)width *.8f, (float)height * 0 , (float)width , (float)height * .2f), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, addRagdollArea, CT_TOUCH_ANY);

	VTouchArea* addCubeArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(0.0f, (float)height*.8f, (float)width*.2f, (float)height), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, addCubeArea, CT_TOUCH_ANY);
#endif 
}