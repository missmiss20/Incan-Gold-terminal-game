#include <stdio.h>
#include <ctype.h>
#include "adventure.h"

#include "player.h"

#include <stdlib.h>
#include <string>        
#include <locale>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class noPlayerActiveException{};
class EncounterMonsterException{};

adventure::adventure(int numberOfPlayers){
	playerNumber = numberOfPlayers;

	for(size_t i = 0; i < playerNumber; i++){
		player* playerr = new player();
		players.push_back(playerr);
	}

	cards.push_back(std::pair<string, int>("Mummy",0));
	cards.push_back(std::pair<string, int>("Zombie",0));
	cards.push_back(std::pair<string, int>("Snake",0));
	cards.push_back(std::pair<string, int>("Trap",0));
	cards.push_back(std::pair<string, int>("Poison cloud",0));
	cardCount += 5;
	for(int x = 0; x < 10; x++){

		cards.push_back(std::pair<string, int>("Treasure",generate()));
		cardCount++;           
	}

}
adventure::~adventure(){

	for(size_t i = 0; i < playerNumber; i++)
	{
		delete players[i];
	}
}

void adventure::game(){

	for(size_t i = 0; i < rounds; i++){
		cout << "ROUND " << i+1 <<endl;
		round();
		summary();
		cout << "End of round " << i+1 <<endl <<endl;
		for(size_t k = 0; k < playerNumber; k++){
			players[k]->decision = true;
		}
	}

	size_t maxScore = 0;
	size_t maxPlayer = 0;

	cout << "GAME OVER: " <<endl;
	for(size_t j = 0; j < players.size(); j++){
		cout << "Player " << j+1 << "'s Score is: " << players[j]->score <<endl;
		if(players[j]->score > maxScore){
			maxScore = players[j]->score;
			maxPlayer = j+1;
		}
	}
	cout << "The Winner is: Player " << maxPlayer << endl;


}

void adventure::round(){

	try{
		for(size_t i = 1; i < 10; i++){
			cout <<"TURN " << i <<endl;
			turn();
		}
		for(size_t k = 0; k < playerNumber; k++){
			players[k]->score += players[k]->bag;
		}
	}
	catch(EncounterMonsterException e){
		cout << "Danger! Run!!!" <<endl;
		for(size_t j = 0; j < playerNumber; j++){
			if(players[j]->decision){
				cout << "Player " << j+1 << " didn't get any score!" <<endl;
				players[j]->bag = 0;
			}
		}
		cout << "End Round Early!" <<endl;
	}
	catch(noPlayerActiveException e){
		cout << "All players have retreated!" <<endl;
	}
}

void adventure::turn(){
	cout << endl << "Turn begins!" <<endl;
	std::cout << "Players type 1 to move forward, type 0 to retreat" <<std::endl;

	int active = 0;
	int retreat = 0;
	for(size_t i = 0; i < playerNumber; i++){
		if(players[i]->decision){
			cout << "Player " << i+1 << " make decision!" <<endl;
			players[i]->move();
			cout << endl;
		}
		else{
			cout << "Player " << i+1 << " has passed the turn!" <<endl;
			cout << endl;
		}
	}

	for(size_t j = 0; j < playerNumber; j++){
		if(players[j]->decision)
			active++;
		if(players[j]->retreating)
			retreat++;
	}
	if(active == 0){
		throw noPlayerActiveException();
	}
	size_t drawCardIndex = rand()%cardCount;
	
	if(cards[drawCardIndex].first != "Treasure"){
		cards[drawCardIndex].second+=1;
		cout << "Warning! Encounter Danger: " << cards[drawCardIndex].first << " For The "<< cards[drawCardIndex].second << " Time!"<< endl;
		
		if(cards[drawCardIndex].second >= 2){
			throw EncounterMonsterException();
		}
	}
	else{
		cout << "Found Treasure! Value: " << cards[drawCardIndex].second <<endl;
		int reward = cards[drawCardIndex].second / active;
		for(size_t k = 0; k < playerNumber; k++){
			if(players[k]->decision){
				cout << "player " << k+1 << " got " << reward << " points in bag!" <<endl; 
				players[k]->bag += reward;
			}
		}
		leftover = leftover + cards[drawCardIndex].second - active*reward;

		if(retreat != 0){
			int retreatReward = leftover / retreat;
			for(size_t l = 0; l < playerNumber; l++){
				if(players[l]->retreating){
					players[l]->score += retreatReward;
					players[l]->retreating = false;
				}

			}
			leftover = leftover - retreatReward;
		}
		cards.erase(cards.begin()+drawCardIndex);
		cardCount--;
		
	}
	cout << endl;
}

void adventure::summary(){
	for(size_t i = 0; i < 5; i++){
	
		cout << "We Have Encountered: " << cards[i].first << " " << cards[i].second << " Time(s)" <<endl;
	}
	for(size_t j = 1; j < playerNumber+1; j++){
	
		cout << "Player " << j << "'s score is " << players[j-1]->score << "!" <<endl;
	}
}


int adventure::getWordCount(std::string word) const {
	int count = 0;
	for(size_t i = 0; i < 30; i++){
		if(cards[i].first == word)
			count++;
	}
	return count;
}

int adventure::generate(){
	return playerNumber*(rand()%5 + 1);
}
