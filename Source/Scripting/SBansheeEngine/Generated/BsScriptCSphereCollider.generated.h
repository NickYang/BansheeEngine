#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "Wrappers/BsScriptComponent.h"
#include "BsScriptCCollider.generated.h"

namespace bs
{
	class CSphereCollider;

	class BS_SCR_BE_EXPORT ScriptCSphereCollider : public TScriptComponent<ScriptCSphereCollider, CSphereCollider, ScriptCColliderBase>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "SphereCollider")

		ScriptCSphereCollider(MonoObject* managedInstance, const GameObjectHandle<CSphereCollider>& value);

	private:
		static void Internal_setRadius(ScriptCSphereCollider* thisPtr, float radius);
		static float Internal_getRadius(ScriptCSphereCollider* thisPtr);
		static void Internal_setCenter(ScriptCSphereCollider* thisPtr, Vector3* center);
		static void Internal_getCenter(ScriptCSphereCollider* thisPtr, Vector3* __output);
	};
}
