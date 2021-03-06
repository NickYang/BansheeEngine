//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsScriptRRefBase.h"
#include "BsScriptMeta.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "Resources/BsResources.h"
#include "Wrappers/BsScriptResource.h"
#include "BsScriptResourceManager.h"
#include "BsApplication.h"
#include "Serialization/BsScriptAssemblyManager.h"

namespace bs
{
	ScriptRRefBase::ScriptRRefBase(MonoObject* instance, ResourceHandle<Resource> resource)
		:ScriptObject(instance), mResource(std::move(resource)), mGCHandle(MonoUtil::newGCHandle(instance))
	{ }

	ScriptRRefBase::~ScriptRRefBase()
	{
		BS_ASSERT(mGCHandle == 0 && "Object being destroyed without its managed instance being freed first.");
	}

	void ScriptRRefBase::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_IsLoaded", (void*)&ScriptRRefBase::internal_IsLoaded);
		metaData.scriptClass->addInternalCall("Internal_GetResource", (void*)&ScriptRRefBase::internal_GetResource);
		metaData.scriptClass->addInternalCall("Internal_GetUUID", (void*)&ScriptRRefBase::internal_GetUUID);
		metaData.scriptClass->addInternalCall("Internal_CastAs", (void*)&ScriptRRefBase::internal_CastAs);
	}

	ScriptRRefBase* ScriptRRefBase::createInternal(const ResourceHandle<Resource>& handle, ::MonoClass* rawType)
	{
		MonoClass* type = nullptr;
		if(rawType == nullptr)
			type = metaData.scriptClass;
		else
		{
			type = MonoManager::instance().findClass(rawType);
			if (type == nullptr)
				return nullptr;

			assert(type->isSubClassOf(metaData.scriptClass));
		}

		MonoObject* obj = type->createInstance();
		ScriptRRefBase* output = new (bs_alloc<ScriptRRefBase>()) ScriptRRefBase(obj, handle);

		return output;
	}

	MonoObject* ScriptRRefBase::getManagedInstance() const
	{
		return MonoUtil::getObjectFromGCHandle(mGCHandle);
	}

	void ScriptRRefBase::_clearManagedInstance()
	{
		if (mGCHandle != 0)
		{
			MonoUtil::freeGCHandle(mGCHandle);
			mGCHandle = 0;
		}
	}

	void ScriptRRefBase::_onManagedInstanceDeleted(bool assemblyRefresh)
	{
		if (mGCHandle != 0)
		{
			MonoUtil::freeGCHandle(mGCHandle);
			mGCHandle = 0;
		}
	}

	::MonoClass* ScriptRRefBase::bindGenericParam(::MonoClass* param)
	{
		MonoClass* rrefClass = ScriptAssemblyManager::instance().getBuiltinClasses().genericRRefClass;

		::MonoClass* params[1] = { param };
		return MonoUtil::bindGenericParameters(rrefClass->_getInternalClass(), params, 1);
	}

	bool ScriptRRefBase::internal_IsLoaded(ScriptRRefBase* thisPtr)
	{
		return thisPtr->mResource.isLoaded(false);
	}

	MonoObject* ScriptRRefBase::internal_GetResource(ScriptRRefBase* thisPtr)
	{
		ResourceLoadFlags loadFlags = ResourceLoadFlag::LoadDependencies | ResourceLoadFlag::KeepInternalRef;

		if (gApplication().isEditor())
			loadFlags |= ResourceLoadFlag::KeepSourceData;

		const HResource resource = gResources().loadFromUUID(thisPtr->getHandle().getUUID(), loadFlags);
		ScriptResourceBase* scriptResource = ScriptResourceManager::instance().getScriptResource(resource, true);

		return scriptResource->getManagedInstance();
	}

	void ScriptRRefBase::internal_GetUUID(ScriptRRefBase* thisPtr, UUID* uuid)
	{
		*uuid = thisPtr->getHandle().getUUID();
	}

	MonoObject* ScriptRRefBase::internal_CastAs(ScriptRRefBase* thisPtr, MonoReflectionType* type)
	{
		::MonoClass* rawResType = MonoUtil::getClass(type);

		MonoClass* resType = MonoManager::instance().findClass(rawResType);
		if (resType == nullptr)
			return nullptr; // Not a valid type

		::MonoClass* rrefType = nullptr;
		if(resType != ScriptResource::getMetaData()->scriptClass)
		{
			if (!resType->isSubClassOf(ScriptResource::getMetaData()->scriptClass))
				return nullptr; // Not a resource type

			rrefType = bindGenericParam(rawResType);
		}

		ScriptRRefBase* castRRefBase = create(thisPtr->mResource, rrefType);
		if(castRRefBase)
			return castRRefBase->getManagedInstance();

		return nullptr;
	}
}

