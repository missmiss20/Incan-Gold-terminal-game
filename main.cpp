#include "player.h"
#include "adventure.h"

#include <stdlib.h>
#include <string>        
#include <locale>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    int playerNumber;
    cout << "How many players are there?" <<endl;
    cin >> playerNumber;
    adventure a(playerNumber);
    a.game();
    return 0;
}
