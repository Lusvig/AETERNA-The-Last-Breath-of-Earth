#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAeternaModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

// Ensure module log category is available
DECLARE_LOG_CATEGORY_EXTERN(LogAeterna, Log, All);
