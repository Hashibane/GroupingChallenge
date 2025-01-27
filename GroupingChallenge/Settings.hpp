#pragma once
#include <stdint.h>
#include <random>
namespace constants
{
	constexpr const int populations = 1;
	constexpr const int populationSize = 100;
	constexpr const int tournamentSize = 20;
	//TODO static assert tw > 0
	constexpr const int tournamentWinners = 3;
	constexpr const double pTournament = 0.15;
	constexpr const double pRandom = 1 - pTournament;
	//constexpr const int bufferSize = 1000;
	constexpr const double pMutation = 0.2;
	constexpr const double pMutationGene = 0.002;

	constexpr const int lowerBound = 1;
	constexpr const bool debug = true;

	constexpr const int windowWidth = 800;
	constexpr const int windowHeight = 600;
	constexpr const float pointSize = 3.;
}

//13s
