// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSlot.h"
#include "CoreMinimal.h"

/**
 * 
 */
class Command
{
public:
	Command() {};
	virtual ~Command() {};

	virtual void Execute() = 0;
	virtual void Revert() = 0;
	virtual void Update(float DeltaTime) {};
	virtual bool IsExecuting() { return false; };
};
