#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "Wrappers/BsScriptComponent.h"
#include "../../../bsf/Source/Foundation/bsfCore/Physics/BsCharacterController.h"
#include "../../../bsf/Source/Foundation/bsfCore/Physics/BsCharacterController.h"
#include "../../../bsf/Source/Foundation/bsfCore/Physics/BsCharacterController.h"
#include "Math/BsRadian.h"

namespace bs
{
	class CCharacterController;
	struct __ControllerControllerCollisionInterop;
	struct __ControllerColliderCollisionInterop;

	class BS_SCR_BE_EXPORT ScriptCCharacterController : public TScriptComponent<ScriptCCharacterController, CCharacterController>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "CharacterController")

		ScriptCCharacterController(MonoObject* managedInstance, const GameObjectHandle<CCharacterController>& value);

	private:
		void onColliderHit(const ControllerColliderCollision& p0);
		void onControllerHit(const ControllerControllerCollision& p0);

		typedef void(BS_THUNKCALL *onColliderHitThunkDef) (MonoObject*, MonoObject* p0, MonoException**);
		static onColliderHitThunkDef onColliderHitThunk;
		typedef void(BS_THUNKCALL *onControllerHitThunkDef) (MonoObject*, MonoObject* p0, MonoException**);
		static onControllerHitThunkDef onControllerHitThunk;

		static CharacterCollisionFlag Internal_move(ScriptCCharacterController* thisPtr, Vector3* displacement);
		static void Internal_getFootPosition(ScriptCCharacterController* thisPtr, Vector3* __output);
		static void Internal_setFootPosition(ScriptCCharacterController* thisPtr, Vector3* position);
		static float Internal_getRadius(ScriptCCharacterController* thisPtr);
		static void Internal_setRadius(ScriptCCharacterController* thisPtr, float radius);
		static float Internal_getHeight(ScriptCCharacterController* thisPtr);
		static void Internal_setHeight(ScriptCCharacterController* thisPtr, float height);
		static void Internal_getUp(ScriptCCharacterController* thisPtr, Vector3* __output);
		static void Internal_setUp(ScriptCCharacterController* thisPtr, Vector3* up);
		static CharacterClimbingMode Internal_getClimbingMode(ScriptCCharacterController* thisPtr);
		static void Internal_setClimbingMode(ScriptCCharacterController* thisPtr, CharacterClimbingMode mode);
		static CharacterNonWalkableMode Internal_getNonWalkableMode(ScriptCCharacterController* thisPtr);
		static void Internal_setNonWalkableMode(ScriptCCharacterController* thisPtr, CharacterNonWalkableMode mode);
		static float Internal_getMinMoveDistance(ScriptCCharacterController* thisPtr);
		static void Internal_setMinMoveDistance(ScriptCCharacterController* thisPtr, float value);
		static float Internal_getContactOffset(ScriptCCharacterController* thisPtr);
		static void Internal_setContactOffset(ScriptCCharacterController* thisPtr, float value);
		static float Internal_getStepOffset(ScriptCCharacterController* thisPtr);
		static void Internal_setStepOffset(ScriptCCharacterController* thisPtr, float value);
		static void Internal_getSlopeLimit(ScriptCCharacterController* thisPtr, Radian* __output);
		static void Internal_setSlopeLimit(ScriptCCharacterController* thisPtr, Radian* value);
		static uint64_t Internal_getLayer(ScriptCCharacterController* thisPtr);
		static void Internal_setLayer(ScriptCCharacterController* thisPtr, uint64_t layer);
	};
}
