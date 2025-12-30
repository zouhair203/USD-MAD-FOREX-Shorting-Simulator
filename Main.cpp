#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

double dollarPrices[30] = {
    9.85, 9.92, 9.88, 9.95, 9.90, 9.97,
    10.02, 9.98, 10.05, 10.01,
    10.08, 10.03, 10.10, 10.06, 10.12,
    10.09, 10.15, 10.11, 10.18, 10.14,
    10.20, 10.16, 10.22, 10.19, 10.25,
    10.21, 10.27, 10.23, 10.29, 10.26
};

double wallet = 10000.0;
int betNumber = 0;

void displayPreviousDays(int daysToShow, int startDay) {
    cout << "\n" << string(50, '=') << endl;
    cout << "     Previous " << daysToShow << " days USD prices" << endl;
    cout << string(50, '=') << endl;
    cout << "Day\tPrice (MAD)" << endl;
    cout << string(20, '-') << endl;
    for (int i = startDay; i < startDay + daysToShow && i < 30; i++) {
        cout << i << "\t" << fixed << setprecision(2) << dollarPrices[i] << endl;
    }
    cout << string(50, '=') << endl;
}

int getUserDirection() {
    cout << "\n" << string(30, '-') << endl;
    cout << "Choose your direction:" << endl;
    cout << "1. LONG  (expect price UP )" << endl;
    cout << "2. SHORT (expect price DOWN)" << endl;
    cout << string(30, '-') << endl;
    cout << "Enter choice (1 or 2): ";
    int choice;
    cin >> choice;
    while (choice != 1 && choice != 2) {
        cout << "Enter 1 or 2 only: ";
        cin >> choice;
    }
    return choice;
}

double getUserPredictedPrice(double previousPrice) {
    cout << "\nLast day price: " << fixed << setprecision(2) << previousPrice << endl;
    cout << "Enter predicted price for next day: ";
    double predictedPrice;
    cin >> predictedPrice;
    return predictedPrice;
}

double getPositionSize() {
    cout << "Enter position size (MAD): ";
    double size;
    cin >> size;
    if (size > wallet || size <= 0) {
        cout << "Using full wallet: " << fixed << setprecision(2) << wallet << endl;
        size = wallet;
    }
    return size;
}

void calculateProfit(double positionSize, double predictedPrice, double previousPrice, int dayIndex) {
    double actualPrice = dollarPrices[dayIndex];
    double priceDifference = abs(actualPrice - predictedPrice);
    
    if (priceDifference < 0.001) {
        priceDifference = 0.001;
    }
    
    double profitMultiplier = positionSize / (priceDifference * 100.0);
    bool predictedUp = (predictedPrice > previousPrice);
    bool actualUp = (actualPrice > previousPrice);
    bool correctDirection = (predictedUp == actualUp);
    
    double profit = correctDirection ? profitMultiplier : -profitMultiplier;
    wallet += profit;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "              Bet " << (betNumber + 1) << " Result" << endl;
    cout << string(50, '=') << endl;
    cout << "Previous price:  " << fixed << setprecision(2) << previousPrice << endl;
    cout << "Your prediction: " << fixed << setprecision(2) << predictedPrice << endl;
    cout << "Actual price:    " << fixed << setprecision(2) << actualPrice << endl;
    cout << "Difference:      " << fixed << setprecision(3) << priceDifference << endl;
    cout << (correctDirection ? "Direction: CORRECT" : "Direction: WRONG") << endl;
    cout << "P&L Formula:     " << fixed << setprecision(0) << positionSize 
         << " / (" << priceDifference << " * 100)" << endl;
    cout << "Profit:          " << (profit >= 0 ? "+" : "") << fixed << setprecision(2) << profit << " MAD" << endl;
    cout << "New Wallet:      " << fixed << setprecision(2) << wallet << " MAD" << endl;
    cout << string(50, '=') << endl;
}

void playBet() {
    int betDays[6] = {6, 10, 15, 20, 25, 30};
    int targetDay = betDays[betNumber];
    int previousDay = targetDay - 1;
    double previousPrice = dollarPrices[previousDay];
    int startDay = (betNumber == 0) ? 0 : targetDay - 5;
    
    displayPreviousDays(5, startDay);
    cout << "Predict Day " << targetDay << " price:" << endl;
    
    int direction = getUserDirection();
    double predictedPrice = getUserPredictedPrice(previousPrice);
    double positionSize = getPositionSize();
    
    cout << "\nDay " << targetDay << " revealed: " << fixed << setprecision(2) << dollarPrices[targetDay] << " MAD" << endl;
    calculateProfit(positionSize, predictedPrice, previousPrice, targetDay);
    betNumber++;
}

void showFinalPnL() {
    double totalPnL = wallet - 10000.0;
    double returnPercent = (totalPnL / 10000.0) * 100;
    
    cout << "\n" << string(60, '=') << endl;
    cout << "                 FINAL RESULTS - 6 BETS COMPLETED" << endl;
    cout << string(60, '=') << endl;
    cout << "Starting wallet:     10,000.00 MAD" << endl;
    cout << "Final wallet:        " << fixed << setprecision(2) << wallet << " MAD" << endl;
    cout << "Total P&L:           " << (totalPnL >= 0 ? "+" : "") 
         << fixed << setprecision(2) << totalPnL << " MAD" << endl;
    cout << "Return percentage:   " << fixed << setprecision(2) << returnPercent << "%" << endl;
    cout << string(60, '=') << endl;
}

int main() {
    cout << string(50, '=') << endl;
    cout << "         USD/MAD Trading Game" << endl;
    cout << string(50, '=') << endl;
    cout << "6 bets over 30 days. Starting wallet: 10000 MAD" << endl;
    cout << "Profit = Position / (|Actual-Predicted| * 100)" << endl;
    cout << string(50, '=') << endl << endl;
    
    for (int i = 0; i < 6; i++) {
        playBet();
        if (i < 5) {
            cout << "\nPress ENTER for next bet or 'q' to quit: ";
            char choice;
            cin >> choice;
            if (choice == 'q' || choice == 'Q') {
                break;
            }
        }
    }
    
    showFinalPnL();
    return 0;
}
