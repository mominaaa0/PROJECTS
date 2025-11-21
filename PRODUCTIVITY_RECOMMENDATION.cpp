#include <iostream>
using namespace std;

string getSuggestion(int focus, int mood, int fatigue) {
    if (focus > 7 && mood > 6 && fatigue < 4)
        return "You should start a High-Intensity Task.";
    else if (focus > 4 && mood >= 5)
        return "Try a Medium-Level Task.";
    else
        return "Take a Short Break and Hydrate.";
}

int main() {
    int focus, mood, fatigue;

    cout << "Enter focus level (1-10): ";
    cin >> focus;

    cout << "Enter mood level (1-10): ";
    cin >> mood;

    cout << "Enter fatigue level (1-10): ";
    cin >> fatigue;

    cout << "\nSuggestion: " 
         << getSuggestion(focus, mood, fatigue) 
         << endl;

    return 0;
}
