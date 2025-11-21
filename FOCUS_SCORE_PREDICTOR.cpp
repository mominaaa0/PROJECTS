#include <iostream>
using namespace std;

int main() {
    int studyTime, screenTime, breaks;
    float score;

    cout << "Enter study time (hours): ";
    cin >> studyTime;

    cout << "Enter screen time (hours): ";
    cin >> screenTime;

    cout << "Enter number of breaks taken: ";
    cin >> breaks;

    score = (studyTime * 10) - (screenTime * 5) - (breaks * 3);

    if (score < 0) score = 0;
    if (score > 100) score = 100;

    cout << "\nYour Focus Score: " << score << "/100\n";

    if (score >= 70) cout << "High Productivity\n";
    else if (score >= 40) cout << "Moderate Productivity\n";
    else cout << "Low Productivity. Try reducing distractions.\n";

    return 0;
}
