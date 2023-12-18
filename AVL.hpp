#ifndef AVL_HPP
#define AVL_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <clocale>
#include <cmath>

class Vertex {
public:
    std::string englishWord;
    std::string russianWord;

    std::shared_ptr<Vertex> left;
    std::shared_ptr<Vertex> right;

    int W = 0;
    int H = 0;
    int bal = 0;
};

class AVL {
private:
	std::shared_ptr<Vertex> root;
	int size(const std::shared_ptr<Vertex>& p);
	int height(const std::shared_ptr<Vertex>& p);
	int dec;
	void LL_turn(std::shared_ptr<Vertex>& p);
	void LL1_turn(std::shared_ptr<Vertex>& p, int dec);
	void RR_turn(std::shared_ptr<Vertex>& p);
	void RR1_turn(std::shared_ptr<Vertex>& p, int dec);
	void LR_turn(std::shared_ptr<Vertex>& p);
	void RL_turn(std::shared_ptr<Vertex>& p);

public:
	int rost;
	AVL(std::shared_ptr<Vertex>& p);
	std::shared_ptr<Vertex>& getRoot();
	void insert(std::string rus, std::string eng, std::shared_ptr<Vertex>& p);
	void BL(std::shared_ptr<Vertex>& p, int dec);
	void BR(std::shared_ptr<Vertex>& p, int dec);
	void del(std::shared_ptr<Vertex>& r, int dec, std::shared_ptr<Vertex>& q);
	void obhod1(const std::shared_ptr<Vertex>& p);
	void obhod2(const std::shared_ptr<Vertex>& p);
	void obhod3(const std::shared_ptr<Vertex>& p, int& count, int currentPage, int pageSize, int& currentDisplayCount);
	void display(std::shared_ptr<Vertex>& root, unsigned int currentPage, unsigned int pageSize, unsigned int totalNumberOfPages);
	void print(const std::string& prefix, std::shared_ptr<Vertex>& root, bool isLeft, std::ostream& os);
	void print(std::shared_ptr<Vertex>& root, std::ostream& os);
	std::string toLower(const std::string& str);
	void searchHelper(const std::shared_ptr<Vertex>& current, const std::string& substr, std::vector<std::string>& result);
	void search(const std::shared_ptr<Vertex>& root, const std::string& substr, std::vector<std::string>& result);
	void searchHelper2(const std::shared_ptr<Vertex>& current, const std::string& substr, std::vector<std::string>& result);
	void search2(const std::shared_ptr<Vertex>& root, const std::string& substr, std::vector<std::string>& result);
	bool startsWith(const std::string& str, const std::string& prefix);
	bool findWordCount(const std::shared_ptr<Vertex>& p, const std::string& substr, int& currentWordNumber, int& wordCount);
	int findPageNumber(const std::shared_ptr<Vertex>& p, const std::string& substr, int N);
};

void displayMenu();
void displayAdditionalMenu();
std::string replaceTabsWithSpaces(const std::string& str);
std::string removeCarriageReturns(const std::string& str);

#endif // AVL_HPP