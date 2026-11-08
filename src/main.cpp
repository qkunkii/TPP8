#include <iostream>

void runRawApiDemo();
void runQueriesDemo();
void runTransactionsDemo();
void runRepoDemo();

int main() {
    try {
        runRawApiDemo();
        runQueriesDemo();
        runTransactionsDemo();
        runRepoDemo();
        std::cout << "\nAll demos finished successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}