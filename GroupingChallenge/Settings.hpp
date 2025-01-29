#pragma once
#include <stdint.h>
#include <random>
namespace constants
{
	constexpr const double greedyProba = 0.000001;

	constexpr const int populations = 10;
	constexpr const int populationSize = 40;
	constexpr const int tournamentSize = 10;
	//TODO static assert tw > 0
	constexpr const int tournamentWinners = 4;
	constexpr const double pTournament = 0.8;
	constexpr const double pRandom = 1 - pTournament;
	//constexpr const int bufferSize = 1000;
	constexpr const double pMutationLow = 0.2; //1/pop * 0.2
	constexpr const double pMutationHigh = 0.8;

	constexpr const double epsilon = 1;

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