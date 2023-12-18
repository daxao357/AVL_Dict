#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif
#include "AVL.hpp"
#include <iostream>
#include <clocale>
#include <algorithm> 
#include <vector>
#include <cctype> 
#include <stack>
#include <fstream>
#include <string> 
#include <stdlib.h> 
#include <cmath>
#include <memory>
#include <limits>

int main()
{
	system(CLEAR_SCREEN);
	setlocale(LC_ALL, "ru_RU.UTF-8");
	std::shared_ptr<Vertex> a;
	AVL tree(a);

	int count = 1;
	std::string line;
	std::ifstream in("dict.txt");
	unsigned int totalNumberOfElements = 0;
	unsigned int N = 20;
	if (in.is_open()) {
		std::string rus;
		std::string eng;
		while (std::getline(in, rus) && std::getline(in, eng)) {
			rus = removeCarriageReturns(replaceTabsWithSpaces(rus));
			eng = removeCarriageReturns(replaceTabsWithSpaces(eng));
			tree.insert(rus, eng, a);
			totalNumberOfElements++;
		}
	}
	unsigned int totalNumberOfPages = totalNumberOfElements / N + (totalNumberOfElements % N != 0 ? 1 : 0);

	//tree.print(a, std::cout);

	std::string searchQuery;
	std::string choice;
	do {
		system(CLEAR_SCREEN);
		displayMenu();
		std::cout << "Выберите действие: ";
		std::getline(std::cin, choice);

		if (choice == "1") {
			std::string searchQuery;
			std::cout << "Введите слово для поиска: ";
			std::getline(std::cin, searchQuery);

			std::vector<std::string> searchResults;
			int dec = 0;
			tree.search2(a, searchQuery, searchResults);

			std::cout << "Результаты поиска для '" << searchQuery << "':\n\n";
			for (const auto& result : searchResults) {
				std::cout << result << std::endl;
			}
			std::cout << "\nДля продолжения нажмите Enter...";
			std::cin.get();
		}

		if (choice == "2") {

			std::string searchQuery;
			std::cout << "Введите слово для поиска: ";
			std::getline(std::cin, searchQuery);

			std::vector<std::string> searchResults;
			int dec = 0;
			tree.search(a, searchQuery, searchResults);

			std::cout << "Результаты поиска для '" << searchQuery << "':\n\n";
			for (const auto& result : searchResults) {
				std::cout << result << std::endl;
			}
			std::cout << "\nДля продолжения нажмите Enter...";
			std::cin.get();
		}

		else if (choice == "3") {
			std::string additionalChoice;
			int currentPage = 1;

			do {
				system(CLEAR_SCREEN);
				displayAdditionalMenu();
				tree.display(a, currentPage, N, totalNumberOfPages);
				std::cout << "Выберите действие: ";
				std::getline(std::cin, additionalChoice);

				if (additionalChoice == "1") {
					system(CLEAR_SCREEN);
					if (currentPage != totalNumberOfPages) currentPage++;
					continue;
				}
				else if (additionalChoice == "2") {
					system(CLEAR_SCREEN);
					if (currentPage != 1) currentPage--;
					continue;
				}
				else if (additionalChoice == "3") {
					unsigned int inputPage;
					std::cout << "Введите номер страницы: ";
					std::cin >> inputPage;

					if (inputPage <= 0 || inputPage > totalNumberOfPages) {
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}

					currentPage = inputPage;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}

				else if (additionalChoice == "4") {
					std::string searchQuery;
					std::cout << "Введите слово для поиска страницы: ";
					std::getline(std::cin, searchQuery);
					int result = tree.findPageNumber(a, searchQuery, N);

					if (result != -1) {
						currentPage = result;
						continue;
					}
					else {
						std::cout << "Слово не найдено в словаре." << std::endl;
					}

					std::cout << "\nДля продолжения нажмите Enter...";
					std::cin.get();
				}

				else if (additionalChoice == "5") {
					break;
				}

				system(CLEAR_SCREEN);
			} while (true);
		}
		else if (choice == "4") {
			std::cout << "Выход!\n";
			break;
		}
		system(CLEAR_SCREEN);
	} while (true);

	in.close();
}
