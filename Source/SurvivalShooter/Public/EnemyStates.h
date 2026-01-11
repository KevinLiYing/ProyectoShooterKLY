// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EEnemyStates : uint8
{
	Patrol        UMETA(DisplayName = "Patrol"),
	Investigate   UMETA(DisplayName = "Investigate"),
	Chase         UMETA(DisplayName = "Chase"),
	Attack		  UMETA(DisplayName = "Attack")
};

