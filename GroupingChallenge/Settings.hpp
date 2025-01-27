#pragma once
#include <stdint.h>
#include <random>
namespace constants
{
	constexpr const int populations = 24;
	constexpr const int populationSize = 20;
	constexpr const int tournamentSize = 10;
	//TODO static assert tw > 0
	constexpr const int tournamentWinners = 3;
	constexpr const double pTournament = 0.15;
	constexpr const double pRandom = 1 - pTournament;
	//constexpr const int bufferSize = 1000;
	constexpr const double pMutationLow = 0.2; //1/pop * 0.2
	constexpr const double pMutationHigh = 0.6;

	constexpr const double epsilon = 10;

	constexpr const double migrationPercent = 0.3;
	constexpr const double migrationPopulationPercent = 0.1;
	constexpr const double migrationSize = populationSize * migrationPopulationPercent;
	constexpr const int migrations = populations * migrationPercent;

	constexpr const int lowerBound = 1;
	constexpr const bool debug = true;

	constexpr const int windowWidth = 800;
	constexpr const int windowHeight = 600;
	constexpr const float pointSize = 3.;
}

//13s