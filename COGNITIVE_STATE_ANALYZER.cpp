#include <iostream>
using namespace std;

string analyzeState(int focus, int mood, int sleep) {
    if (focus > 7 && mood > 6 && sleep >= 6)
        return "Productive / High Focus State";
    
    else if (focus >= 4 && mood >= 4)
        return "Neutral / Balanced State";
    
    else
        return "Low Focus / Stressed State";
}

int main() {
    int focus, mood, sleep;

    cout << "Enter focus level (1-10): ";
    cin >> focus;

    cout << "Enter mood level (1-10): ";
    cin >> mood;

    cout << "Enter hours of sleep: ";
    cin >> sleep;

    string result = analyzeState(focus, mood, sleep);

    cout << "\nCognitive State Analysis Result: " << result << endl;

    return 0;
}
